#include "../warrior-sfs-lib.h"

int sfs_write(int fd, int start, int length, char *buffer){
	int blockOffset = start % super.blockSize;
	if(blockOffset + length > super.blockSize)
		return -1;
	//get open file table
	inode** oft; //open file table
	char* oft_buffer = malloc(sizeof(char)*super.blockSize);
	int ret = get_block( super.openFileTable_loc, oft_buffer);
	if (ret < 0) {
		free(oft_buffer);
		return ret;} //super not initialized?
	oft = malloc(sizeof(inode*));
	int oft_size = read_itable( oft_buffer, oft, super.blockSize);
	free(oft_buffer);
	if (oft_size < 0) {
		free(oft);
		return -1;} //read failed?
	if ( fd < 0 || fd >= oft_size) {//verify fd range
		free(*oft);
		free(oft);
		return -1;}
	if( (*oft)[fd].type == 1){ //cant write dir like file
		free(*oft);
		free(oft);
		return -1;}
	if( (*oft)[fd].size < start + length){ //file is not that big
		free(*oft);
		free(oft);
		return -1;}
		
	//everything's good, we can can write the fd'th element
	char* block = malloc(sizeof(char)*super.blockSize);
	ret = get_block( (*oft)[fd].index + blockOffset, block);
	if( ret < 0){
		free(*oft);
		free(oft);
		free(block);
		return ret;}
	int i;
	for(i = 0; i < length; i++)
		block[start + i] = buffer[i];
	ret = put_block( (*oft)[fd].index + blockOffset, block);
	free(*oft);
	free(oft);
	free(block);
	if( ret < 0) return ret;
	
	//done
	return 0;}
