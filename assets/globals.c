#include "../assets.h"

/**
 * Global data structures
 */
void initialize_globals(){
	command_buffer = malloc (sizeof(char)*(MAX_INPUT_LENGTH+1));
	io_buffer = malloc (sizeof(char)*(MAX_IO_LENGTH+1));
	data_buffer_1 = malloc (sizeof(char)*(MAX_INPUT_LENGTH));}

/**
*void free globals function frees up memory for command_buffer, io_buffer and data_buffer_1
**/
void free_globals(){
	free(command_buffer);
	free(io_buffer);
	free(data_buffer_1);}

/**
*int put_bytes function takes last 2 bytes from the int and puts them in indexes 0 and 1 in the cstring or char array
**/
int put_bytes(char* s, int bytes){
	s[0] = bytes/128;
	s[1] = bytes%128;
	return 2;}

/**
*int get_bytes function returns last 2 bytes from the int that are stored in index 0 and 1, using integer pointer
**/
int get_bytes(char* s, int* bytes){
	*bytes = s[0]*128 + s[1];
	return 2;}
