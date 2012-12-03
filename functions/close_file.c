#include "../warrior-sfs-lib.h"

/*
*@param	int fd			passes the close function the file descriptor number
*@param open_i_block	passes the file descriptor to the open_i_block
*
*int sfs_close function closes a block. If the file that is passed into open_i_node returns true it is open, and then changed to false. Returns true to system to confirm closed. Otherwise, the file isn't open and returns true, that it's closed, to system.
*/
int sfs_close(int fd){
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
	if ( fd < 0 || fd >= oft_size) {
		free(*oft);
		return -1;}
	
	
