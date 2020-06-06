#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int mysize();
int main(int argc, char *argv[]);

int mysize()
{
char* path_name;
path_name = getcwd(path_name, PATH_MAX);
DIR* dir = opendir(path_name);
if(errno == ENOENT){
	perror("Error: Directory or 'name' doesnt exist");
	return -1;
} else if(errno == ENOTDIR){
        perror("Error: The 'name' provided isnt a directory");
        return -1;
}
struct dirent* dirProperties;
int dfile;
off_t file_size;
char buffer[BUFFER_SIZE];

while((dirProperties = readdir(dir)) != NULL){
	if(dirProperties->d_type == DT_REG){
		if((dfile = open(dirProperties->d_name,O_RDONLY))<0){
			perror("Error: File failed to open");
			return -1;
		}
		if((file_size=lseek(dfile,0,SEEK_END))<0){
			perror("Error: Unable to relocate file offset");
			return -1;
		}
		//FPRINTF() Y WRITE()
		sprintf(buffer,"%s\t%jd\n",dirProperties->d_name,file_size);
		write(STDOUT_FILENO, buffer,strlen(buffer));
		close(dfile);
	}
}
closedir(dir);
return 0;
}

int main(int argc, char *argv[])
{

if((argc<1)|(argc >1)){
	 perror("Error: Incorrect number of arguments");
	 exit(-1);
}
if(mysize()<0) exit(-1);

exit(0);

}

