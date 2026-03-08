CC = gcc
CFLAGS = -Wall -Wextra -I./include
SRC = src/avl_tree.c src/main.c
OBJ = $(SRC:.c=.o)
TARGET = build/avl_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f src/*.o $(TARGET)
