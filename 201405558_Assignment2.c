#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h> 
#include<sys/dir.h>
#include<fcntl.h>
#include<unistd.h>
#include<math.h>
#include<stdlib.h>
#include <unistd.h>

void func(char *file,char *dest,int s,int e)
{
	long size;
	int fileno;
	char *fdest;
	//Obtain the filedescriptor number from open system call. To be used in other subsequent calls.

	fileno = open(file, O_RDONLY);
 
	if ((size = lseek(fileno, 0L, SEEK_END)) == -1)
	{
		perror("lseek() error");
		return;
	}
	else 
	{
		//printf("Total size of file is: %ld\n", size);
	}

		
	double temp = s*size/100;
	temp = floor(temp);
	int start = temp;
	
	temp = e*size/100;
	temp=floor(temp);
	int end = temp;

	//printf("\nstart: %d",start);
	//printf("\nend: %d", end);
	lseek(fileno, start, 0);
	char buf[1000];
	int n;

        n = read(fileno, buf,end-start+1);	
	//printf("\nNo of bytes read: %d\n",n);
	//printf("%s\n",buf);

	//Locating the destination folder
	const char slash[2] = "/";
	const char home[5] = "/home";
	char *filename,*temps;
	DIR *dirptr;
	int l1 = strlen(dest);
	char path[l1+1];
	int count=0,j;
	
	filename = strtok(dest,slash);
	while( filename != NULL ) 
   	{
		int l2 = strlen(filename);
		for(j=0;j<l2;j++)
		{
			path[count] = filename[j];
			count++;		
		}
		
		if(strcmp(filename,"home")==0)
		{
			int n = chdir("/home");
			if(n==0)
			{
			//	printf("\nn is: %d",n);
			}
			else
				perror("Error");
			temps = strtok(NULL, slash);
			//printf( "\nHOME !! Directory %s  and path is%s\n", filename,path);
				
		}
		else
		{
	      		//printf( "\nDirectory %s and path is%s\n",filename,path);
			dirptr = opendir(filename);
			temps = strtok(NULL, slash);
			if((dirptr==NULL)&&(temps!=NULL))
			{
				//printf("\nDirptr is null. For path %s Directory %s not found",path,filename);
				mkdir(filename);
				chmod(filename,S_IXUSR|S_IRUSR|S_IWUSR);
				int ch = chdir(filename); 
				if(ch==0)
				{
				//	printf("\nchdir Success ,ch is: %d",ch);
				}
				else
					perror("Error");				
				fdest = temps;
			}
			else if(temps!=NULL)
			{
				//printf("\n Succesfully opened directory %s for path %s",filename,path);
				chdir(filename);
				fdest = temps;		
			}      		
		}
		
		filename = temps;
		path[count]='/';
		count++;		
		  
 	}
	//printf("\nOpening: %s",fdest);
	//Opening Destination File
	int fileno1 = open(fdest, O_CREAT|O_APPEND|O_WRONLY);
	 ssize_t num;
	write(fileno1,buf,n);

	// Closing the file of particular file descriptor
	close(fileno);
	close(fileno1);

	printf("Successfully copied :%d Bytes\n",n);

   	
}
void listdir(const char *path,const char *disp) 
{
	struct stat sb;
	lstat(path, &sb);
	switch (sb.st_mode)
	{
		case S_IFLNK: return;
	}


	if(path==NULL)return;
	if(strcmp(path,"X11")==0)
		return;	
	if(strcmp(path,".")==0)
	{
		chdir("..");
		return;
	}
	
	if(strcmp(path,"..")==0)
	{
		chdir("..");
		return;
	}
	
	//printf("\nIn listdir function path is %s and disp is %s",path,disp);
	access(path,F_OK);
	
	DIR *dirptr = opendir(path);
	if(dirptr==NULL)
	{
		//perror("");		
		//perror("\ndirptr is null. Directory not found");
		
		return;
	}
	printf("\n%s/%s:",disp,path);
	   struct dirent **namelist;
	   int n;

	   n = scandir(path, &namelist, NULL, alphasort);
	if (n < 0)
	{
		// printf("n is less then zero");
	}
	else 
	{	printf("\n");
		int m =n;
		while (m--) 
		{
			//Displaying the files
			char *name = namelist[m]->d_name;
		        if((strcmp(name,"..")!=0)&&(strcmp(name,".")!=0))			
			{
				//strcat(path,name);	
				//char temp = path;
				printf("%s/%s/%s\t",disp,path,name);
			}			
		}	
		while (n--) 
		{
			//Recursion logic
			//if(strcmp(namelist[n]->d_name,'.')!=0)
			char *name = namelist[n]->d_name;
		        //printf("Name of File parameter is: %s\n", name);
			chdir(path);	
			int l1 = strlen(disp);
			int l2 = strlen(path);
			int i,j,count;
			char parameter[l1+l2+2];
			for(i=0;i<l1;i++)	
				parameter[i] = disp[i];
			parameter[i]='/';
			i++;
			count=i;
			for(j=0;j<l2;j++)
			{	
				//printf("\ncount=%d and path val is %c",count,path[j]);
				parameter[count] = path[j];
				count++;			
			}
			//printf("\nValue of parameter : %s",parameter);
			if(namelist[n]->d_type==DT_DIR)			
				listdir(name,parameter);                   
			free(namelist[n]);
		}
		free(namelist);
	}
	closedir(dirptr);
    
}


int main()
{
	char c[64];
	scanf("%s",c);
	while(c!="exit")
	{
		//printf("\nin loop, c is: %s",c);
		if(strcmp(c,"list")==0)
		{
			//printf("\nCase One");
			char s[1024];
			scanf("%s",s);
			//printf("\nSource: %s",s);
			char s1[]="";
			listdir(s,s1);
		}
		else if(strcmp(c,"copy")==0)
		{
			
			//printf("\nCase Two");
			char source[1024],dest[1024];
			int start,end;
			scanf("%s",source);
			scanf("%s",dest);
			scanf("%d",&start);	
			scanf("%d",&end);
			
			//printf("\nSource: %s Dest: %s start: %d end: %d",source,dest,start,end);
			func(source,dest,start,end);	
		}
		
		
		scanf("%s",c);
		if(strcmp(c,"exit")==0)
			break;	
	}
}
