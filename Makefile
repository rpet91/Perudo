NAME =			perudo

CC =			clang++
CFLAGS =		-Wall -Werror -Wextra -std=c++98 -pedantic
UNUSED = 		-Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wno-unused-private-field

SDIR =			src
ODIR =			obj
IDIR =			inc

CLASSES =		Options Game Player

_OBJS =			main $(CLASSES)
OBJS =			$(addsuffix .o, $(addprefix $(ODIR)/, $(_OBJS)))
HEADERS =		$(addsuffix .hpp, $(addprefix $(IDIR)/, $(CLASSES)))

ifeq ($(DEBUG),1)
		CFLAGS += -fsanitize=address -g3
	endif

.PHONY: all clean fclean re debug game

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(ODIR)/%.o: $(SDIR)/%.cpp $(HEADERS)
		@mkdir -p $(ODIR)
		$(CC) $(CFLAGS) -I$(IDIR) -c $< -o $@

clean:
		$(RM) $(OBJS)
		$(RM) *.dSYM

fclean: clean
		$(RM) $(NAME)

re: fclean all

debug: fclean
		@make DEBUG=1

game: all
		clear
		./$(NAME)
