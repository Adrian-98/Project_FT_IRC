#include "../inc/lib_irc.hpp"


int send_to_user(ft_irc::Args *_args, int client, std::string receiver, std::list<std::string> to_send_splitted)
{
	std::string message;
	std::string complete_message;
	int id_receiver;

	// if receiver is error 411, send error message
	if (receiver == "411")
        return (send_message(client, _args->getHost(), "411", _args->getUsernameById(client), "none"));
	// parsing message to send
	message = message_to_send(to_send_splitted);
	// if message is error 411, send error message
	if (message == "411")
        return (send_message(client, _args->getHost(), "411", _args->getUsernameById(client), receiver));
	// mute words
	message = _args->searchAndReplaceWords(message);
	// creating completed message to send
	complete_message = ":" + _args->getNicknameById(client) + "!" + _args->getUsernameById(client)
    + "@" + _args->getHost() + " PRIVMSG " + receiver + " " + message + "\r\n";
	std::cout<<"Complete message: ["<<complete_message<<"]"<<std::endl;
	// searching the id from the receiver
	id_receiver = _args->getIdByNickname(receiver);
	// id not found, send error
	if (id_receiver == -1)
        return (send_message(client, _args->getHost(), "411", _args->getUsernameById(client), receiver));
	// id is found, send message
    else
        send (id_receiver, complete_message.c_str(), complete_message.size(), 0);
	return (1);
}

int send_to_channel(ft_irc::Args *_args, int client, std::string channel_name, std::list<std::string> to_send_splitted)
{
	std::string message;
	std::string complete_message;
	std::list<int>::iterator iter;
	ft_irc::Channel *channel;
	// remove the first letter of channel name
	if (channel_name[0] == '#' || channel_name[0] == '$')
		channel_name = channel_name.substr(1, channel_name.size());
	// channel found in channel_list, send message to all users;
	if (channel_exist(_args->channels_list, _args->getChannelByName(channel_name)) == 1)
	{
		channel = _args->getChannelByName(channel_name);
		// if user is not in channel
		if (search_in_list(channel->user_list, client) == 0)
			return (1);
		// parsing message from list, to send it
		message = message_to_send(to_send_splitted);
		// message is 411 error, send error
		if (message == "411")
        	return (send_message(client, _args->getHost(), "411", _args->getUsernameById(client), channel_name));
		// mute words
		message = _args->searchAndReplaceWords(message);
		// create an iter, to send message to every user from the list, except who sends it
		iter = _args->getChannelByName(channel_name)->user_list.begin();
		// iterate the list
		while (iter != _args->getChannelByName(channel_name)->user_list.end())
		{
			//create the full message to send
			complete_message = return_full_message(_args, client, *iter, channel_name, message);
			if ((*iter) != client)
				send(*iter, complete_message.c_str(), complete_message.size(), 0);
			iter++;
		}
		return (1);
	}
	// channel not found, send error message
	return (1);
}

int send_private_message(ft_irc::Args *_args, std::list<std::string> words, int client)
{
    std::string receiver;

    if (words.size() <= 2)
        return (send_message(client, _args->getHost(), "461", _args->getUsernameById(client), *words.begin()));
    receiver = whose_to_send(words);
    if (receiver == "411")
        return (send_message(client, _args->getHost(), "411", _args->getUsernameById(client), *words.begin()));
    if (check_receiver(receiver) == 1) // is a channel
        return (send_to_channel(_args, client, receiver, words));
    else
        return (send_to_user(_args, client, receiver, words));
}