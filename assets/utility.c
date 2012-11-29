#include "../assets.h"

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
