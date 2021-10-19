#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "args.hpp"
namespace ft_irc
{
class Sock_args
{
    public:
        struct sockaddr_storage	their_addr;
        socklen_t	addr_size;
        int			newfd;
        int			sockfd;
        int			fdmax;
        fd_set		master;
        fd_set		fdreads;
    public:
        Sock_args();
        Sock_args(struct sockaddr_storage _their_addr, socklen_t _addr_size,
        int _newfd, int _sockfd, int _fdmax, fd_set _master, fd_set _fdreads);
        Sock_args(Sock_args const &copy);
        Sock_args &operator=(Sock_args const &copy);
        ~Sock_args();
};
}
#endif