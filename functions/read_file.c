#include "../warrior-sfs-lib.h"

int sfs_read(int fd, int start, int length, char *buffer){
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
	if( (*oft)[fd].type == 1){ //cant read dir like file
		free(*oft);
		free(oft);
		return -1;}
	if( (*oft)[fd].size < start + length){ //file is not that big
		free(*oft);
		free(oft);
		return -1;}
		
	//everything's good, we can can read the fd'th element
	char* block = malloc(sizeof(char)*super.blockSize);
	ret = get_block( (*oft)[fd].index + blockOffset, block);
	free(*oft);
	free(oft);
	if( ret < 0){
		free(block);
		return ret;}
	int i;
	for(i = 0; i < length; i++)
		buffer[i] = block[start + i];
	free(block);
	buffer[length] = '\0';
	
	//done
	return 0;}
