#include "../inc/args.hpp"

ft_irc::Args::Args()
{

}
ft_irc::Args::Args(std::string _host, std::string _port_network, std::string _psw_network, std::string _port, std::string _password)
{
    this->host = _host;
    this->port_network = _port_network;
    this->password_network = _psw_network;
    this->port = _port;
    this->password = _password;
}
ft_irc::Args::~Args()
{
    std::list<ft_irc::User*>::iterator iter = user_list.begin();
    std::list<ft_irc::Channel*>::iterator iter_channel = channels_list.begin();

    while (iter != user_list.end())
    {
        close((*iter)->getId());
        delete *iter;
        iter++;
    }
    this->user_list.erase(this->user_list.begin(), this->user_list.end());
    while (iter_channel != channels_list.end())
    {
        delete *iter_channel;
        iter_channel++;
    }
    this->channels_list.erase(this->channels_list.begin(), this->channels_list.end());
}
ft_irc::Args &ft_irc::Args::operator=(Args const &copy)
{
    this->host = copy.host;
    this->port_network = copy.port_network;
    this->password_network = copy.password_network;
    this->port = copy.port;
    this->password = copy.password;
    return (*this);
}
ft_irc::Args::Args(Args const &copy)
{
    this->host = copy.host;
    this->port_network = copy.port_network;
    this->password_network = copy.password_network;
    this->port = copy.port;
    this->password = copy.password;
}

//getters
std::string ft_irc::Args::getHost()
{
    return (this->host);
}
std::string ft_irc::Args::getPortNetwork()
{
    return (this->port_network);
}
std::string ft_irc::Args::getPasswdNetwork()
{
    return (this->password_network);
}
std::string ft_irc::Args::getPort()
{
    return (this->port);
}
std::string ft_irc::Args::getPasswd()
{
    return (this->password);
}
std::string ft_irc::Args::getParsingNet()
{
    return (this->_parsing_net);
}
std::string ft_irc::Args::getPartialCmdById(int _id)
{
    std::map<int, std::string>::iterator iter = this->partial_cmds.find(_id);

    if (iter != this->partial_cmds.end())
        return (iter->second);
    else
        return (NULL);
}
int ft_irc::Args::checkingPartialCmdById(int _id)
{
    std::map<int, std::string>::iterator iter = this->partial_cmds.find(_id);

    if (iter != this->partial_cmds.end())
        return (1);
    else
        return (0);
}
//setters
void ft_irc::Args::setHost(std::string _host)
{
    this->host = _host;
}
void ft_irc::Args::setPortNetwork(std::string _PortNetwork)
{
    this->port_network = _PortNetwork;
}
void ft_irc::Args::setPasswdNetwork(std::string _passwdNetwork)
{
    this->password_network = _passwdNetwork;
}
void ft_irc::Args::setPort(std::string _port)
{
    this->port = _port;
}
void ft_irc::Args::setPasswd(std::string _passwd)
{
    this->password = _passwd;
}
void ft_irc::Args::setParsingNet(std::string _parsingNet)
{
    this->_parsing_net = _parsingNet;
}
void ft_irc::Args::setPartialCmdById(int _id, std::string _cmd)
{
    std::map<int, std::string>::iterator iter = this->partial_cmds.find(_id);
    std::string command;

    if (iter != this->partial_cmds.end())
    {
        command = this->getPartialCmdById(_id) + _cmd;
        if (command.find("\n") < command.length())
            command = command.substr(0, command.find("\n"));
        iter->second = command;
    }
    else
        this->partial_cmds.insert(std::pair<int, std::string>(_id, _cmd));
}
void ft_irc::Args::erasePartialCmdById(int _id)
{
    this->partial_cmds.erase(_id);
}
//list functions
std::string ft_irc::Args::getNicknameById(int id)
{
    std::list<User*>::iterator iter = user_list.begin();

    while (iter != this->user_list.end())
    {
        if ((*iter)->getId() == id)
            return ((*iter)->getNickname());
        iter++;
    }
    return (NULL);
}

std::string ft_irc::Args::getUsernameById(int id)
{
    std::list<User*>::iterator iter = user_list.begin();

    while (iter != this->user_list.end())
    {
        if ((*iter)->getId() == id)
            return ((*iter)->getUsername());
        iter++;
    }
    return (NULL);
}

