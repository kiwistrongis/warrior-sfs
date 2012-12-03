#include "../warrior-sfs-lib.h"

int sfs_readdir( int fd, char* buffer){
	//get open file table
	inode** oft;//open file table
	char* oft_buffer = malloc(sizeof(char)*super.blockSize);
	int ret = get_block(super.openFileTable_loc, oft_buffer);
	if (ret < 0) {
		free(oft_buffer);
		return ret;}
	oft = malloc(sizeof(inode*));
	int oft_size = read_itable( oft_buffer, oft, super.blockSize);
	free(oft_buffer);
	if (oft_size < 0){
		free(oft);
		return -1;}
	if ( fd < 0 || fd >= oft_size) {
		free(*oft);
		free(oft);
		return -1;}
	
	//get the dir
	inode* dir_meta = (*oft) + fd;
	if( (*dir_meta).type != 1) {
		free(*oft);
		free(oft);
		return -1;}
	inode** dir;
	char* dir_buffer = malloc(sizeof(char)*super.blockSize);
	ret = get_block( (*dir_meta).index, dir_buffer);
	if (ret < 0) {
		free(*oft);
		free(oft);
		free(dir_buffer);
		return ret;}
	int dir_size = read_itable( dir_buffer, dir, super.blockSize);
	if (dir_size < 0) {
		free(*oft);
		free(oft);
		free(dir_buffer);
		return ret;}
		
	//cleanup
	free(*oft);
	free(oft);
	free(dir_buffer);
	
	//everything is okay, we can now read and print the directory
	int i;
	for( i = 0; i < dir_size; i++)
		printf("%s\n",(*dir)[i].name);
	
	//done
	free(*dir);
	return 0;}
