# Define compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -O2
LDFLAGS = -lm

# Define the source files
SRCS = Queue.c AObject.c st_pipeline.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Define the header files
DEPS = Queue.h AObject.h

# Define the output name
OUT = st_pipeline

# The "all" target will build the final binary
all: $(OUT)

# The final binary depends on the object files
$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Compile each .c file into corresponding .o file
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove object files and the binary
clean:
	rm -f $(OBJS) $(OUT)
