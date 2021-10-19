#include "../inc/socket.hpp"

ft_irc::Sock_args::Sock_args()
{}
ft_irc::Sock_args::Sock_args(struct sockaddr_storage _their_addr, socklen_t _addr_size,
int _newfd, int _sockfd, int _fdmax, fd_set _master, fd_set _fdreads)
{
    this->their_addr = _their_addr;
    this->addr_size = _addr_size;
    this->newfd = _newfd;
    this->sockfd = _sockfd;
    this->master = _master;
    this->fdreads = _fdreads;
}
ft_irc::Sock_args::Sock_args(Sock_args const &copy)
{
    this->their_addr = copy.their_addr;
    this->addr_size = copy.addr_size;
    this->newfd = copy.newfd;
    this->sockfd = copy.sockfd;
    this->master = copy.master;
    this->fdreads = copy.fdreads;
}
ft_irc::Sock_args &ft_irc::Sock_args::operator=(Sock_args const &copy)
{
    this->their_addr = copy.their_addr;
    this->addr_size = copy.addr_size;
    this->newfd = copy.newfd;
    this->sockfd = copy.sockfd;
    this->master = copy.master;
    this->fdreads = copy.fdreads;
    return (*this);
}

ft_irc::Sock_args::~Sock_args(){}