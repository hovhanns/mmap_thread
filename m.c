#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "mmap_in.h"

typedef struct Wrt_param
{	
	char *msg;
	int seek;
	int part_size;
}wrt_param;

const char * f_name = "file.txt";

/**
 * /
 * @param  arg 	thread argument list
 *              *msg  		- message to write in file
				seek  		- file seek size
				part_size	- size of writing message
 * @return     non return value
 */
void *write_thrd(void* arg)
{
	
	int seek = ((wrt_param*)arg)->seek;
	int p_size = ((wrt_param*)arg)->part_size;
	char *msg = ((wrt_param*)arg)->msg;

	printf("seek = %d, p_size = %d, msg = %s\n", seek,p_size, msg);
	char *m_dst = mmap_dst + seek;	

	int i = 0;
	for (i = 0; i < p_size; i+=4)
	{
		strcpy(m_dst+i,msg);
	}
}


/**
 * simple function, which generates 4 length character array 
 * which contains passed char argument
 * @param  c  - character for creating array
 * @return   	allocated char array.
 */
char *gen_char(char c)
{
	int sz = 4;
	char *ret = calloc(sz, sizeof(char));
	int i;
	for (i = 0; i < sz; ++i)
	{
		ret[i] = c;
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	int file_size = 1024;
	mmap_init(f_name, file_size);
	int i = 0;
	pthread_t p_arr[10];
	int size = 5;
	for (i = 0; i < size; ++i)
	{
		wrt_param *p = calloc(1, sizeof(wrt_param));
		p->seek = 100*(i);
		p->part_size = 100;
		p->msg = gen_char('0'+i);
		pthread_create (&p_arr[i], NULL, &write_thrd, p);		
	}
	
	int j;

	for (j = 0; j < size; ++j)
	{
		pthread_join(p_arr[j], NULL);
	}

	mmap_rem();
	return 0;
}