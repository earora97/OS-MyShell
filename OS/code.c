#include<header.h>
char hostname[200],cwd[200],string[100],thishome[200]="/OS";
char *line,*dir;
int status;
char **args;
int a;
int main(int argc, char* argv[])
{
	int i=0,count=0;
	gethostname(hostname, sizeof(hostname));
	struct passwd *p = getpwuid(getuid());
	while(1)
	{
		int a = dup(0);
		int b = dup(1);
		getcwd(cwd, 200);
		dir = strstr(cwd, thishome);
		if(strcmp(dir,thishome)==0)
			dir = "~"; 
		else
		{
			char *temp=strtok(dir,thishome);
			strcpy(dir,"~");
			strcat(dir,temp);
		}
		printf("<%s@%s:%s>", p->pw_name,hostname,dir);
		line = eve_read_line();
		status = eve_split_command(line);
		signal(SIGINT,ctrlC);
		dup2(a,0);
		dup2(b,1);
		close(a);
		close(b);
	}
	return 0;
}
