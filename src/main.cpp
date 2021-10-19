#include "../inc/args.hpp"
#include <list>
#include <sstream> 
#include <fcntl.h>
#include "../inc/lib_irc.hpp"
#define GRN   "\x1B[32m"

int _signals_var = 0;

void send_all_client(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args, int nbytes, std::string to_send, int socket_sending)
{
    int j;
    std::string name;
}

void signals(int signal)
{
    if (signal == SIGINT)
    {
        //desconectar socket y conexione aqui!!!
        _signals_var = 1;
        std::cout << "losing server..." << std::endl;
    }
}

int creating_user(ft_irc::Args *_args, int newfd, std::string received)
{
    char welcome[] = "Welcome to the Internet Relay Network\n";

    if ((received.find("NICK") < received.size() || received.find("nick") < received.size()) ||
    received.find("USER") < received.size() || received.find("user") < received.size())
    {
        received = parsing_welcome_message(_args, received, newfd);
        send(newfd, received.c_str(), received.size(), 0);
    }
    // if not info is from nc
    else
    {
        send(newfd, welcome, strlen(welcome), 0);
        initialize_user(_args, newfd);
    }
    return (0);
}

void new_client(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args)
{
    int newfd;
    char buffer[1024];
    char welcome[39] = "Welcome to the Internet Relay Network\n";
    int nbytes;
    std::string received;

    _sock_args->addr_size = sizeof _sock_args->their_addr;
    // accept new client
    newfd = accept(_sock_args->sockfd, (struct sockaddr *)&_sock_args->their_addr, &_sock_args->addr_size);
    initialize_user(_args, newfd);
    // add new user to socket master, and set the maxclient to the new one
    if (newfd > _sock_args->fdmax)
        _sock_args->fdmax = newfd;
    FD_SET(newfd, &_sock_args->master);
}

void read_fd(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args)
{
    int i;
    int state;

    i = 0;
    while (i <= _sock_args->fdmax)
    {
        if (FD_ISSET(i, &_sock_args->fdreads))
        {
            if (i == _sock_args->sockfd)
                new_client(_args, _sock_args);
            else
            {
                char buffer[1024];
                int nbytes;

                nbytes = recv(i, buffer, 1024, 0);
                //mensajes erroneos y vacio
                if (nbytes <= 0)
                {
                    memset(&buffer, 0, sizeof(buffer));
                    close(i);
                    FD_CLR(i, &_sock_args->master);
                    _args->removeFromList(i);
                }
                if (nbytes > 0 && nbytes < 1023)
                    buffer[nbytes] = '\0';
                std::string to_send = buffer;
                //std::cout<<"BUFFER FROM WEECHAT: ["<<to_send<<"]"<<std::endl;
                if (_args->getStateById(i) == 3)
                    creating_user(_args, i, to_send);
                std::list<std::string> words = ft_split(to_send, ' ');
                // comando partido
                if (to_send.find("\n") > to_send.size())
                    _args->setPartialCmdById(i, to_send);
                // comando completo per existe ya un comando partido, por tanto final del comando
                else if (to_send.find("\n") < to_send.size() && (_args->checkingPartialCmdById(i) == 1))
                {
                    _args->setPartialCmdById(i, to_send);
                    words = ft_split(_args->getPartialCmdById(i), ' ');
                    if (checking_words_to_send(_args, _sock_args, words, i) == 0 &&
                    _args->getIdChannelByIdUser(i) != 0)
                        send_all_client(_args, _sock_args, nbytes, _args->getPartialCmdById(i), i);
                    _args->erasePartialCmdById(i);
                }
                // mensaje correcto
                else if (checking_words_to_send(_args, _sock_args, words, i) == 0 &&
                _args->getIdChannelByIdUser(i) != 0)
                    send_all_client(_args, _sock_args, nbytes, to_send, i);
            }
        }
        i++;
    }
}

void while_loop(ft_irc::Args *_args, ft_irc::Sock_args *_sock_args)
{
    _sock_args->fdreads = _sock_args->master;
    std::cout<<"Esperando mensaje"<<std::endl;
    if (_signals_var == 0)
        select(_sock_args->fdmax + 1, &_sock_args->fdreads, NULL, NULL, NULL);
    std::cout<<"Mensaje recibido"<<std::endl;
    if (_signals_var == 0)
        read_fd(_args, _sock_args);
}

int creating_irc_server(ft_irc::Args *_args)
{
    struct addrinfo hints;
    struct addrinfo *res;
    ft_irc::Sock_args _sock_args;

    signal(SIGINT, &signals);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(_args->getHost().c_str(), _args->getPortNetwork().c_str(), &hints, &res);
    _sock_args.sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(_sock_args.sockfd, res->ai_addr, res->ai_addrlen);
    listen(_sock_args.sockfd, 10);
    FD_ZERO(&_sock_args.fdreads);
    FD_ZERO(&_sock_args.master);
    FD_SET(_sock_args.sockfd, &_sock_args.master);
    _sock_args.fdmax = _sock_args.sockfd;
    _args->pushChannelByName("general_chat");
    while (_signals_var == 0)
         while_loop(_args, &_sock_args);
    freeaddrinfo(res);
    return 0;
}

int main(int argc, char **argv)
{
    ft_irc::Args _args;

    if (argc != 4)
        std::cout<<"Error: number of arguments."<<argc<<std::endl;
    else if (parse_args(argv, &_args) != 0)
        std::cout<<"Error: Bad arguments."<<std::endl;
    else
    {
        _args.printingArgs();
        creating_irc_server(&_args);
    }
    //system("leaks ircserv");
    return (0);
}
