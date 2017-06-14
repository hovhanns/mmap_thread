#include "mmap_in.h"

char *mmap_dst;
static int mmap_fd = 0; //// mapped file descriptor

int mmap_init(const char *f_name, int size)
{

	int mmap_fd = 0;	
	if ((mmap_fd = open(f_name, O_RDWR | O_CREAT | O_TRUNC)) < 0)
	{
		printf("can't create file for writing\n");
		return -1;
	}

	if ( lseek(mmap_fd, size - 1, SEEK_SET) == -1 )
	{
		printf("error in lseek\n");
		return -1;
	}
	if ( write(mmap_fd, "", 1) != 1 )
	{
		printf("error call write\n");
	}

	if ( (mmap_dst = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, mmap_fd, 0)) == MAP_FAILED ) 
	{
		printf("error call mmap\n");
		return -1;
	}
	
	return 0;
}

int mmap_rem()
{
	close(mmap_fd);
	return 0;
}