#include "../inc/lib_irc.hpp"

std::list<std::string> ft_split(std::string str, char splitter)
{
 	std::list<std::string> words_list;
    std::string word;
    int end;
    int start = 0;

    end = str.find(splitter);
    while (end != -1)
    {
        word = str.substr(start, end - start);
		if (word.find("\r\n") < word.size())
        	word = word.substr(0, word.find("\r\n"));
        if (word.find("\n") < word.size())
        	word = word.substr(0, word.find("\n"));
        if (word != "\0")
            words_list.push_back(word);
        start = end + 1;
        end = str.find(splitter, start);
    }
    word = str.substr(start, end);
	if (word.find("\r\n") < word.size())
        word = word.substr(0, word.find("\r\n"));
    if (word.find("\n") < word.size())
        word = word.substr(0, word.find("\n"));
    words_list.push_back(word);
    return (words_list);
}

std::string clean_word(std::string _word, std::string to_clean)
{
	if (_word.find(to_clean) < _word.size())
		_word = _word.replace(_word.find(to_clean), to_clean.size(), "");
	return (_word);
}