#include "../assets.h"

/*inode reads and writes inodes and itables
*
*char* write_inode	converts inodes into cstrings
*char* read_inode		converts cstrings into inodes
*int write_itable		...
*int read_itable		...
*/

int size_in_blocks(inode i){
	return i.size/128 + 1;}

/**
*@param i			inode to be converted
*@param name_length	integer length of the inode's name
*@param *result		char pointer to allocated space in memory equal to 4+name length
*
*The result of write_inode place the inodes index, size, type and name length into the first 4 blocks of allocated
*memory and stores the name in the remaining blocks
**/
char* write_inode(inode i){//reliably converts inodes into cstrings
	int name_length = strlen(i.name);
	char* result = malloc((8 + name_length + 1)* sizeof(char));
	put_bytes(result + 0, i.index);
	put_bytes(result + 2, i.size);
	put_bytes(result + 4, i.type);
	put_bytes(result + 6, name_length);
	int j;
	for(j = 0; j<name_length; j++)
		result[8+j] = i.name[j];
	*(result+8+j) = '\0';
	return result;}
	
/**
 *@param s				char pointer
 *@param i				inode to be read
 *@param name_length	integer stores length of the inode name, casts the char array's 4th value to int
 *
 *The result of read_inode retrieves the index, size, type and name of the char array 'inode' and converts it into an inode
 **/	
inode read_inode(char* s){//reliably converts cstrings into inodes
	inode i;
	int ret;
	ret = get_bytes(s + 0, (int*)&(i.index));
	ret = get_bytes(s + 2, (int*)&(i.size));
	ret = get_bytes(s + 4, (int*)&(i.type));
	int name_length;
	get_bytes(s + 6, (int*)&(name_length));
	i.name = malloc((name_length + 1) * sizeof(char));
	int j;
	for(j = 0; j<name_length; j++)
		i.name[j] = s[8+j];
	*(i.name+j) = '\0';
	return i;}

/**
*
*@param result		char pointer to allocated memory, size determined by size_alloc value
*@param *t				pointer to inode in memory
*@param t_size			integer value of inode's pointer size
*@param size_alloc	integer value of size of memory allocated 
*@param r_i				integer value to index next unused space in result
*@param buffer			char pointer to place in memory
*@param j,k				integer counters
*
*int write_itable function determines whether there is sufficient room then converts inode into string using write_inode function. Increases result index then frees up memory of buffer.
**/
int write_itable(char* result, inode* t, int result_size_alloc){
	int r_i = 0; //index in result
	int space_left; //space left in result
	int t_i = 0; //index in inode table
	char* i_buffer; //buffer for inode data
	int ib_i;//index in inode buffer
	int ib_size; //size of i_buffer
	do{
		ib_size = 8 + strlen(t[t_i].name);
		i_buffer = write_inode( t[t_i++]);
		space_left = (result_size_alloc - r_i) - 1;
		if( space_left < ib_size){ //we have run out of space
			free(result);
			free(i_buffer);
			return -1;}
		//we have enough space
		for(ib_i = 0; ib_i < ib_size; ib_i++)
			result[r_i++] = i_buffer[ib_i];
		free(i_buffer);}
	while( ib_size > 8); //we have exausted t: \
		terminator inode has null name, \
		therefore ib_size = 8 + name length = 8
	*(result + r_i) = '\0';
	return r_i;}
	
/**
*@param *s			char pointer
*@param *t			inode pointer
*@param s_size		integer length of s 'string' char array
*@param s_i			integer, current index of s
*@param s_left		integer of total size of s minus current index
*@param t_size		integer, minimal possible number of elements
*@param t_i			integer, index of element
*@param *s_p		char pointer to reference variable of s at current index
*@param next_size	integer value of next element
*
*int read_itable function frees up memory for inode t, t then allocates memory for minimal possible number of elements. While s_left is greater than 4, it checks to see if s_left is less than the next_size and breaks, otherwise, if the element index is greater or equal to next_size, t reallocates memory and increases its index, sending s_p to the read_inode function.
* alternatively
**/
int read_itable(char* s, inode** t, int s_size){
	//int s_size = strlen(s);
	int s_i = 0;
	int s_left;
	int t_size = s_size/14 + 1;
	*t = realloc(*t, sizeof(inode) * t_size);
	int t_i = 0;
	while((s_left = s_size - s_i) > 8){ //we can read name length from s
		int new_name_length;
		get_bytes(s + s_i + 6, (int*) &new_name_length);
		int new_size = new_name_length + 8;
		if(s_left < new_size){ //s is incorrectly formatted
			int k;
			for( k=0; k<t_i; k++)
				free((*t)[k].name);
			free(t);
			return -1;}
		if( t_size < t_i){
			t_size = s_left/14 + 1;
			*t = realloc(*t, sizeof(inode) * t_size);}
		(*t)[t_i++] = read_inode(s + s_i);
		s_i += new_size;
		if(new_name_length <= 0){ //we have reached the terminator inode
			*t = realloc( *t, sizeof(inode) * t_i);
			return t_i - 1;}}}

