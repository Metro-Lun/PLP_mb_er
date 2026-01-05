CC = gcc
CFLAGS = -Wall -Wextra
SRC = stack_char.c stack_double.c interpretor.c postfix.c main.c
TARGET = prog

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run:
	./$(TARGET)

.PHONY: all clean