#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/stat.h"


int *get_size(unsigned char *buffer, int NumOfFiles)
{
	int *size=calloc(NumOfFiles,sizeof(int));
	for(int i=0,j=0;i<NumOfFiles*7;i+=7)
    {
    	size[j]=(buffer[4+i+2]<<16)+(buffer[4+i+1]<<8)+buffer[4+i];
    	j++;
    }
    return size;
}

int *get_offset(unsigned char *buffer, int NumOfFiles)
{
	int *offset=calloc(NumOfFiles,sizeof(int));
	for(int i=0,j=0;i<NumOfFiles*7;i+=7)
    {
    	offset[j]=(buffer[4+i+6]<<32)+(buffer[4+i+5]<<16)+(buffer[4+i+4]<<8)+buffer[4+i+3];
    	j++;
    }
    return offset;
}
char **get_names(unsigned char *buffer, int NumOfFiles, int file_len)
{
	int *size=get_size(buffer, NumOfFiles);
	int *offset=get_offset(buffer, NumOfFiles);
	char **names;
	names=(char**)calloc(NumOfFiles,sizeof(char));
	int counter=0;
	for(int i=0;i<NumOfFiles-1;i++)
	{
		counter=offset[i+1]-(offset[i]+size[i]);
    	names[i]=calloc(counter,sizeof(char));
    	strncpy(names[i],buffer+(offset[i]+size[i]),counter);
	}
	counter=file_len-(offset[NumOfFiles-1]+size[NumOfFiles-1]);
    names[NumOfFiles-1]=calloc(counter,sizeof(char));
    strncpy(names[NumOfFiles-1],buffer+(offset[NumOfFiles-1]+size[NumOfFiles-1]),counter);

	return names;
}

char *get_dir(unsigned char *path,long int n){

	char *dirs;
	int position=-1;
	for(int i=0;i<n+1;i++){
		if(path[i]=='/'){
			position=i;
		}
	}
	if(position!=-1)
	{
		dirs=(char*)calloc(position,sizeof(char));
		strncpy(dirs,path,position);
	}
	else {
		dirs=(char*)calloc(1,sizeof(char));
		dirs[0]='\0';
	}
	return dirs;
}

int main(int argc, char *argv[])
{

	FILE *fileptr;
	unsigned char *buffer;
	long filelen;

	fileptr = fopen(argv[1], "r");  		// Open the file in binary mode
	fseek(fileptr, 0, SEEK_END);          	// Jump to the end of the file
	filelen = ftell(fileptr);				// Get the current byte offset in the file
            
	rewind(fileptr);                      	// Jump back to the beginning of the file

	buffer = (unsigned char *)malloc(filelen * sizeof(unsigned char)); 	// Enough memory for the file
	fread(buffer, filelen, 1, fileptr); 								// Read in the entire file
	fclose(fileptr); // Close the file


    int NumOfFiles=0;
    NumOfFiles=(buffer[3]<<8)+buffer[2];//converts to little endian
    int *size=get_size(buffer, NumOfFiles);
    int *offset=get_offset(buffer, NumOfFiles);
    char **names;
    names=get_names(buffer, NumOfFiles, filelen);

    for(int i=0;i<NumOfFiles;i++){
    	char *dir=get_dir(names[i],strlen(names[i]));
    	mkdir(dir, 0700);
    	FILE *d;
    	if((d=fopen(names[i],"w+"))==NULL)
    	{
    		perror("Error occured while creating file");
    	}
    	for(int j=offset[i];j<(offset[i]+size[i]);j++)
    	{
    		putc(buffer[j],d);
    	}
    	fclose(d);

    }

	return 0;
}