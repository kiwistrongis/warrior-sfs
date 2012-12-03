//Library Includes
//Assets Include
#include "assets.h"
/**
 * Warrior Filesystem Functions
 */

int sfs_open(char* pathname);
int sfs_read(int fd, int start, int length, char* buffer);
int sfs_write(int fd, int start, int length, char* buffer);
int sfs_readdir(int fd, char* buffer);
int sfs_close(int fd);
int sfs_delete(char* pathname);
int sfs_create(char* pathname, int type, int size);
int sfs_getsize(char* pathname);
int sfs_gettype(char* pathname);
int sfs_initialize(int erase);
