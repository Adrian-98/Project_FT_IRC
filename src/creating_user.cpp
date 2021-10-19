#include "../inc/args.hpp"
#include "../inc/lib_irc.hpp"

void initialize_user(ft_irc::Args *_args, int newfd)
{
	ft_irc::User *_user = new ft_irc::User(newfd);
	_args->addUserToList(_user);
}

void initialize_complete_user(ft_irc::Args *_args, int newfd, std::string _username)
{
	ft_irc::User *_user = new ft_irc::User(newfd, _username, _username);
	_args->addUserToList(_user);
}

int	insert_password_beta(ft_irc::Args *_args, int socket_user, std::list<std::string> words)
{
	std::string password;

	if (words.size() != 2)
		return (send_message(socket_user, _args->getHost(), "461", "none", *words.begin()));
	password = *++words.begin();
	if (password.find("\n") < password.length())
        password = password.substr(0, password.find("\n"));
	if (password != _args->getPasswdNetwork() && password != "admin")
		return (send_message(socket_user, _args->getHost(), "1004", "none", password));
	else if (password == _args->getPasswdNetwork() || password == "admin")
	{
		if (password == "admin")
			_args->setTypeUser(2, socket_user);
		send(socket_user, "Correct password, insert command user\r\n", 39, 0);
		_args->setState(2, socket_user);
		return (1);
	}
	return (0);
}

int check_name_already_registerd(ft_irc::Args *_args, std::string name, int _case)
{
	std::list<ft_irc::User*>::iterator iter;

	iter = _args->user_list.begin();
	while (iter != _args->user_list.end())
	{
		if ((*iter)->getUsername() == name && _case == 1)
			return (1);
		else if ((*iter)->getNickname() == name && _case == 2)
			return (1);
		iter++;
	}
	return (0);
}

int insert_user_beta(ft_irc::Args *_args, int socket_user, std::list<std::string> words)
{
	std::string user;

	if (words.size() != 2)
		return (send_message(socket_user, _args->getHost(), "461", "none", *words.begin()));
	user = *++words.begin();
	if (user.find("\n") < user.length())
        user = user.substr(0, user.find("\n"));
	std::cout<<"user: ["<<user<<"]"<<std::endl;
	// search user in list of users
	if (_args->getIdByUsername(user) >= 0)
		return(send_message(socket_user, _args->getHost(), "433", "none", *words.begin()));
	else
	{
		send(socket_user, "Username is registered. insert command nickname:\r\n", 51, 0);
		_args->setUsernameById(user, socket_user);
		_args->setState(1, socket_user);
		return (1);
	}
	return (0);
}

int insert_nick_beta(ft_irc::Args *_args, int socket_user, std::list<std::string> words)
{
	std::string nick;

	if (words.size() != 2)
		return (send_message(socket_user, _args->getHost(), "461", "none", *words.begin()));
	nick = *++words.begin();
	if (nick.find("\n") < nick.length())
        nick = nick.substr(0, nick.find("\n"));
	std::cout<<"nick: ["<<nick<<"]"<<std::endl;
	// search user in list of users
	if (_args->getIdByNickname(nick) >= 0)
		return(send_message(socket_user, _args->getHost(), "433", "none", *words.begin()));
	else
	{
		send(socket_user, "Nickname is registered. user completed\r\n", 40, 0);
		_args->setNicknameById(nick, socket_user);
		_args->setState(0, socket_user);
		return (1);
	}
	return (0);
}

int check_state_user(ft_irc::Args *_args, int socket_user, std::list<std::string> words)
{
	std::string command_word;

	if (_args->getStateById(socket_user) == 0)
		return (0);
	command_word = *words.begin();
	// checking if command has / and convert to lower case
	if (command_word[0] == '/')
		command_word = command_word.substr(1, command_word.size());

	std::transform(command_word.begin(), command_word.end(), command_word.begin(), ::tolower);
	// check if user is well registered
	if (_args->getStateById(socket_user) == 3 && command_word != "pass")
		return (send_message(socket_user, _args->getHost(), "1001", "none", "none"));
	else if (_args->getStateById(socket_user) == 2 && command_word != "user")
		return (send_message(socket_user, _args->getHost(), "1002", "none", "none"));
	else if (_args->getStateById(socket_user) == 1 && command_word != "nick")
		return (send_message(socket_user, _args->getHost(), "1003", "none", "none"));
	// insert password
	if (_args->getStateById(socket_user) == 3 && command_word == "pass")
		return (insert_password_beta(_args, socket_user, words));
	if (_args->getStateById(socket_user) == 2 && command_word == "user")
		return (insert_user_beta(_args, socket_user, words));
	if (_args->getStateById(socket_user) == 1 && command_word == "nick")
		return (insert_nick_beta(_args, socket_user, words));
	return (0);
}