# Compiler settings
CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -O2 -g

# Source files and target
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGET = server.bin

# Header files
HDRS = $(wildcard *.h)

# Default target (just calls build)
all: build

# Build target
build: $(TARGET)

# Run target (depends on build)
run: build
	./$(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all build run clean
