#include "../warrior-sfs-lib.h"

//open file specified by pathname; if it doesn't exist, error
//if file opens;return file descriptor(non-negative integer value) to caller

int sfs_open(char *pathname){
	//get file
	inode* result = malloc(sizeof(inode));
	int ret = parse(pathname, result);
	if ( ret < 0) { //file does not exist
		free(result);
		return ret;}
	if(DEBUG) printf("%d\n",29);
	
	//get open file table
	inode** oft; //open file table
	char* oft_buffer = malloc(sizeof(char)*super.blockSize);
	ret = get_block( super.openFileTable_loc, oft_buffer);
	if(DEBUG) printf("%d\n",30);
	if (ret < 0) {
		free(result);
		free(oft_buffer);
		return ret;} //super not initialized?
	oft = malloc(sizeof(inode*));
	int oft_size = read_itable( oft_buffer, oft, super.blockSize);
	if(DEBUG) printf("%d\n",31);
	free(oft_buffer);
	if (oft_size < 0) {
		free(result);
		free(oft);
		return -1;} //read failed?
	
	//add file to oft
	oft_size++;
	if(DEBUG) printf("%d\n",32);
	*oft = realloc( *oft, sizeof(inode) * ( oft_size + 1));
	if(DEBUG) printf("%d\n",33);
	if( *oft == NULL) {
		free(result);
		free(oft);
		return -1;} //ran out of memory
	(*oft)[oft_size] = (*oft)[oft_size - 1];
	(*oft)[oft_size - 1] = *result;
	oft_buffer = calloc( super.blockSize, sizeof(char));
	ret = write_itable( oft_buffer, *oft, super.blockSize);
	if(DEBUG) printf("%d\n",34);
	free(result);
	free(*oft);
	free(oft);
	if(ret < 0) {
		return ret;} //there wasn't enough space
	
	//put new open file table
	if(DEBUG) printf("%d\n",35);
	ret = put_block( super.openFileTable_loc, oft_buffer);
	free( oft_buffer);
	if ( ret < 0) return ret;
	
	//done
	return oft_size - 1;}//open file's fd
