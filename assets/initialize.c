#include "blockio.h"
#include "superblock.h"
#include "../assets.h"

int sfs_initialize(int erase){
		int i;
		if(erase = 1){
			char * zero_block;
			zero_block = (char *) calloc(128, sizeof(char));
			for(i = 0; i < 512; i++){
				put_block(i,zero_block);}}
		bfree(0,super.blockCount);
		if(init_superblock() >= 0){
			for(i=0; i < 4; i++)
			{
				set_used(i);
			}
			return 1;}
		else{
			return -1;}
	}
