#include "../inc/lib_irc.hpp"
#include "../inc/args.hpp"

int join_command(ft_irc::Args *_args, std::list<std::string> words, int client)
{
	std::list<std::string>::iterator iter;
	std::string channel_name;
	std::string password;

	std::cout<<"JOIN COMMAND ENTER"<<std::endl;
	//ERR_TOOMANYTARGETS
	if (words.size() != 3)
		return (send_message(client, _args->getHost(), "461", _args->getUsernameById(client), *words.begin()));
	channel_name = *++words.begin();
	//ERR_NEEDMOREPARAMS
	if (channel_name[0] != '#' && channel_name[0] != '&')
		return (send_message(client, _args->getHost(), "461", _args->getUsernameById(client), *words.begin()));
	else
		channel_name = channel_name.substr(1, channel_name.size());
	iter = words.begin();
	iter++;
	password = *++iter;
	password = clean_word(password, "\n");
	//ERR_BADCHANNELKEY
	if (password == "none")
		return (send_message(client, _args->getHost(), "475", _args->getUsernameById(client), channel_name));
	else if ((_args->searchChannelByName(channel_name) == true) && (password == _args->getPasswdByChannel(channel_name))
	&& (_args->isUserBanned(channel_name, client) == 0))
	{
		//successfully joined
		if (push_channel_to_list(_args, client, channel_name, password) == 0)
		{
			std::string join = ":" + _args->getNicknameById(client) + " JOIN " + "#" + channel_name + "\r\n";
			send(client, join.c_str(), join.size(), 0);
			std::string message = ":" + _args->getNicknameById(client) + "!" + _args->getUsernameById(client)
   			+ "@" + _args->getHost() + " PRIVMSG #" + channel_name + " :" + _args->getNicknameById(client) + " joined the channel!\r\n";
			send_to_users_of_channel(_args, client, channel_name, message);
		}
	}
	//ERR_BADCHANNELKEY
	else if ((_args->searchChannelByName(channel_name) == true) && (password != _args->getPasswdByChannel(channel_name)))
		return (send_message(client, _args->getHost(), "475", _args->getUsernameById(client), channel_name));
	else if ((_args->searchChannelByName(channel_name) == false) && (_args->getTypeUserById(client) == 2))
	{
		//crear canal y unirse
		if (create_channel(_args, client, channel_name, password) == 0)
		{
			std::string join = ":" + _args->getNicknameById(client) + " JOIN " + "#" + channel_name + "\r\n";
			send(client, join.c_str(), join.size(), 0);
			return (1);
		}
	}
	//channel not found
	else if ((_args->searchChannelByName(channel_name) == false))
		return (send_message(client, _args->getHost(), "403", _args->getUsernameById(client), channel_name));
	//leave channel
	else if (channel_name == "0")
		return (1);
	return (1);
}

int show_all_channels(ft_irc::Args *_args, int client)
{
	_args->showChannelsToId(client);
	return (1);
}

int leave_channel(ft_irc::Args *_args, std::list<std::string> words, int client)
{
	std::string channel_name;

	channel_name = *++words.begin();
	if (channel_name[0] == '#' || channel_name[0] == '$')
		channel_name = channel_name.substr(1, channel_name.size());
	if (words.size() < 2)
		return (send_message(client, _args->getHost(), "461", _args->getUsernameById(client), *words.begin()));
	if (_args->searchChannelByName(channel_name) == false)
		return (send_message(client, _args->getHost(), "403", _args->getUsernameById(client), *words.begin()));
	if (_args->getChannelByName(channel_name)->searchAndDeleteUser(client) == 0)
		return (send_message(client, _args->getHost(), "442", _args->getUsernameById(client), *words.begin()));
	else
	{
		std::string part_message = ":" + _args->getNicknameById(client) + " PART #" + channel_name + " Bye from channel.\r\n";
		send(client, part_message.c_str(), part_message.size(), 0);
	}
	return (1);
}

int show_commands(ft_irc::Args *_args, int client)
{
	int type_of_user = _args->getTypeUserById(client);

	send(client, "--Commands--\n", 13, 0);
	send(client, "- private message: /pm [user] [message]\n", 40, 0);
	send(client, "- know commands: /help or /commands\n", 36, 0);
	if (type_of_user == 2)
	{
		send(client, "- Timeout user: /timeout [name] [seconds]\n", 43, 0);
		send(client, "- Mute words: /mute_word [word]\n", 32, 0);
		send(client, "- Unmute words: /unmute_word [word]\n", 36, 0);
		send(client, "- Kick user: /kick [user]\n", 26, 0);
		send(client, "- Create channels: /create_channel [channel]\n", 45, 0);
	}
	send(client, "- Join channel: /join [channel]\n", 32, 0);
	send(client, "- Show all channels: /channels\n", 31, 0);
	send(client, "- Leave channel: /leave\n", 24, 0);
	send(client, "- Exit ft_irc: /exit\n", 21, 0);
	return (1);
}

int exit_irc(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args, int client)
{
	std::list<ft_irc::Channel*>::iterator iter;

	close(client);
	FD_CLR(client, &_sock_args->master);
	_args->removeFromList(client);
	iter = _args->channels_list.begin();
	while (iter != _args->channels_list.end())
	{
		(*iter)->searchAndDeleteUser(client);
		iter++;
	}
	return (1);
}