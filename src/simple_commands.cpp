#include "../inc/lib_irc.hpp"

int		oper_command(ft_irc::Args *_args, int client, std::list<std::string> words)
{
	std::list<std::string>::iterator iter;
	std::string user;
	std::string password;

	// check if user is already operator
	if (_args->getUserById(client).getType() == 2)
		return (send_message(client, _args->getHost(), "381", _args->getUsernameById(client), *words.begin()));
	// wrong size of list, sends error
	if (words.size() != 3)
		return (send_message(client, _args->getHost(), "461", _args->getUsernameById(client), *words.begin()));
	iter = words.begin();
	user = *++iter;
	// wrong username, sends error
	if (user != _args->getUsernameById(client))
		return (send_message(client, _args->getHost(), "491", _args->getUsernameById(client), *words.begin()));
	password = *++iter;
	// wrong password, sends error
	if (password != "admin")
		return (send_message(client, _args->getHost(), "464", _args->getUsernameById(client), *words.begin()));
	// all arguments correct, change type of user
	else
	{
		_args->setTypeUser(2, client);
		return (send_message(client, _args->getHost(), "381", _args->getUsernameById(client), *words.begin()));
	}
	return (1);
}

int kick_user(ft_irc::Args *_args, std::list<std::string> words, int client)
{
	std::list<std::string>::iterator iter;
	std::list<ft_irc::Channel*>::iterator iter_channel;
	std::string channel;
	std::string user;
	int id_user;

	// bad size of parameters, send error
	if (words.size() != 3)
		return (send_message(client, _args->getHost(), "461", _args->getUsernameById(client), *words.begin()));
	// user not operator, send error
	if (_args->getTypeUserById(client) != 2)
		return (send_message(client, _args->getHost(), "482", _args->getUsernameById(client), *words.begin()));
	iter = words.begin();
	channel = *++iter;
	// removing first character if # or $
	if (channel[0] == '#' || channel[0] == '$')
		channel = channel.substr(1, channel.size());
	user = *++iter;
	user = clean_word(user, "\n");
	// user not found, send error
	if (_args->getIdByUsername(user) == -1)
		return (send_message(client, _args->getHost(), "442", _args->getUsernameById(client), channel));
	// iterate all channel list, finding the channel
	iter_channel = _args->channels_list.begin();
	while (iter_channel != _args->channels_list.end())
	{
		if ((*iter_channel)->getName() == channel)
		{
			// user found in channel
			if ((*iter_channel)->searchAndDeleteUser(_args->getIdByUsername(user)) == 1)
			{
				// send message to user kicked
				id_user = _args->getIdByUsername(user);
				std::string part_message = ":" + _args->getNicknameById(id_user) + " PART #" + channel + " You have been kicked.\r\n";
				send(id_user, part_message.c_str(), part_message.size(), 0);
				// send message to oper who kicked the user from the channel
				std::string message = ":" + _args->getNicknameById(client) + "!" + _args->getUsernameById(client) + "@" + _args->getHost()
				+ " User kicked \r\n";
				return (send(client, message.c_str(), message.size(), 0));
			}
			// user not found in channel, return error
			else
				return (send_message(client, _args->getHost(), "406", _args->getUsernameById(client), user));
		}
		iter_channel++;
	}
	// channel not found, return error
	return (send_message(client, _args->getHost(), "403", _args->getUsernameById(client), channel));
}

//send a private message without replies
int		notice_command(ft_irc::Args *_args, int client, std::list<std::string> words)
{
	std::list<std::string>::iterator iter;
	std::string nickname;
	std::string message;
	std::string complete_message;
	int id_nickname;

	//wrong number of parameters
	if (words.size() < 3)
		return (1);
	iter = words.begin();
	nickname = *++iter;
	// wrong nickname
	if ((id_nickname = _args->getIdByNickname(nickname)) == -1)
		return (1);
	message = message_to_send(words);
	// mute words
	message = _args->searchAndReplaceWords(message);
	// wrong message
	if (message == "411")
		return (1);
	// all is ok, send message to nickname user
	else
	{
		complete_message = ":" + _args->getNicknameById(client) + "!" + _args->getUsernameById(client)
    	+ "@" + _args->getHost() + " NOTICE " + nickname + " " + message + "\r\n";
		send (id_nickname, complete_message.c_str(), complete_message.size(), 0);
		return (1);
	}
}

int		kill_command(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args, int client, std::list<std::string> words)
{
	std::list<std::string>::iterator iter;
	std::string nickname;
	std::string message;
	int id_username;

	// wrong number of parameters, send error message
	if (words.size() <= 2)
		return (send_message(client, _args->getHost(), "461", _args->getUsernameById(client), *words.begin()));
	iter = words.begin();
	nickname = *++iter;
	// user is not operator, send error
	if (_args->getTypeUserById(client) != 2)
		return (send_message(client, _args->getHost(), "481", _args->getUsernameById(client), "no parameter"));
	// wrong nickname, send error
	if ((id_username = _args->getIdByNickname(nickname)) == -1)
		return (send_message(client, _args->getHost(), "401", _args->getUsernameById(client), nickname));
	// join message words from list to string
	message = message_to_send(words);
	// create full message to send to the kicked user
	message = ":" + _args->getNicknameById(id_username) + "!" + _args->getUsernameById(id_username) + "@" + _args->getHost()
	+ " You are kicked from the server: " + message + "\r\n";
	send(id_username, message.c_str(), message.size(), 0);
	// kick user from the server
	exit_irc(_args, _sock_args, id_username);
	// confirm user is kicked to the operator
	message = ":" + _args->getNicknameById(client) + "!" + _args->getUsernameById(client) + "@" + _args->getHost()
	+ " User: " + nickname + " kicked from the server!\r\n";
	send(client, message.c_str(), message.size(), 0);
	return (1);
}

int partial_command(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args, std::list<std::string> words, std::string to_send, int i, 
int nbytes)
{
	_args->setPartialCmdById(i, to_send);
	words = ft_split(_args->getPartialCmdById(i), ' ');
	if (checking_words_to_send(_args, _sock_args, words, i) == 0 &&
	_args->getIdChannelByIdUser(i) != 0)
		send_all_client(_args, _sock_args, nbytes, _args->getPartialCmdById(i), i);
	_args->erasePartialCmdById(i);
	return (i);
}