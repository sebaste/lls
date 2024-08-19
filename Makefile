NAME = lls

SRC_PROJECT = src/lls.c \
			  src/get_args.c src/aux.c src/swap.c src/sort.c \
			  src/timespec_comp.c src/dir_ent_init.c src/dir_ent_get.c \
			  src/dir_ent_print.c src/print_rights.c src/print_other.c \
			  src/dir_ent_print_printers.c src/err.c src/init.c \
			  src/custom/custom_memlib.c src/custom/custom_strlib.c

FLAGS = -O3 -Wall -Wextra -Werror -Iinclude/

OBJECT_PROJECT = $(SRC_PROJECT:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT_PROJECT)
	@gcc -o $(NAME) $(OBJECT_PROJECT) $(FLAGS)

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@/bin/rm -f $(OBJECT_PROJECT)

fclean: clean
	@/bin/rm -f $(NAME)

re:	fclean all
