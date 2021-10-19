#include "../inc/lib_irc.hpp"
#include "../inc/args.hpp"

int timeout_user(ft_irc::Args *_args, std::string to_send, int client)
{
	send (client, "\x1B[31mAdmin: dont know how to timeout a user, sorry :(\n\x1B[0m", 56, 0);
	return (1);
}

int mute_words(ft_irc::Args *_args, std::list<std::string> words, int client)
{
	std::string message;
	std::list<std::string>::iterator iter;

	if (_args->getTypeUserById(client) != 2)
		return (send_message(client, _args->getHost(), "481", _args->getUsernameById(client), "no parameter"));
	if (words.size() <= 1)
		return (send_message(client, _args->getHost(), "481", _args->getUsernameById(client), *words.begin()));
	iter = words.begin();
	// jumping cmd word
	iter++;
	// pusing all the words to muted vector
    while (iter != words.end()) {
        _args->pushWordToVector(*iter);
		iter++;
    }
	// create message
	message = ":admin!admin@" + _args->getHost()
	+ " :\x1B[31m words muted.\n\x1B[0m";
	// send message
	send (client, message.c_str(), message.size(), 0);
	_args->printVector();
	return (1);
}

int unmute_words(ft_irc::Args *_args, std::list<std::string> words, int client)
{
	std::list<std::string>::iterator iter;
	std::string message;
	// splitting words
	iter = words.begin();
	iter++;
	// remove words from mute vector
    while (iter != words.end()) {
        _args->popWordFromVector(*iter);
        iter++;
    }
	// create message
	message = ":Admin!Admin@" + _args->getHost()
	+ " \x1B[31m:words unmuted.\n\x1B[0m";
	// send message
	send (client, message.c_str(), message.size(), 0);
	return (1);
}

int create_channel(ft_irc::Args *_args, int client, std::string channel_name, std::string password)
{
	ft_irc::Channel *chan = new ft_irc::Channel(channel_name, password, 10);
	if (chan->user_list.size() < 10)
		chan->user_list.push_back(client);
	_args->channels_list.push_back(chan);
	return(0);
}