NAME = 			ft_containers
STDNAME =		std_containers
CC = 			clang++
CFLAGS = 		-Wall -Werror -Wextra -std=c++98 -pedantic

HEADERS =		list map vector stack queue \
				Iterator ReverseIterator \
				BidirectionalIterator NodeIterator RandomAccessIterator \
				utils pair
INCDIR =		includes/
SRC =			main.cpp
INC =			$(addprefix $(INCDIR), $(addsuffix .hpp, $(HEADERS)))

FTOUTPUT =		output_ft.txt
STDOUTPUT =		output_std.txt
FTTIMES =		times_ft.txt
STDTIMES =		times_std.txt

.PHONY: all clean fclean re test

all: $(NAME) $(STDNAME)

$(NAME): $(SRC) $(INC)
	$(CC) $(CFLAGS) -I$(INCDIR) $(SRC) -o $(NAME)

$(STDNAME): $(SRC) $(INC)
	$(CC) $(CFLAGS) -I$(INCDIR) -D USE_STD=1 $(SRC) -o $(STDNAME)

clean:
	$(RM) $(FTOUTPUT) $(STDOUTPUT) $(FTTIMES) $(STDTIMES)

fclean: clean
	$(RM) $(NAME) $(STDNAME)

re: fclean all

test: all
	./$(NAME) > $(FTOUTPUT)
	./$(STDNAME) > $(STDOUTPUT)
	diff $(FTOUTPUT) $(STDOUTPUT)
