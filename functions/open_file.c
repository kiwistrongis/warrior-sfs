#include "../warrior-sfs-lib.h"

//open file specified by pathname; if it doesn't exist, error
//if file opens;return file descriptor(non-negative integer value) to caller

int sfs_open(char *pathname){
	//get file
	inode* result;
	int ret = parse(pathname, result);
	if ( ret < 0) return ret; //file does not exist
	
	//get open file table
	inode** oft; //open file table
	char* oft_buffer = malloc(sizeof(char)*super.blockSize);
	ret = get_block( super.openFileTable_loc, oft_buffer);
	if (ret < 0) {
		free(oft_buffer);
		return ret;} //super not initialized?
	int oft_size = read_itable( oft_buffer, oft, super.blockSize);
	free(oft_buffer);
	if (oft_size < 0) return -1; //read failed?
	
	//add file to oft
	oft_size++;
	*oft = realloc( *oft, sizeof(inode) * ( oft_size + 1));
	if( oft == NULL) return -1; //ran out of memory
	(*oft)[oft_size] = (*oft)[oft_size - 1];
	(*oft)[oft_size - 1] = *result;
	oft_buffer = calloc( super.blockSize, sizeof(char));
	ret = write_itable( oft_buffer, *oft, super.blockSize);
	free(*oft);
	if(ret < 0) return ret; //there wasn't enough space
	
	//put new open file table
	ret = put_block( super.openFileTable_loc, oft_buffer);
	free( oft_buffer);
	if ( ret < 0) return ret;
	
	//done
	return oft_size - 1;}//open file's fd
