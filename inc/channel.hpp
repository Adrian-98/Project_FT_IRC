#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <list>
#include "userIrc.hpp"
namespace ft_irc
{
class Channel
{
	private:
		std::string name;
		std::string password;
		int			limit;

	public:
		std::list<int> user_list;
		std::list<int> ban_id_list;
		
		Channel();
		Channel(std::string name, std::string password, int limit);
		Channel(std::string name);
		~Channel();
		//getters
		std::string getName();
		std::string getPasswd();
		int			getLimit();
		//setters
		void setName(std::string _name);
		void setPasswd(std::string _passwd);
		void setLimit(int _limit);
		//operational functions
		int searchAndDeleteUser(int client);
};
}
#endif