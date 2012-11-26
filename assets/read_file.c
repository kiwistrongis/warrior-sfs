#include "blockio.h"
#include "../assets.h"

int sfs_read(int fd, int start, int length, char *mem_pointer){
	int length_to_read=length;
    char *mem_ptr=mem_pointer;
    data_blcok * data_blcok_tmp;
    int next_blk;
    open_i_blcok[fd].file_ptr=start;
    if(open_i_blcok[fd].type) {
        printf("Can't read from a file folder :P\n");
        return -1;
    }

    while (open_i_blcok[fd].file_ptr>=120){
        open_i_blcok[fd].file_ptr=open_i_blcok[fd].file_ptr%120;
        next_blk=((data_blcok*)(open_i_blcok[fd].block_content))->next_block_num;
        if(get_block(next_blk, open_i_blcok[fd].block_content)!=0) return -1;
    }
    printf("open_i_blcok[fd].block_index: %d\n", open_i_blcok[fd].block_index);
    while (length_to_read){

        if(get_block(open_i_blcok[fd].block_index, open_i_blcok[fd].block_content)!=0) return -1;
        if(open_i_blcok[fd].file_ptr==120){
            //Current Block has been finished for reading
            //Going to the next one
            open_i_blcok[fd].file_ptr=0;
            if (((data_blcok*)(open_i_blcok[fd].block_content))->next_block_num<=0) return -1;
            if(get_block(((data_blcok*)(open_i_blcok[fd].block_content))->next_block_num, open_i_blcok[fd].block_content)!=0) return -1;
        }
        data_blcok_tmp=(data_blcok*)(open_i_blcok[fd].block_content);
        *mem_ptr=((data_blcok*)(open_i_blcok[fd].block_content))->content[open_i_blcok[fd].file_ptr];
        open_i_blcok[fd].file_ptr++;
        //putchar(*mem_ptr);
        mem_ptr++;
        length_to_read--;
    }
	return 1;}
