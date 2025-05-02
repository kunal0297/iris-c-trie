CC = gcc
CFLAGS = -fPIC -shared
TARGET = insert.so
SRC = insert.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
