#include "../inc/lib_irc.hpp"
#include "../inc/userIrc.hpp"

std::string get_username_from_recv(std::string recv_message, char character)
{
    if (recv_message.find("NICK") < recv_message.size())
    {
        recv_message = recv_message.substr(recv_message.find("NICK") + 5, recv_message.size());
        recv_message = recv_message.substr(0, recv_message.find(" "));
    }
    else if (recv_message.find("USER") < recv_message.size())
    {
        recv_message = recv_message.substr(recv_message.find("USER") + 5, recv_message.size());
        recv_message = recv_message.substr(0, recv_message.find(" "));
    }
    if (recv_message.find("\r\n") < recv_message.size())
        recv_message = recv_message.substr(0, recv_message.find("\r\n"));
    return (recv_message);
}

std::string parsing_welcome_message(ft_irc::Args *_args, std::string recv_message, int newfd)
{
    std::string username;
    username = get_username_from_recv(recv_message, ' ');
	_args->setUsernameById(username, newfd);
	_args->setNicknameById(username, newfd);
	_args->setState(0, newfd);
    //initialize_complete_user(_args, newfd, username);
    recv_message = ":" + _args->getHost() + " 001 " + username + RPL_WELCOME(username);
    return (recv_message);
}

std::string create_message(std::string host, std::string num, std::string username, std::string receiver)
{
	std::string first_part;
	std::stringstream ss;
	int error;

	ss << num;
	ss >> error;
	switch(error)
	{
		case 411 :
			return first_part + ERR_NORECIPIENT(receiver);
		case 403 :
			return first_part + ERR_NOSUCHCHANNEL(receiver);
		case 407 :
			return first_part + ERR_TOOMANYTARGETS(receiver);
		case 475 :
			return first_part + ERR_BADCHANNELKEY(receiver);
		case 461 :
			return first_part + ERR_NEEDMOREPARAMS(receiver);
		case 353 :
			return first_part + RPL_NAMREPLY(receiver, "@dav bir");
		case 366 :
			return first_part + RPL_ENDOFNAMES(receiver);
		case 381 :
			return first_part + RPL_YOUREOPER();
		case 401 :
			return first_part + ERR_NOSUCHNICK(receiver);
		case 433:
			return first_part + ERR_NICKNAMEINUSE(receiver);
		case 442 :
			return first_part + ERR_NOTONCHANNEL(receiver);
		case 464 :
			return first_part + ERR_PASSWDMISMATCH();
		case 481 :
			return first_part + ERR_NOPRIVILEGES();
		case 482 :
			return first_part + ERR_CHANOPRIVSNEEDED(receiver);
		case 491 :
			return first_part + ERR_NOOPERHOST();
		case 1000 : // joining channel
			return first_part + ": joining channel " + receiver + "\r\n";
		case 1001 :
			return first_part + ERR_NEED_PASSWD();
		case 1002 :
			return first_part + ERR_NEED_USERNAME();
		case 1003 :
			return first_part + ERR_NEED_NICKNAME();
		case 1004 :
			return first_part + ERR_BAD_PASSWORD(receiver);
		default :
			std::cout<<"falta enviar error"<<std::endl;
			return ("error");
	}
}

int send_message(int client, std::string host, std::string n_error, std::string username, std::string receiver)
{
	std::string message;
	message = create_message(host, n_error, username, receiver);
	send(client, message.c_str(), message.size(), 0);
	return (1);
}
