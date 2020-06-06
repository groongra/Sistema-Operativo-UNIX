#include <stdio.h>              /* Cabecera llamada al sistema printf  */
#include <sys/types.h>          /* Cabeceras llamada al sistema open  */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>             /* Cabecera llamadas al sistema read, write y close  */
#include <stdlib.h>		/* Brings exit() method */

#define BUFFER_SIZE 1024

int mycat(char* file_name);
int main(int argc, char *argv[]);

int mycat(char* file_name){

int dfile, nread;
char buffer[BUFFER_SIZE];
if((dfile = open(file_name, O_RDONLY))<0){
	perror("Error: File failed to open\n");
	close(dfile);
	return -1;
}
while((nread = read(dfile, buffer, BUFFER_SIZE))>0){
	if(write(STDOUT_FILENO, buffer, nread)<nread){
	perror("Error: File failed to writte on Shell\n");
	close(dfile);
	return -1;
	}
}
if(nread<0){
	perror("Error: File failed to read\n");
	close(dfile);
	return -1;
}
close(dfile);
return 0;
}

int main(int argc, char *argv[])
{
if(argc<2 | argc>2){
	perror("Error: Incorrect number of arguments");
	exit(-1);
}
if(mycat(argv[1])<0){
	exit(-1);
}
exit(0);
}