void ft_irc::Args::removeFromList(int client)
{
    std::list<ft_irc::User*>::iterator iter = this->user_list.begin();
    
    while (iter != this->user_list.end())
    {
        if ((*iter)->getId() == client)
            this->user_list.erase(iter);
        iter++;
    }
}

int ft_irc::Args::getStateById(int _id)
{
    std::list<ft_irc::User*>::iterator iter = this->user_list.begin();
    
    while (iter != this->user_list.end())
    {
        if ((*iter)->getId() == _id)
            return ((*iter)->getState());
        iter++;
    }
    return (-1);
}
int ft_irc::Args::getIdByNickname(std::string _nickname)
{
    std::list<ft_irc::User*>::iterator iter = this->user_list.begin();
    
    while (iter != this->user_list.end())
    {
        if ((*iter)->getNickname() == _nickname)
            return ((*iter)->getId());
        iter++;
    }
    return (-1);
}

int ft_irc::Args::getIdByUsername(std::string _username)
{
    std::list<ft_irc::User*>::iterator iter = this->user_list.begin();
    
    while (iter != this->user_list.end())
    {
        if ((*iter)->getUsername() == _username)
            return ((*iter)->getId());
        iter++;
    }
    return (-1);
}
ft_irc::User ft_irc::Args::getUserById(int _id)
{
    std::list<ft_irc::User*>::iterator iter = this->user_list.begin();
    
    while (iter != this->user_list.end())
    {
        std::cout<<"ID: "<<(*iter)->getId()<<std::endl;
        if ((*iter)->getId() == _id)
            return (*(*iter));
        iter++;
    }
    return (0);
}

void ft_irc::Args::setState(int _state, int _id)
{
    std::list<ft_irc::User*>::iterator iter = this->user_list.begin();
    
    while (iter != this->user_list.end())
    {
        if ((*iter)->getId() == _id)
            (*iter)->setState(_state);
        iter++;
    }
}

void ft_irc::Args::setUsernameById(std::string _username, int _id)
{
    std::list<ft_irc::User*>::iterator iter = this->user_list.begin();
    
    while (iter != this->user_list.end())
    {
        if ((*iter)->getId() == _id)
            (*iter)->setUsername(_username);
        iter++;
    }
}

void ft_irc::Args::setNicknameById(std::string _nickname, int _id)
{
    std::list<ft_irc::User*>::iterator iter = this->user_list.begin();
    
    while (iter != this->user_list.end())
    {
        if ((*iter)->getId() == _id)
            (*iter)->setNickname(_nickname);
        iter++;
    }
}

void ft_irc::Args::setTypeUser(int _type, int _id)
{
    std::list<ft_irc::User*>::iterator iter = this->user_list.begin();
    
    while (iter != this->user_list.end())
    {
        if ((*iter)->getId() == _id)
            (*iter)->setType(_type);
        iter++;
    }
}

int ft_irc::Args::getTypeUserById(int _id)
{
    std::list<ft_irc::User*>::iterator iter = this->user_list.begin();
    
    while (iter != this->user_list.end())
    {
        if ((*iter)->getId() == _id)
            return ((*iter)->getType());
        iter++;
    }
    return (0);
}

void ft_irc::Args::setChannelById(int _id, std::string _channel)
{
    std::list<ft_irc::User*>::iterator iter = this->user_list.begin();
    int id_channel = this->getIdChannelByName(_channel);

    while (iter != this->user_list.end())
    {
        if ((*iter)->getId() == _id)
        {
            (*iter)->setChannel(id_channel);
            break ;
        }
        iter++;
    }
}

int ft_irc::Args::getIdChannelByIdUser(int _id)
{
    std::list<ft_irc::User*>::iterator iter = this->user_list.begin();
    
    while (iter != this->user_list.end())
    {
        if ((*iter)->getId() == _id)
            return ((*iter)->getChannel());
        iter++;
    }
    return (-2);
}

bool ft_irc::Args::are_same_channel(int receiver, int sender)
{
    if (this->getIdChannelByIdUser(receiver) == this->getIdChannelByIdUser(sender))
        return true;
    return false;
}


void ft_irc::Args::addUserToList(ft_irc::User *_user)
{
    this->user_list.push_back(_user);
}

