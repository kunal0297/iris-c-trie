CC := gcc
CFLAGS := -Wall -Wextra -O2 -fPIC -shared -fvisibility=hidden
TARGET := libfastlookup.so
SRC := fastlookup.c

.PHONY: all clean debug

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

debug:
	$(CC) -Wall -g -fPIC -shared -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
