#ifndef LIB_IRC_HPP
# define LIB_IRC_HPP

# include "args.hpp"
#include <list>
#include <sstream>
#include <fcntl.h>
#define RPL_WELCOME(nick) (" :Welcome to the Internet Relay Network " + nick + "\r\n")
#define ERR_NORECIPIENT(command) (" :No recipient given (" + command + ")\r\n");
#define RPL_TOPIC(channel, subject) (channel + " :" + subject + "\r\n") // 332
#define RPL_NAMREPLY(channel, nick_list) (channel + " :" + nick_list + "\r\n") //353
#define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list\r\n") // 366
#define RPL_YOUREOPER() (":You are now an IRC operator\r\n") // 381
#define ERR_NOSUCHNICK(pseudo) (pseudo + " :No such nick or channel\r\n") //401
#define ERR_NOSUCHCHANNEL(channel) (channel + " :No such channel\r\n") //403
#define ERR_WASNOSUCHNICK(nickname) (nickname + " :There was no such nickname\r\n") //406
#define ERR_TOOMANYTARGETS(dest) (dest + ":Duplicate recipients. No message delivered\r\n") //407
#define ERR_NOTONCHANNEL(channel) (channel + " :You're not on that channel\r\n") // 442
#define ERR_NEEDMOREPARAMS(command) (command + " :Bad number of parameters\r\n") // 461
#define ERR_PASSWDMISMATCH() (":Password incorrect\r\n") // 464
#define ERR_BADCHANNELKEY(channel) (channel + " :Cannot join channel (+k)\r\n") // 475
#define ERR_NOPRIVILEGES() (":Permission Denied- You're not an IRC operator\r\n") // 481
#define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You're not channel operator\r\n") // 482
#define ERR_NOOPERHOST() (":incorrect username\r\n") // 491
#define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname/Username is already in use\r\n") // 433
// self commands
#define ERR_NEED_PASSWD() (": You need to insert password:\r\n"); // 1001
#define ERR_NEED_USERNAME() (": You need to insert username:\r\n"); // 1002
#define ERR_NEED_NICKNAME() (": You need to insert nickname:\r\n"); // 1003
#define ERR_BAD_PASSWORD(passwd) (": " + passwd + " Bad password, insert again!\r\n"); // 1004

int insert_password(ft_irc::Args *_args, int socket_user);
int parsing_network_errors(char *network);
int parsing_network(char *network, ft_irc::Args *_args);
int parse_args(char **args, ft_irc::Args *_args);
int send_private_message(ft_irc::Args *_args, std::list<std::string> words, int client);
std::string return_password(char *buff, int newfd);
void initialize_user(ft_irc::Args *_args, int newfd);
void create_user(ft_irc::Args *_args, int newfd);
int insert_nickname(ft_irc::Args *_args, int socket_user);
int insert_username(ft_irc::Args *_args,int socket_user);
int timeout_user(ft_irc::Args *_args, std::string to_send, int client);
int mute_words(ft_irc::Args *_args, std::list<std::string> words, int client);
int unmute_words(ft_irc::Args *_args, std::list<std::string> words, int client);
int kick_user(ft_irc::Args *_args, std::list<std::string> words, int client);
int checking_words_to_send(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args, std::list<std::string> words, int client);
//int create_channel(ft_irc::Args *_args, std::string to_send, int client);
int join_command(ft_irc::Args *_args, std::string to_send, int client);
int push_channel_to_list(ft_irc::Args *_args, int client, std::string channel_name, std::string password);
int show_commands(ft_irc::Args *_args, int client);
int show_all_channels(ft_irc::Args *_args, int client);
int leave_channel(ft_irc::Args *_args, std::list<std::string> words, int client);
int exit_irc(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args, int client);
std::string get_username_from_recv(std::string recv_message, char character);
std::string parsing_welcome_message(ft_irc::Args *_args, std::string recv_message, int newfd);
void initialize_complete_user(ft_irc::Args *_args, int newfd, std::string _username);
std::list<std::string> ft_split(std::string str, char splitter);
int send_message(int client, std::string host, std::string n_error, std::string username, std::string receiver);
int create_channel(ft_irc::Args *_args, int client, std::string channel_name, std::string password);
std::string create_message(std::string host, std::string num, std::string username, std::string receiver);
int join_command(ft_irc::Args *_args, std::list<std::string> words, int client);
std::string clean_word(std::string _word, std::string to_clean);
int send_to_user(ft_irc::Args *_args, int client, std::string receiver, std::list<std::string> to_send_splitted);
int send_to_channel(ft_irc::Args *_args, int client, std::string channel_name, std::list<std::string> to_send_splitted);
int send_to_users_of_channel(ft_irc::Args *_args, int client, std::string channel_name, std::string message);
int channel_exist(std::list<ft_irc::Channel *> list, ft_irc::Channel *to_search);
int check_receiver(std::string receiver);
std::string whose_to_send(std::list<std::string> words_list);
std::string message_to_send(std::list<std::string> words_list);
std::string return_full_message(ft_irc::Args *_args, int client, int receiver, std::string channel, std::string message);
template <typename T>
int search_in_list(std::list<T> list, T to_search);
int		oper_command(ft_irc::Args *_args, int client, std::list<std::string> words);
int		notice_command(ft_irc::Args *_args, int client, std::list<std::string> words);
int		kill_command(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args, int client, std::list<std::string> words);
int check_state_user(ft_irc::Args *_args, int socket_user, std::list<std::string> words);
void signals(int signal);
void send_all_client(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args, int nbytes, std::string to_send, int socket_sending);
int partial_command(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args, std::list<std::string> words, std::string to_send, int i, 
int nbytes);
void cleaning_socket(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args, int i, char *buffer);
#endif