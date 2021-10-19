#include "../inc/lib_irc.hpp"
#include <iostream>

int push_channel_to_list(ft_irc::Args *_args, int client, std::string channel_name, std::string password)
{
	ft_irc::Channel *_channel = _args->getChannelByName(channel_name);
	if (_channel != NULL)
	{
		_channel->user_list.push_back(client);
		return (0);
	}
	else
		return (1);
}