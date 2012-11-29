#include "superblock.h"
#include "../assets.h"
#include <string.h>

/**
 *the rootof the parsing algorithm
 **/
int parse(char* s, inode* dest);
/**
 *an iteration of the parsing algorithm
 **/
int parse_it(char* s, inode* dest, inode i);
