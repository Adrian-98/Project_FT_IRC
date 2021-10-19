#include "../inc/lib_irc.hpp"

int checking_words_to_send(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args, std::list<std::string> words, int client)
{
    //std::string word;
    std::string command;
    // check state user
    if (check_state_user(_args, client, words) != 0)
        return (1);
    command = *words.begin();
    // removing / from command
    if (command[0] == '/')
        command = command.substr(1, command.size());
    else
        command = command.substr(0, command.size());
    // to lower command word
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    // search command options 
    std::cout<<"command: ["<<command<<"]"<<std::endl;
    if (command == "privmsg" || command == "msg")
        return (send_private_message(_args, words, client));
    else if (command == "mute")
        return (mute_words(_args, words, client));
    else if (command == "unmute")
        return (unmute_words(_args, words, client));
    else if (command == "kick")
        return (kick_user(_args, words, client));
    else if (command == "kill")
        return (kill_command(_args, _sock_args, client, words));
    else if (command == "join")
        return (join_command(_args, words, client));
    else if (command == "part")
        return (leave_channel(_args, words, client));
    else if (command == "quit")
        return (exit_irc(_args, _sock_args, client));
    else if (command == "channels")
        return (show_all_channels(_args, client));
    else if (command == "oper")
        return (oper_command(_args, client, words));
    else if (command == "notice")
        return (notice_command(_args, client, words));
    return (0);
}