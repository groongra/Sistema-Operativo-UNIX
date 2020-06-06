#include <stdio.h>              /* Cabecera llamada al sistema printf  */
#include <unistd.h>             /* Cabecera llamada al sistema gtcwd  */
#include <sys/types.h>          /* Cabeceras llamadas al sistema opendir, readdir y closedir  */
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int mylsVoid();
int mylsArgs(char* dir_name);
int main(int argc, char *argv[]);

int mylsArgs(char* dir_name)
{
DIR* dirp = opendir(dir_name); //Opendir() opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream. 
			     	//	The stream is positioned at the first entry in the directory.
if(ENOENT == errno){
	perror("Error: dir failed to open\n");
	return -1;
}
struct dirent* dirProperties;
char buffer [BUFFER_SIZE];
while((dirProperties=readdir(dirp))!=NULL){	//The readdir() function returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp.
						// It returns NULL on reaching the end of the directory stream or if an error occurred.
	//perror("Error: dir failed to read\n");
	//return -1;

	sprintf(buffer,"%s\n",dirProperties->d_name);	//sprintf(destination,type,origin) copies the string into buffer
	write(STDOUT_FILENO, buffer, strlen(buffer));
}
closedir(dirp);
return 0;
}

int mylsVoid()
{
char* path_name;

path_name = getcwd(path_name,PATH_MAX);

if(ERANGE == errno){    //getcwd( name, size) returns a null-terminated string containing an absolute pathname that is the current working directory of the $
        perror("Error: unable to obtain pathname\n");
        return -1;
}
DIR* dirp = opendir(path_name); //Opendir() opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream.
                                //      The stream is positioned at the first entry in the directory.
if(ENOENT == errno){
        perror("Error: dir failed to open\n");
        return -1;
}
struct dirent* dirProperties;
while((dirProperties=readdir(dirp))!=NULL){     //The readdir() function returns a pointer to a dirent structure representing the next directory entry in th$
                                                // It returns NULL on reaching the end of the directory stream or if an error occurred.
        //perror("Error: dir failed to read\n");
        //return -1;
        printf("%s\n",dirProperties->d_name);
}
closedir(dirp);
return 0;
}

int main(int argc, char *argv[])
{
switch(argc){
default:
	if(argc<2) perror("Error: Not enough arguments. Only 2 expected");

	else if(argc>2) perror("Error: too many arguments. Only 2 expected");
        exit(-1);
	break;
case 1:
	if(mylsVoid()<0) exit(-1);
	break;
case 2:
	if(mylsArgs(argv[1])<0);
	exit(-1);
	break;
}
exit(0);
}

