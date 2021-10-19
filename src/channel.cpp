#include "../inc/channel.hpp"

ft_irc::Channel::Channel()
{}
ft_irc::Channel::Channel(std::string _name, std::string _passwd, int _limit)
{
	this->name = _name;
	this->password = _passwd;
	this->limit = _limit;
}
ft_irc::Channel::Channel(std::string _name)
{
	this->name = _name;
	this->password = "none";
	this->limit = 10;
}
ft_irc::Channel::~Channel()
{}
//getters
std::string ft_irc::Channel::getName()
{
	return (this->name);
}
std::string ft_irc::Channel::getPasswd()
{
	return (this->password);
}
int			ft_irc::Channel::getLimit()
{
	return (this->limit);
}
//setters
void ft_irc::Channel::setName(std::string _name)
{
	this->name = _name;
}
void ft_irc::Channel::setPasswd(std::string _passwd)
{
	this->password = _passwd;
}
void ft_irc::Channel::setLimit(int _limit)
{
	this->limit = _limit;
}
//functions
int ft_irc::Channel::searchAndDeleteUser(int client)
{
	std::list<int>::iterator iter;
	int flag = 0;
	iter = user_list.begin();
	while (iter != user_list.end())
	{
		if (*iter == client)
		{
			user_list.erase(iter);
			flag = 1;
			break ;
		}
		iter++;
	}
	iter = ban_id_list.begin();
	while (iter != ban_id_list.end())
	{
		if (*iter == client)
		{
			ban_id_list.erase(iter);
			break ;
		}
		iter++;
	}
	return (flag);
}