NAME=evalast

OBJECT_NAMES=	\
				evalast \

OBJ_DIR=./.obj
SRC_DIR=./src
INC_DIR=./inc

IFLAGS=-I$(INC_DIR)
WFLAGS=-Werror -Wextra -Wall
CFLAGS=$(WFLAGS) $(IFLAGS)
OBJECTS=$(patsubst %, $(OBJ_DIR)/%.o, $(OBJECT_NAMES))

CC=gcc

all: $(NAME)
$(NAME): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all