CC = gcc
CFLAGS ?= -Wall -Wextra -pedantic -O2

SRCDIR = src
BUILDDIR = build

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

NAME = bf-interpreter

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $^ -o $@

$(BUILDDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run : $(NAME)
	./$(NAME) $(ARGS)

clean:
	-rm -r $(BUILDDIR)
	-rm $(NAME)

.PHONY: all clean run
