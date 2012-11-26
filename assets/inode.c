/*summary of what inode does
*
*/
#include "inode.h"

/*write_inode		converts indoes into cstrings
*
*@param i			inode to be converted
*@param name_length	integer length of the inode's name
*@param *result		char pointer to allocated space in memory equal to 4+name length
*
*The result of write_inode place the inodes index, size, type and name length into the first 4 blocks of allocated
*memory and stores the name in the remaining blocks
*/
char* write_inode(inode i){//reliably converts inodes into cstrings
	int name_length = strlen(i.name);
	char* result = malloc((4+name_length)* sizeof(char);
	result[0] = i.index;
	result[1] = i.size;
	result[2] = i.type;
	result[3] = name_length;
	int j;
	for(j = 0; j<name_length; j++)
		result[4+j] = i.name[j];
	return result;}
	
/**read_inode		converts cstrings into inodes
 *
 *@param s			char pointer
 *@param i			inode to be read
 *@param name_length	integer stores length of the inode name, casts the char array's 4th value to int
 *
 *The result of read_inode retrieves the index, size, type and name of the char array 'inode' and converts it into an 
 *inode
 **/	
inode read_inode(char* s){//reliably converts cstrings into inodes
	inode i;
	i.index = s[0];
	i.size = s[1];
	i.type = s[2];
	int name_length = (int) s[3];
	i.name = malloc(name_length*sizeof(char));
	int j;
	for(j = 0; j<name_length; j++)
		i.name[j] = s[4+j];
	return i;}

/*write_itable stores indoes in blocks of allocated memory? -is that right????????
*
*@param result		char pointer to allocated memory, size determined by size_alloc value
*@param *t			pointer to inode in memory
*@param t_size		integer value of inode's
*@param size_alloc
*@param r_i		
*@param buffer
*
*/
int write_itable(char* result, inode* t, int t_size, int size_alloc){
	result = malloc(sizeof(char)*size_alloc);
	int r_i = 0;
	char* buffer;
	int j;
	for(j = 0; j<t_size; j++){
		if(size_alloc - r_i < 10)
			return -1;
		buffer = write_inode(t[j]);
		int k;
		for(k = 0; buffer[k]!='\0'; k++)
			result[r_i++] = buffer[k];
		free(buffer);}
	result = realloc( result, sizeof(inode)*(r_i+1));
	return r_i;}
	
/**/
int read_itable(char* s, inode* t){
	free(t);
	int s_size = strlen(s);
	int s_i = 0;//current index of s
	int s_left = s_size - s_i;
	int t_size = s_size/10;//minimum possible number of elements
	t = malloc(sizeof(inode)*t_size);
	int t_i = 0;
	while ((s_left = s_size-s_i) > 4){
		char* s_p = &(s[s_i]);
		int next_size = 4 + s[3];
		if(s_left < next_size)
			break;
		if(t_i >= t_size){
			s_left = s_size - s_i;
			t = realloc( t, sizeof(inode)*(t_size + (s_left/10) + 1));}
		t[t_i++] = read_inode(s_p);
		s_i+=next_size;}
	t = realloc(t, sizeof(inode)*(t_i+1));
	return t_i+1;}
