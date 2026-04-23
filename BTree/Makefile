build:
	gcc main.c erase/erase.c find/find.c insert/insert.c tree/btree.c -o main

clear:
	rm -f main

run: clear build
	./main

run_example: clear build
	./main < example.txt

