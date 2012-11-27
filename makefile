#universals
default: all
clean: tool/cleandir.sh \
		clean-extras
	tool/cleandir.sh
	tool/cleandir.sh assets
	tool/cleandir.sh tests
	rm -f -r documentation
check: all clean
freshen: clean all
jdoc:	javadoc -d documentation \
		-sourcepath . \
		*.ja*
cdoc: doxyfile codefiles
	doxygen
	
#all
all: assets locals
locals: 
assets: \
		assets/blockio.o \
		assets/close_file.o \
		assets/create_file.o \
		assets/delete_file.o \
		assets/free_block_table.o \
		assets/get_size.o \
		assets/get_type.o \
		assets/globals.o \
		assets/initialize.o \
		assets/inode.o \
		assets/open_file.o \
		assets/parsing.o \
		assets/read_dir.o \
		assets/read_file.o \
		assets/superblock.o \
		assets/write_file.o
tests: tests/sfstest
tests-minor: \
		tests/casting.out\
		tests/intest.out \
		tests/sbtest.out \
		tests/shift.out

working: \
		assets/blockio.o \
		assets/free_block_table.o \
		assets/globals.o \
		assets/inode.o \
		assets/parsing.o \
		assets/superblock.o 

clean-extras:
	rm -f tests/sfstest

#locals


#assets
assets/blockio.o: assets/blockio.h assets/blockio.c \
		assets.h
	gcc -c assets/blockio.c -o assets/blockio.o

assets/close_file.o: assets/close_file.c \
		assets.h
	gcc -c assets/close_file.c -o assets/close_file.o
	
assets/create_file.o: assets/create_file.c \
		assets.h
	gcc -c assets/create_file.c -o assets/create_file.o
	
assets/delete_file.o: assets/delete_file.c \
		assets.h
	gcc -c assets/delete_file.c -o assets/delete_file.o
	
assets/free_block_table.o: assets/free_block_table.c \
		assets/free_block_table.h \
		assets/blockio.h \
		assets/superblock.h \
		assets.h
	gcc -c assets/free_block_table.c -o assets/free_block_table.o
	
assets/get_size.o: assets/get_size.c \
		assets/inode.h \
		assets.h
	gcc -c assets/get_size.c -o assets/get_size.o
	
assets/get_type.o: assets/get_type.c \
		assets/inode.h \
		assets.h
	gcc -c assets/get_type.c -o assets/get_type.o
	
assets/globals.o: assets/globals.c \
		assets.h
	gcc -c assets/globals.c -o assets/globals.o
	
assets/initialize.o: assets/initialize.c \
		assets.h
	gcc -c assets/initialize.c -o assets/initialize.o
	
assets/inode.o: assets/inode.c assets/inode.h \
		assets.h
	gcc -c assets/inode.c -o assets/inode.o
	
assets/open_file.o: assets/open_file.c \
		assets/inode.h \
		assets.h
	gcc -c assets/open_file.c -o assets/open_file.o
	
assets/parsing.o: assets/parsing.c assets/parsing.h \
		assets/inode.h \
		assets/superblock.h \
		assets.h
	gcc -c assets/parsing.c -o assets/parsing.o
	
assets/read_dir.o: assets/read_dir.c \
		assets.h
	gcc -c assets/read_dir.c -o assets/read_dir.o
	
assets/read_file.o: assets/read_file.c \
		assets.h
	gcc -c assets/read_file.c -o assets/read_file.o
	
assets/superblock.o: assets/superblock.c assets/superblock.h \
		assets.h \
		assets/blockio.h \
		assets/inode.h \
		
	gcc -c assets/superblock.c -o assets/superblock.o
	
assets/write_file.o: assets/write_file.c \
		assets.h
	gcc -c assets/write_file.c -o assets/write_file.o

#major tests
tests/sfstest.o: tests/sfstest.c \
		assets.h
	gcc -c tests/sfstest.c -o tests/sfstest.o

tests/sfstest: tests/sfstest.o \
		assets.h \
		assets
	gcc -o tests/sfstest tests/sfstest.o \
		assets/blockio.o \
		assets/close_file.o \
		assets/create_file.o \
		assets/delete_file.o \
		assets/free_block_table.o \
		assets/get_size.o \
		assets/get_type.o \
		assets/globals.o \
		assets/initialize.o \
		assets/inode.o \
		assets/open_file.o \
		assets/read_dir.o \
		assets/read_file.o \
		assets/superblock.o \
		assets/write_file.o

#minor tests
tests/casting.out: tests/casting.c
	gcc tests/casting.c -o tests/casting.out

tests/shift.out: tests/shift.c
	gcc tests/shift.c -o tests/shift.out

tests/sbtest.o: tests/sbtest.c \
		assets.h \
		assets/superblock.h
	gcc -c tests/sbtest.c -o tests/sbtest.o

tests/sbtest.out: tests/sbtest.o \
		assets/blockio.o \
		assets/globals.o \
		assets/inode.o \
		assets/superblock.o
	gcc -o tests/sbtest.out tests/sbtest.o \
		assets/blockio.o \
		assets/globals.o \
		assets/inode.o \
		assets/superblock.o

tests/intest.o: tests/intest.c \
		assets.h \
		assets/inode.h
	gcc -c tests/intest.c -o tests/intest.o

tests/intest.out: tests/intest.o \
		assets/globals.o \
		assets/inode.o
	gcc -o tests/intest.out tests/intest.o \
		assets/globals.o \
		assets/inode.o

#codefiles
codefiles: codefiles-assets codefiles-locals codefiles-tests

codefiles-assets: \
		assets/blockio.c \
		assets/blockio.h \
		assets/close_file.c \
		assets/create_file.c \
		assets/delete_file.c \
		assets/free_block_table.c \
		assets/free_block_table.h \
		assets/get_size.c \
		assets/get_type.c \
		assets/globals.c \
		assets/initialize.c \
		assets/inode.c \
		assets/inode.h \
		assets/open_file.c \
		assets/read_dir.c \
		assets/read_file.c \
		assets/superblock.c \
		assets/superblock.h \
		assets/write_file.c

codefiles-locals: \
		

codefiles-tests: \
		tests/casting.c \
		tests/intest.c \
		tests/sbtest.c \
		tests/sfstest.c \
		tests/shift.c
