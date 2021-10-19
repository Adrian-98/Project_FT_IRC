#include "../inc/lib_irc.hpp"

int parsing_network_errors(char *network)
{
    int i = 0;
    int colons = 0;

    i++;
    if (network[0] == ':')
        return (1);
    while (network[i])
    {
        if (network[i] == ':')
            colons++;
        i++;
    }
    if (colons != 2 || network[i] == ':')
        return (1);
    return (0);
}

int adding_to_class(std::list<std::string> list_network, ft_irc::Args *_args)
{
    std::list<std::string>::iterator iter = list_network.begin();
    int i = 0;
    if (list_network.size() != 3)
        return (1);
    _args->setHost((*iter++));
    _args->setPortNetwork(*iter++);
    _args->setPasswdNetwork(*iter);
    return (0);
}

int parsing_network(char *network, ft_irc::Args *_args)
{
    std::list<std::string> list_network;
    std::string word;
    std::string net_string;
    int end;
    int start = 0;
    int n_word = 1;

    if (parsing_network_errors(network) != 0)
        return (1);
    net_string = std::string(network);
    end = net_string.find(":");
    while (end != -1)
    {
        word = net_string.substr(start, end - start);
        if (word != "\0")
            list_network.push_back(word);
        start = end + 1;
        end = net_string.find(":", start);
        n_word++;
    }
    word = net_string.substr(start, end);
    list_network.push_back(word);
    if (adding_to_class(list_network, _args) != 0)
        return (1);
    return (0);
}

int parse_args(char **args, ft_irc::Args *_args)
{
    if (parsing_network(args[1], _args) != 0)
        return (1);
    if (atoi(args[1]) != 0)
        _args->setPort(args[2]);
    else
        return (1);
    _args->setPasswd(std::string(args[3]));
    return (0);
}