#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#define MAX_PATH_LENGTH 1024
void findlargestfile(char *dir_path, int total_usage, int *larg_size, char *large_file){
DIR *dir;
struct dirent *entry;
struct stat statbuf;
char file_path[MAX_PATH_LENGTH];
if ((dir = opendir(dir_path))==NULL){
	fprintf(stderr, "Unable to  open directory %s: %s\n", dir_path, strerror(errno));
	return;
	}
while ((entry = readdir(dir))!=NULL){
snprintf(file_path, MAX_PATH_LENGTH, "%s/%s", dir_path,  entry->d_name);
if (lstat(file_path,&statbuf)==-1){
	fprintf(stderr, "%s: %s\n", file_path, strerror(errno));
	continue;
	}
if (S_ISREG(statbuf.st_mode)){
	total_usage += statbuf.st_size;
	if(statbuf.st_size > *larg_size){
		*larg_size =statbuf.st_size;
		strcpy(large_file, file_path);
		}
	} else if (S_ISDIR(statbuf.st_mode)&& strcmp(entry->d_name, ".") !=0 && strcmp(entry->d_name, "..") != 0){
		findlargestfile(file_path,total_usage,larg_size, large_file);
		}
	}
	closedir(dir);
}

int main(int argc,char **argv)
{
	if (argc!=2){
	fprintf(stderr, "Usage: %s Directory\n",argv[0]);
	return EXIT_FAILURE;
	}
	char *dir_path = argv[1];
	int total_usage = 0;
	int larg_size= -1;
	char large_file[MAX_PATH_LENGTH]="";
	findlargestfile(dir_path,total_usage,&larg_size, large_file);
	if(larg_size == -1){
		printf("No files found in directory %s \n",dir_path);
	} 
	else {
		printf("%d %s\n"larg_size,large_file);
		}
	printf("Total disk usage in directory %s: %d bytes \n", dir_path,total_usage);
	return 0;
}


