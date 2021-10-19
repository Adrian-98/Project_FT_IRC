#include "../inc/lib_irc.hpp"

std::string message_to_send(std::list<std::string> words_list)
{
	std::list<std::string>::iterator iter = words_list.begin();
	std::string word;
	std::string complete_message;
	int flag = 0;
	// jumping command word
	iter++;
	while (iter != words_list.end())
	{
		word = *iter;
		if (word.find(":") == 0)
		{
			word = word.substr(1, word.size());
			if (word.find("\n") < word.size())
				word.replace(word.find("\n"), 1, "");
			complete_message = word;
			flag = 1;
			iter++;
		}
		if (flag == 1 && iter != words_list.end())
			complete_message = complete_message + " " + *iter;
		if (iter != words_list.end())
			iter++;
	}
	if (flag == 1)
		return (complete_message);
	else
		return ("411");
}

std::string whose_to_send(std::list<std::string> words_list)
{
	std::list<std::string>::iterator iter = words_list.begin();
	std::string word;
	std::string second_word;

	if (words_list.size() > 2)
	{
		word = *++iter;
		second_word = *++iter;
		if (second_word.find(":") < second_word.size())
			return (word);
		else
			return ("411");
	}
	else
		return ("411");
}

int check_receiver(std::string receiver)
{
	if (receiver[0] == '#' || receiver[0] == '$') //is a channel
		return (1);
	else
		return (0);
}

std::string return_full_message(ft_irc::Args *_args, int client, int receiver, std::string channel, std::string message)
{
	std::string complete_message;

	if (message.find("\n") < message.size())
		message.replace(message.find("\n"), 1, "");
	complete_message = ":" + _args->getNicknameById(client) + "!" + _args->getUsernameById(client)
    + "@" + _args->getHost() + " PRIVMSG #" + channel + " :" + message + "\r\n";
	return (complete_message);
}

int channel_exist(std::__1::list<ft_irc::Channel *> list, ft_irc::Channel *to_search)
{
    std::list<ft_irc::Channel *>::iterator iter = list.begin();

    if (list.size() == 0)
        return (0);
    while (iter != list.end())
    {
        if (*iter == to_search)
            return (1);
        iter++;
    }
    return (0);
}

int send_to_users_of_channel(ft_irc::Args *_args, int client, std::string channel_name, std::string message)
{
	std::list<int>::iterator iter;

	iter = _args->getChannelByName(channel_name)->user_list.begin();
	while (iter != _args->getChannelByName(channel_name)->user_list.end())
	{
		//create the full message to send
		if ((*iter) != client)
			send(*iter, message.c_str(), message.size(), 0);
		iter++;
	}
	return (0);
}