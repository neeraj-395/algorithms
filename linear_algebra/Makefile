# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -I.

# Source files for the library
LIB_SRCS = matrix.c gausseli.c inverse.c
LIB_OBJS = $(LIB_SRCS:.c=.o)

# Source file for the test executable
TEST_SRC = test.c

# Build the static library
lib: $(LIB_OBJS)
	ar rcs libmat.a $(LIB_OBJS)
	rm -f $(LIB_OBJS)

# Build the test executable
test: $(TEST_SRC) lib
	$(CC) $(CFLAGS) -o test $(TEST_SRC) -L. -lmat

# Compile source files into object files
%.o: %.c matrix.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(LIB_OBJS) libmat.a test

# Phony targets
.PHONY: lib test clean