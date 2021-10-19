NAME = ircserv

SRC_FOLDER = src/
SRC = 	admin_utils.cpp       creating_user.cpp     privmsg_parse.cpp     userIrc.cpp\
		args.cpp              join_command.cpp      replies_to_client.cpp utils.cpp\
		channel.cpp           main.cpp\
		channels.cpp          network_utils.cpp     simple_commands.cpp\
		check_commands.cpp    privmsg_command.cpp   socket.cpp

INCL_FOLDER = inc/
INC =	args.hpp    channel.hpp lib_irc.hpp socket.hpp  userIrc.hpp
INCLUDES = $(addprefix $(INCL_FOLDER), $(INC))

OBJ_FOLDER = obj/
OBJ = $(SRC:.cpp=.o)
OBJECT = $(addprefix $(OBJ_FOLDER), $(OBJ))

$(OBJ_FOLDER)%.o : $(SRC_FOLDER)%.cpp $(INCLUDES)
	@mkdir -p $(OBJ_FOLDER)
	clang++ -c $< -o $@
 
$(NAME): $(OBJECT)
	clang++ $(OBJECT) -o $(NAME)

all: $(NAME)

re: fclean all

clean:
	rm -rf $(OBJ_FOLDER)

fclean: clean
	rm -f $(NAME)

.PHONY: all re clean fclean 