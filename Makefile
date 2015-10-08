##
## Makefile
## 
## Made by oleszkiewicz Jonathan
## Email   <JonathanOlesz@gmail.com>
## 
## Started on  Sun Feb 16 23:40:55 2014 oleszkiewicz
## Last update Sun Feb 16 23:40:57 2014 oleszkiewicz
##

CC=     gcc
SRC        = add_memory_block.c \
			 fusion.c \
			 initiation.c \
			 main_function.c \
			 manage_system_memory.c \
			 search_free_block.c \
			 split.c
OBJ=    $(SRC:.c=.o)
CFLAGS= -fPIC -Wextra -Wall -W -Werror -lpthread
LDFLAGS= -shared -lpthread -O3
NAME=   libmy_malloc_$(HOSTTYPE).so
LN_TARGET=      libmy_malloc.so
RM=             rm -rf
all:    $(OBJ)
		$(CC) $(LDFLAGS) -o $(NAME) $(OBJ)
		ln -fs $(NAME) $(LN_TARGET)
clean:
		$(RM) $(OBJ)
fclean: clean
		$(RM) $(NAME)
		$(RM) $(LN_TARGET)
re:     fclean all
