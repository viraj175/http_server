CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC = src/main.c src/socket.c src/request.c src/response.c src/file.c
OBJ = $(SRC:.c=.o)
TARGET = http-server

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
