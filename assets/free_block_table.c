#include "../assets.h"
/**
*free_block_table does some stuff to some other stuff.
*int set_free	sets block indexed by block_num to free
*int set_used	sets block indexed by block_num to used
*int find_free
*int balloc
*int bfree
**/


/**
*@param block_num			integer, number of the block.
*@param *block_buff		char pointer allocates memory of 128 
*@param table_block_num	integer, set to 3
*@param ret					integer, value of get_block on table_block_num and block_buff
*@param loc					integer, block_num divided by 8
*@param mod					integer, block_num mod by 8
*@param byte				char, block_buff of location loc value
*
*set_free function sets the block indexed by block_num to free
**/
int set_free(int block_num){
	char* block_buff = malloc(sizeof(char)*128);
	int table_block_num = super.freeBlockTable_loc;
	int ret = get_block(table_block_num,block_buff);
	if (ret<0) return ret;
	//find and change the bit representing the requested block
	int loc = block_num/8;
	int mod = block_num%8;
	char byte = block_buff[loc];
	byte |= (128>>mod);
	//put the byte back into the table's block and write it
	block_buff[loc] = byte;
	ret = put_block(table_block_num,block_buff);
	return ret<0?ret:0;}

/**
*@param block_num			integer, number of the block.
*@param *block_buff		char pointer allocates memory of 128 
*@param table_block_num	integer, set to 3
*@param ret					integer, value of get_block on table_block_num and block_buff
*@param loc					integer, block_num divided by 8
*@param mod					integer, block_num mod by 8
*@param byte				char, block_buff of location loc value
*
*set_used function sets the block indexed by block_num to used
**/
int set_used(int block_num){//set the block indexed by block_num to used
	char* block_buff = malloc(sizeof(char)*128);
	int table_block_num = super.freeBlockTable_loc;
	int ret = get_block(table_block_num,block_buff);
	if (ret<0) return ret;
	//find and change the bit representing the requested block
	int loc = block_num/8;
	int mod = block_num%8;
	char byte = block_buff[loc];
	byte &= 255-(128>>mod);
	//put the byte back into the table's block and write it
	block_buff[loc] = byte;
	ret = put_block(table_block_num,block_buff);
	free(block_buff);
	return ret<0?ret:0;}

/**
*@param size
*@param *block_buff_size	char pointer, allocated memory of size block_buff_size
*@param table_block_num		integer, initialized to 0
*@param ret					integer, value of get_block on table_block_num and block_buff
*@param loc					integer, block_num divided by 8
*@param mod					integer, block_num mod by 8
*@param ubound				integer, the size of the block buffer size minus size in blocks +1
*@param bit					integer, initialized to 0
*@param n_free				integer, initialized to 0, stores number of free blocks
*@param byte				char, block_buff of location loc value
*
*find_free finds free blocks in memory of system.
**/
int find_free(int size){//size in blocks
	if (size<1) return -1;
	//setup
	int block_buff_size = 128;
	char* block_buff = malloc(sizeof(char)*block_buff_size);
	int table_block_num = super.freeBlockTable_loc;
	int ret = get_block(table_block_num,block_buff);
	if (ret<0) return ret;
	int loc = 0;
	int ubound = block_buff_size - size + 1;
	int bit = 0;
	int n_free = 0;
	char byte = block_buff[loc];
	//search
	while((8*loc + bit) < ubound){
		if(byte & (128>>bit) > 0) n_free++;
		loc += ++bit / 8;
		bit %= 8;
		if(n_free >= size){
			free(block_buff);
			return 8*loc + bit - n_free;}
		if(bit == 0)
			byte = block_buff[loc];}
	free(block_buff);
	return -1;}

/**
*@param block_num		integer, value returned by find_free
*@param *zero_block	128 bits of memory allocated for array
*@param ret				integer, value of get_block on table_block_num and block_buff
*
*balloc function allocates blocks in memory for arrays.
**/
int balloc(int size){//allocates blocks
	int block_num = find_free(size);
	if (block_num<0) return block_num;
	char* zero_block = calloc(128,sizeof(char));
		//must be calloc, ensures zeros
	int ret;
	int i;
	for(i=0; i<size; i++){
		ret = put_block(block_num+i,zero_block);
		if (ret<0){
			free(zero_block);
			return ret;}
		ret = set_used(block_num+i);
		if (ret<0){
			free(zero_block);
			return ret;}}
	free(zero_block);
	return block_num;}
	
/**
*@param ret	integer, value of get_block on table_block_num and block_buff
*
*bfree function sets blocks to free
**/
int bfree(int block_num, int size){
	int ret;
	int i;
	for(i = 0; i<size; i++){
		ret = set_free(block_num + i);
		if(ret<0) return ret;}
	return 0;}

