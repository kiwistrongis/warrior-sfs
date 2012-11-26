#include "blockio.h"
#include "../assets.h"

int sfs_write(int fd, int start, int length, char *mem_pointer){
    char temp_blk[128];
    int length_to_write=length;
    int working_blk=open_i_blcok[fd].block_index;
    char *mem_ptr=mem_pointer;
    int new_size=((data_blcok*)(open_i_blcok[fd].block_content))->file_size;
    //open_i_blcok[fd].file_ptr=start;
    if(open_i_blcok[fd].type) {
        printf("Can't write to a folder file\n");
        return -1;
    }
    if (start<0){
        open_i_blcok[fd].file_ptr=new_size;
        new_size=new_size+length;
        ((data_blcok*)(open_i_blcok[fd].block_content))->file_size=new_size;
    }else{
        open_i_blcok[fd].file_ptr=start;
        if((start+length)>new_size)
            return -1;
    }

    while (open_i_blcok[fd].file_ptr>=120){
        open_i_blcok[fd].file_ptr=open_i_blcok[fd].file_ptr%120;
        if(get_block(((data_blcok*)(open_i_blcok[fd].block_content))->next_block_num, open_i_blcok[fd].block_content)!=0) return -1;
    }
    while(length_to_write){
        if(open_i_blcok[fd].file_ptr==120){
            if(put_block(working_blk, open_i_blcok[fd].block_content)!=0) return -1;
            open_i_blcok[fd].file_ptr=0;
            if (((data_blcok*)(open_i_blcok[fd].block_content))->next_block_num<=0){
                ((data_blcok*)(open_i_blcok[fd].block_content))->next_block_num=find_first_empty_block();
                ((data_blcok*)temp_blk)->next_block_num=0;
                ((data_blcok*)temp_blk)->type=0;
                ((data_blcok*)temp_blk)->valid=1;
                put_block(((data_blcok*)(open_i_blcok[fd].block_content))->next_block_num, temp_blk);
            }else{
                working_blk=((data_blcok*)(open_i_blcok[fd].block_content))->next_block_num;
            }
           
            if(get_block(((data_blcok*)(open_i_blcok[fd].block_content))->next_block_num, open_i_blcok[fd].block_content)!=0) return -1;
        }
        ((data_blcok*)(open_i_blcok[fd].block_content))->content[open_i_blcok[fd].file_ptr]=*mem_ptr;
       
        putchar(((data_blcok*)(open_i_blcok[fd].block_content))->content[open_i_blcok[fd].file_ptr]);
        open_i_blcok[fd].file_ptr++;
        mem_ptr++;
        length_to_write--;
    }
    if(put_block(working_blk, open_i_blcok[fd].block_content)!=0) return -1;
	return 1;
}
