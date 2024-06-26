# Compiler and Compiler Flags
CC=gcc
CFLAGS=-Wall -g -Iinclude `pkg-config --cflags gtk+-3.0`
# Linker flags
LDFLAGS=-lreadline `pkg-config --libs gtk+-3.0`

# The build target executable:
TARGET=minios

# Source, Object files
SRCS=kernel/kernel.c kernel/Shell-cmd/program.c kernel/system.c kernel/Shell-cmd/command.c kernel/Shell-cmd/parser.c kernel/Shell-cmd/symbol.c kernel/Shell-cmd/execute.c kernel/Shell-cmd/redirect.c kernel/gtk_app.c
OBJS=$(SRCS:.c=.o) 

# Include directory
INCLUDE_DIR=include

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# To obtain object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up:
clean:
	rm -f $(OBJS) $(TARGET)

