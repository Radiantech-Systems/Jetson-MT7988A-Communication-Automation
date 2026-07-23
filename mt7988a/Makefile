# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -O2

# Target Executable
TARGET = tcp_client

# Source File
SRC = tcp_client.c

# Default Target
all: $(TARGET)

# Build Rule
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean Rule
clean:
	rm -f $(TARGET)
