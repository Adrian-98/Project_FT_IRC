#include "../inc/userIrc.hpp"

ft_irc::User::User(){}

//state 3 Falta contraseña
//state 2 Falta username
//state 1 Falta nickname
//state 0 todo ok
ft_irc::User::User(int _id)
{
	this->id = _id;
	this->state = 3;
	this->type_user = 1;
}

ft_irc::User::User(int _id, std::string _username, std::string _nickname)
{
	this->id = _id;
	this->username = _username;
	this->nickname = _nickname;
	this->state = 0;
	this->channel = 0;
	this->type_user = 1;
}

ft_irc::User::User(User const &copy)
{
	this->id = copy.id;
	this->username = copy.username;
	this->nickname = copy.nickname;
	this->state = copy.state;
	this->channel = copy.channel;
	this->type_user = copy.type_user;
}
ft_irc::User const &ft_irc::User::operator=(User const &copy)
{
	this->id = copy.id;
	this->username = copy.username;
	this->nickname = copy.nickname;
	this->state = copy.state;
	this->channel = copy.channel;
	this->type_user = copy.type_user;
	return (*this);
}
ft_irc::User::~User(){}
//getters
int ft_irc::User::getId()
{
	return (this->id);
}
int ft_irc::User::getState()
{
	return (this->state);
}
std::string ft_irc::User::getUsername()
{
	return (this->username);
}
std::string ft_irc::User::getNickname()
{
	return (this->nickname);
}
int ft_irc::User::getType()
{
	return (this->type_user);
}
int ft_irc::User::getChannel()
{
	return (this->channel);
}
//setters
void ft_irc::User::setState(int _state)
{
	this->state = _state;
}
void ft_irc::User::setId(int _id)
{
	this->id = _id;
}
void ft_irc::User::setUsername(std::string _username)
{
	this->username = _username;
}
void ft_irc::User::setNickname(std::string _nickname)
{
	this->nickname = _nickname;
}
void ft_irc::User::setType(int _type)
{
	this->type_user = _type;
}
void ft_irc::User::setChannel(int _channel)
{
	this->channel = _channel;
}