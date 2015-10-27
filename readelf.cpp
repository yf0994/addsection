#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <errno.h>

int main(int argc, char** argv){
	int fd = -1;
	int errno, i = 0;
	ssize_t headersize, filesize;
	if((fd = open(argv[1], O_RDONLY)) == -1){
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}
	Elf32_Ehdr *header;
	Elf32_Half type, ehsize, phentsize, phnum, shentsize, shnum, shstrndx;
	Elf32_Word version, flags;
	Elf32_Off phoff, shoff;
	unsigned char* header_magic;
	headersize = sizeof(Elf32_Ehdr);
	if(read(fd, header, headersize) == -1){
		fprintf(stderr, "%s\n", strerror(errno));
		goto exit;
	}
	header_magic = header -> e_ident;
	type = header -> e_type;
	version = header -> e_version;
	phoff = header -> e_phoff;
	shoff = header -> e_shoff;
	flags = header -> e_flags;
	ehsize = header -> e_ehsize;
	phentsize = header -> e_phentsize;
	phnum = header -> e_phnum;
	shentsize = header -> e_shentsize;
	shnum = header -> e_shnum;
	shstrndx = header -> e_shstrndx;
	
	for(i = 0; i < EI_NIDENT; i++){
		printf("%02x ", header_magic[i]);
	}
	printf("\n");
exit:
	if(fd != -1){
		close(fd);
		return -1;
	}
	return 0;
}
