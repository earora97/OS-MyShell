#include<header.h>
extern char* line;
extern int count,n,flag;
extern char **args;
extern char cwd[200];
extern int foreground;
void function()
{
	//printf("f1\n");
	flag=1;
	if(n==count)
	{
		printf("Wrong Usage. There must be a file name after >\n");
	}
	else
	{
		args[n] = NULL;
		char* filename = args[n+1];
		printf("Filename:%s\n",filename);
		int fd;
	    // open the file to replace stdout

	    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	    if(fd == -1)
			perror("Failed to open file");
	   	
	   	close(1); // not required, but a good practice
	    
	    // use dup2() to duplicate the fd
	   	if(dup2(fd, 1) != 1)  // 1 refers to stdout
			perror("dup2 fail");

	    eve_launch(args);
	    // close the original fd
	   	close(fd);
	  	freopen("/dev/tty","w",stdout);
	}
	return;
}

void function2()
{
	//	printf("f2\n");
	flag=1;
	if(n==count)
	{
		printf("Wrong Usage. There must be a file name after >>\n");
	}
	else
	{
		char* filename = args[n+1];
		args[n] = NULL;
		//printf("Filename:%s\n",filename);
		int fd;
	    // open the file to replace stdout

	    fd = open(filename, O_WRONLY | O_APPEND | O_CREAT  , 0644);
	    if(fd == -1)
			perror("Failed to open file");
	   	
	   	close(1); // not required, but a good practice
	    
	    // use dup2() to duplicate the fd
	   	if(dup2(fd, 1) != 1)  // 1 refers to stdout
			perror("dup2 fail");

	    eve_launch(args);
	    // close the original fd
	   	close(fd);
	  	freopen("/dev/tty","w",stdout);
	}
	return;
}

void function3()
{
	//	printf("f3\n");

	flag=1;
	if(n==count)
	{
		printf("Wrong Usage. There must be a file name after <\n");
	}
	else
	{
		args[n] = NULL;
		char* filename = args[n+1];
		//printf("Filename:%s\n",filename);
		int fd;
	    // open the file to replace stdout

	    fd = open(filename, O_RDONLY, 0644);
	    if(fd == -1)
			perror("Failed to open file");
	   	
	   	close(0); // not required, but a good practice
	    
	    // use dup2() to duplicate the fd
	   	if(dup2(fd, 0) == -1)  // 0 refers to stdout
			perror("dup2 fail");

	    eve_launch(args);
	    // close the original fd
	   	close(fd);
	   	freopen("/dev/tty","r",stdin);
	}
	return;
}

//JOBS
running_jobs *rjobs;
void my_jobs()
{
	//printf("helo\n");
	running_jobs *curr=rjobs;
	int i;
	for (i=1;curr!=NULL;curr=curr->next,i++) {
		printf("[%d] %s [%d]\n",i,curr->jobName,curr->pid);
	}
	//return 1;
}
//END JOBS

//FG
void my_fg(char ** args)
{
	if(args[1]==NULL)
		printf("Syntax Error!\n");
	else
	{
	pid_t pid=make_int(args[1]),wpid;
	int status;
	do{
		wpid=waitpid(pid, &status,WUNTRACED);
	}while(!WIFEXITED(status) && !WIFSIGNALED(status));
}
}

int make_int(char * str)
{
	int i=0,num=0;
	for(;str[i]!='\0';i++)
	{
		num=num*10+(str[i]-'0');
	}
	return num;
}
//END FG

//KILLALLBG
void my_killallbg()
{
	running_jobs *curr=rjobs;
	for(;curr!=NULL;curr=curr->next)
	{
		pid_t pid=curr->pid;
		kill(pid,SIGQUIT);
	}
}

//QUIT
void my_quit()
{
	exit(0);
	//return 0;
}
//END QUIT


//kjob
void my_kjob(char **args)
{
	pid_t pid=make_int(args[1]);
	int sig=make_int(args[2]);
	kill(pid,sig);
}
//end kjobs

void ctrlC()
{
	int now = getpid();
	//printf("%d\n",now);
	if(foreground==1)
		kill(now,0);
  printf("\n");
}

void ctrlD() 
{
  printf("\n");
  return exit(1);
}