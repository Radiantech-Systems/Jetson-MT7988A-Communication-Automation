# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -O2

# Output Executable
TARGET = server

# Source File
SRC = main.c

# Default Build Target
all: $(TARGET)

# Build the Server
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean Build Files
clean:
	rm -f $(TARGET)