std::list<ft_irc::User*>::iterator ft_irc::Args::listBegin()
{
    return (this->user_list.begin());
}
std::list<ft_irc::User*>::iterator ft_irc::Args::listEnd()
{
    return (this->user_list.end());
}
// vector function
void ft_irc::Args::pushWordToVector(std::string _word)
{
    if (_word.find("\n") < _word.length())
        _word.erase(_word.length() - 1);
    this->mute_words.push_back(_word);
}
std::string ft_irc::Args::searchAndReplaceWords(std::string _words)
{
    std::vector<std::string>::iterator iter = this->mute_words.begin();
    int pos;

    while (iter != this->mute_words.end())
    {
        if ((pos = _words.find(*iter)) < _words.length())
        {
            std::string word = *iter;
            _words.replace(pos, word.length(), "*****");
        }
        iter++;
    }
    return (_words);
}

bool ft_irc::Args::searchChannelByName(std::string _name)
{
    std::list<ft_irc::Channel*>::iterator iter = channels_list.begin();

    while (iter != channels_list.end())
    {
        if ((*iter)->getName() == _name)
            return (true);
        iter++;
    }
    return (false);
}

void ft_irc::Args::showChannelsToId(int _id)
{
    std::vector<std::string>::iterator iter = this->channels.begin();
    std::string complete_message;

    send (_id, "--Channels--\n", 12, 0);
    while (iter != this->channels.end())
    {
        complete_message = "- " + *iter + "\n";
        send(_id, complete_message.c_str(), complete_message.length(), 0);
        iter++;
    }
}
void ft_irc::Args::printVector()
{
    std::vector<std::string>::iterator iter = this->mute_words.begin();

    while (iter != this->mute_words.end())
    {
        std::cout<<"Vector: ["<<*iter<<"]"<<std::endl;
        iter++;
    }
}

void ft_irc::Args::popWordFromVector(std::string _word)
{
    std::vector<std::string>::iterator iter = this->mute_words.begin();

    if (_word.find("\n") < _word.length())
        _word.erase(_word.length() - 1);
    if (this->mute_words.size() == 1)
        this->mute_words.erase(this->mute_words.begin());
    else
    {
        while (iter != this->mute_words.end())
        {
            if (*iter == _word)
            {
                this->mute_words.erase(iter);
                break ;
            }
            iter++;
        }
    }
}
std::string ft_irc::Args::getPasswdByChannel(std::string _channelName)
{
    std::list<ft_irc::Channel*>::iterator iter = channels_list.begin();
   
    while (iter != channels_list.end())
    {
        if ((*iter)->getName() == _channelName)
            return ((*iter)->getPasswd());
        iter++;
    }
    return ("none");
}
template <typename T>
int search_in_list(std::list<T> list, T to_search)
{
    typename std::list<T>::iterator iter = list.begin();

    if (list.size() == 0)
        return (0);
    while (iter != list.end())
    {
        if (*iter == to_search)
            return (1);
        iter++;
    }
    return (0);
}

int ft_irc::Args::isUserBanned(std::string _channelName, int _clientId)
{
    std::list<ft_irc::Channel*>::iterator iter = channels_list.begin();
   
    if (channels_list.size() == 0)
        return (0);
    while (iter != channels_list.end())
    {
        if ((*iter)->getName() == _channelName)
            return (search_in_list((*iter)->ban_id_list, _clientId));
        iter++;
    }
    return (0);
}
ft_irc::Channel *ft_irc::Args::getChannelByName(std::string _channelName)
{
    std::list<ft_irc::Channel*>::iterator iter = channels_list.begin();

    while (iter != channels_list.end())
    {
        if ((*iter)->getName() == _channelName)
            return (*iter);
        iter++;
    }
    return (NULL);
}
//channel functions
void ft_irc::Args::pushChannelByName(std::string _name)
{
    this->channels.push_back(_name);
}
int ft_irc::Args::getIdChannelByName(std::string _name)
{
    std::vector<std::string>::iterator iter = this->channels.begin();
    int i = 0;
    while (iter != this->channels.end())
    {
        if (*iter == _name)
            return (i);
        i++;
        iter++;
    }
    return (-1);
}
// printing all
void ft_irc::Args::printingArgs()
{
    std::cout<<"Host: "<<this->host<<std::endl;
    std::cout<<"Port_network: "<<this->port_network<<std::endl;
    std::cout<<"Password_network: "<<this->password_network<<std::endl;
    std::cout<<"Port: "<<this->port<<std::endl;
    std::cout<<"Password: "<<this->password<<std::endl;
}