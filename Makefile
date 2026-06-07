CC		= gcc
CFLAGS	= -Wall -Wextra -O2 -g
LDFLAGS	= -lsqlite3

SOURCE_FILES = $(filter-out src/removed_from_mainc.c src/test.c src/rascunho.txt, $(wildcard src/*.c))
OBJECT_FILES = $(SOURCE_FILES:.c=.o)

srs: $(OBJECT_FILES)
	$(CC) -o $@ $(OBJECT_FILES) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f srs $(OBJECT_FILES)

.PHONY: clean test check
