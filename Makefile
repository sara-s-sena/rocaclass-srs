srs: src/main.c
	gcc -o srs src/main.c -lsqlite3

clean:
	rm -f srs