#include "blockio.h"
#include "../assets.h"

int sfs_readdir(int fd, char *mem_pointer){
	int i;
	folder_block* temp_f_blk;
	char temp[128];

	if(get_block(open_i_block[fd].block_index,temp)!=0) return -1;

	temp_f_blk=(folder_block*)temp;
	if(open_i_block[fd].type){
		for (i=open_i_block[fd].file_ptr;i<NUM_CONTENT_IN_FOLDER;i++){
		if (i==0) i++;

		if(temp_f_blk->dest_list[i]>0){
			strcpy(mem_pointer, temp_f_blk->name_list[i]);
			printf("mem_pointer: %s\n",mem_pointer);
			open_i_block[fd].file_ptr=i+1;
			return 1;
		}
	}
	if (i==NUM_CONTENT_IN_FOLDER)
		return -1;
	}else{
		return 1;
	}
}
