#include "stdio.h"
#include "dirent.h"
#include "sys/stat.h"
#include "time.h"
#include "pwd.h"
#include "grp.h"
void directory_files(char *path);
void print_info(const char *file_name);
int main(int argc, char *argv[]){
	
	if (argc==2)
	{
		directory_files(argv[1]);
	}
	else{
		directory_files(".");
	}

	return 0;
}

void directory_files(char *path)
{
	DIR *directory;
	struct dirent *dir;
	printf("\n");
	directory=opendir(path);
	if(directory)
	{

		while((dir = readdir(directory))!=NULL)
		{

			print_info(dir->d_name);
		}
		closedir(directory);
	}
}

void print_info(const char *file_name)
{
	struct stat stats;
	stat(file_name,&stats);
    printf( (S_ISDIR(stats.st_mode) ) ? ("d") : ("-") );
    printf( (stats.st_mode & S_IRUSR) ? ("r") : ("-") );//prints owner permissions read, write, execute
    printf( (stats.st_mode & S_IWUSR) ? ("w") : ("-") );
    printf( (stats.st_mode & S_IXUSR) ? ("x") : ("-") );
    printf( (stats.st_mode & S_IRGRP) ? ("r") : ("-") );//prints group permissions 
    printf( (stats.st_mode & S_IWGRP) ? ("w") : ("-") );
    printf( (stats.st_mode & S_IXGRP) ? ("x") : ("-") );
    printf( (stats.st_mode & S_IROTH) ? ("r") : ("-") );//prints permissions for others(users aside from 
    printf( (stats.st_mode & S_IWOTH) ? ("w") : ("-") );//the owner or members of editors)
    printf( (stats.st_mode & S_IXOTH) ? ("x") : ("-") );
    printf(" %ld\t",stats.st_nlink);
    printf("%s  ",getpwuid(stats.st_uid)->pw_name);
    printf("%s  ",getgrgid(stats.st_gid)->gr_name);
    printf("%ld   \t",stats.st_size);
 	struct tm mod_time;
   	mod_time = *(gmtime(&stats.st_mtime));	
    printf("%d-%c%d-%d %d:%c%d", mod_time.tm_mday, mod_time.tm_mon<10 ? '0' : '\0' , mod_time.tm_mon,	//prints time
    mod_time.tm_year + 1900, mod_time.tm_hour + 3, mod_time.tm_min<10 ? '0' : '\0' , mod_time.tm_min);
   	printf(" %s\n",file_name);
}