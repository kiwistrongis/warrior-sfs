#include "../warrior-sfs-lib.h"

int sfs_readdir( int fd, char* buffer){
	//get open file table
	inode** oft;//open file table
	if(DEBUG) printf("%d\n",36);
	char* oft_buffer = malloc(sizeof(char)*super.blockSize);
	int ret = get_block(super.openFileTable_loc, oft_buffer);
	if (ret < 0) {
		free(oft_buffer);
		return ret;}
	oft = malloc(sizeof(inode*));
	int oft_size = read_itable( oft_buffer, oft, super.blockSize);
	if(DEBUG) printf("%d\n",37);
	free(oft_buffer);
	if (oft_size < 0){
		free(oft);
		return -1;}
	if(DEBUG) printf("%d\n",38);
	if ( fd < 0 || fd >= oft_size) {
		free(*oft);
		free(oft);
		return -1;}
	
	//get the dir
	if(DEBUG) printf("%d\n",39);
	inode* dir_meta = (*oft) + fd;
	if( (*dir_meta).type != 1) {
		free(*oft);
		free(oft);
		return -1;}
	inode** dir;
	char* dir_buffer = malloc(sizeof(char)*super.blockSize);
	if(DEBUG) printf("%d\n",40);
	ret = get_block( (*dir_meta).index, dir_buffer);
	if (ret < 0) {
		free(*oft);
		free(oft);
		free(dir_buffer);
		return ret;}
	if(DEBUG) printf("%d\n",41);
	int dir_size = read_itable( dir_buffer, dir, super.blockSize);
	if (dir_size < 0) {
		free(*oft);
		free(oft);
		free(dir_buffer);
		return ret;}
		
	//cleanup
	if(DEBUG) printf("%d\n",42);
	free(*oft);
	free(oft);
	free(dir_buffer);
	
	//everything is okay, we can now read and print the directory
	int i;
	int j = 0;//index in buffer
	if(DEBUG) printf("%d\n",43);
	for( i = 0; i < dir_size; i++){
		int name_length = strlen( (*dir)[i].name);
		strncpy( buffer + j, (*dir)[i].name, name_length);
		strncpy( buffer + j + 1, "\n", 1);
		j += name_length + 1;}
	
	//done
	free(*dir);
	return 0;}
