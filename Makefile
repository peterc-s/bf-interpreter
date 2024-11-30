CC = gcc
CFLAGS ?= -Wall -Wextra -pedantic -O2 -D_FORTIFY_SOURCE=3 -Werror=format-security -fstack-clash-protection -fstack-protector-all -fcf-protection -s -Wl,-z,relro,-z,now
CFLAGS += $(CFLAGS_EX)

SRCDIR = src
BUILDDIR = build

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

INSTALLDIR = /usr/sbin

NAME = bf-interpreter

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run : $(NAME)
	./$(NAME) $(ARGS)

clean:
	-rm -r $(BUILDDIR)
	-rm $(NAME)

install : $(NAME)
	sudo cp $(NAME) $(INSTALLDIR)/$(NAME)

uninstall :
	sudo rm $(INSTALLDIR)/$(NAME)

.PHONY: all clean run install uninstall
