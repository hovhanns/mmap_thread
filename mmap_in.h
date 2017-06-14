#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
extern char *mmap_dst;  /// pointer to mapped memory
/**
 * init memory mapping
 * @param  f_name file name for mapping
 * @param  size   file size
 * @return        -1	error
 *                 0	success
 */
int mmap_init(const char *, int);

/**
 * closes file descriptor (fd)
 * @return 		0	success
 *             	-1	error
 */
int mmap_rem();