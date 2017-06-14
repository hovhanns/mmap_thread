all:
	gcc m.c mmap_in.c -l pthread
clean:
	rm a.out file.txt