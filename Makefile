CC := gcc
CFLAGS := -Wall -Wextra -O2 -fPIC -shared
TARGET := insert.so
SRC := insert.c
OBJ := $(SRC:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	@echo "Cleaning up..."
	@rm -f $(TARGET) $(OBJ)
