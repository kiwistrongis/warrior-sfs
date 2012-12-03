#include "../assets.h"
int main(){
	
	int ret;
	ret = get_superblock();
	printf("%d %d %d %d %d %d %d %d %d %s\n",
		ret, super.blockSize, super.blockCount, super.super_loc, super.openFileTable_loc, super.freeBlockTable_loc, super.root.index, super.root.size, super.root.type, super.root.name);
	ret = init_superblock();
	printf("%d %d %d %d %d %d %d %d %d %s\n",
		ret, super.blockSize, super.blockCount, super.super_loc, super.openFileTable_loc, super.freeBlockTable_loc, super.root.index, super.root.size, super.root.type, super.root.name);
	ret = get_superblock();
	printf("%d %d %d %d %d %d %d %d %d %s\n",
		ret, super.blockSize, super.blockCount, super.super_loc, super.openFileTable_loc, super.freeBlockTable_loc, super.root.index, super.root.size, super.root.type, super.root.name);
	
	super.blockSize = 128,
	super.blockCount= 512,
	super.super_loc= 0,
	super.openFileTable_loc= 1,
	super.freeBlockTable_loc= 2,
	super.root.index = 3,
	super.root.size = 1,
	super.root.type = 0,
	super.root.name = malloc(4*sizeof(char));
	super.root.name = "root";
	/*
	int i = 511;
	char* s = malloc(20);
	printf("%s\n",s);
	printf("ASDF\n");
	put_bytes(s+2,i);
	printf("%d %d\n",s[0],s[1]);
	printf("%s\n",s);
	int b;
	get_bytes(s+2,(int*)&b);
	printf("%d\n",b);*/
	return 0;
}
