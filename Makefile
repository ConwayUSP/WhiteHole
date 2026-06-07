CC = gcc
CFLAGS = -Wall
TARGET = whitehole.out
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC = src/main.c src/modules/*.c

all: game

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f whitehole.out
