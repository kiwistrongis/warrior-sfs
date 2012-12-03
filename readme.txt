warrior-sfs - A Strong Simulated Filesystem

DESCRIPTION
===========
Description text is descriptiony.

Supported Commands
==================
close <fd> - Closes the file represented by the file descriptor fd.
create <path> <type> <size> - Creates the file/dir at the specified path. Type indicates whether to make a file or dir. Size indicates the desired allocated size of the file in bytes. Size is overridden when creating a dir.
dir <fd> - Lists the contents of the already-opened folder represented by the file descriptor fd.
del <path> - Deletes the file indicated by path.
exit - Exits the program.
init <erase> - Initialize the filesystem. The disk is reformated if erase is 1.
open <path> - Opens the file/dir indicated by path.
read <fd> <start> <length> - Seeks to position <start> in the already-opened file (non-directory), then reads <length> bytes.
size <path> - Returns the size of the file/dir indicated by path.
type <path> - Returns the type of the file/dir indicated by path.
write <fd> <start> <length> <data> - Seeks to position <start> in the already-opened file (non-directory), then writes <length> bytes from <data>

