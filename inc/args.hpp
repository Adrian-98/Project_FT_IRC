#ifndef ARGS_HPP
# define ARGS_HPP

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/select.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include "userIrc.hpp"
#include <list>
#include <vector>
#include "socket.hpp"
#include <map>
#include "channel.hpp"

namespace ft_irc
{
class Args
{
    private:
        std::string host;
        std::string port_network;
        std::string password_network;
        std::string port;
        std::string password;
        std::string _parsing_net;
        std::vector<std::string> channels;
        std::vector<std::string> mute_words;
        std::map<int, std::string> partial_cmds;
    public:
        std::list<ft_irc::User*> user_list;
        std::list<ft_irc::Channel *> channels_list;
        //coplien
        Args();
        Args(std::string _host, std::string _port_network, std::string _psw_network, std::string _port, std::string _password);
        ~Args();
        Args &operator=(Args const &copy);
        Args(Args const &copy);
        //getters
        std::string getHost();
        std::string getPortNetwork();
        std::string getPasswdNetwork();
        std::string getPort();
        std::string getPasswd();
        std::string getParsingNet();
        std::string getPartialCmdById(int _id);
        //setters
        void setHost(std::string _host);
        void setPortNetwork(std::string _PortNetwork);
        void setPasswdNetwork(std::string _passwdNetwork);
        void setPort(std::string _port);
        void setPasswd(std::string _passwd);
        void setParsingNet(std::string _parsingNet);
        void setPartialCmdById(int _id, std::string _cmd);
        //list functions
        std::string getNicknameById(int id);
        std::string getUsernameById(int id);
        void addUserToList(ft_irc::User *_user);
        std::list<ft_irc::User*>::iterator listBegin();
        std::list<ft_irc::User*>::iterator listEnd();
        void removeFromList(int client);
        int getIdByNickname(std::string _nickname);
        int getIdByUsername(std::string _username);
        int getStateById(int _id);
        int getTypeUserById(int _id);
        ft_irc::User getUserById(int _id);
        void setState(int _state, int _id);
        void setUsernameById(std::string _username, int _id);
        void setNicknameById(std::string _nickname, int _id);
        void setTypeUser(int _type, int _id);
        std::string getPasswdByChannel(std::string _channelName);
        int isUserBanned(std::string _channelName, int _clientId);
        //vector functions
        void pushWordToVector(std::string _word);
        std::string searchAndReplaceWords(std::string _words);
        void popWordFromVector(std::string _word);
        void printVector();
        void erasePartialCmdById(int _id);
        int checkingPartialCmdById(int _id);
        //channel functions
        void setChannelById(int _id, std::string channel);
        void pushChannelByName(std::string _name);
        int getIdChannelByName(std::string _name);
        bool are_same_channel(int receiver, int sender);
        int getIdChannelByIdUser(int _id);
        bool searchChannelByName(std::string _name);
        void showChannelsToId(int _id);
        ft_irc::Channel *getChannelByName(std::string _channelName);
        //signals
        void mySigint();
        static void static_mySigint(int sign);
        std::list<ft_irc::User*>::iterator getBeginList();
        //print arguments
        void printingArgs();
};
}
#endif