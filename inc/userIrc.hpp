#ifndef USERIRC_HPP
# define USERIRC_HPP

#include <iostream>

namespace ft_irc
{
class User
{
	private:
		int			id;
		int			type_user;
		std::string username;
		std::string nickname;
		int			state;
		int			channel;
	public:
		//Coplien
		User();
		User(int id);
		User(int id, std::string username, std::string nickname);
		User(User const &copy);
		User const &operator=(User const &copy);
		~User();
		//getters
		int getId();
		int getState();
		int getType();
		int getChannel();
		std::string getUsername();
		std::string getNickname();
		//setters
		void setId(int id);
		void setUsername(std::string _username);
		void setNickname(std::string _nickname);
		void setState(int _state);
		void setType(int _type);
		void setChannel(int _channel);
};
}
#endif