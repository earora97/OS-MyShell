#include<header.h>
extern char* line;
int status;
int flag=0,n=0;
extern int count;
extern char **args;
extern char cwd[200];
#define EVE_TOK_BUFSIZE 64
#define EVE_TOK_DELIM " \t\n\r"
struct command
{
  char **argv;
};

void compare()
{
	flag=0;
	n = 0;
	while(n<count)
	{
	//	printf("%d\n", n);
		if(strcmp(args[n],">")==0)
			function();
		else if(strcmp(args[n],">>")==0)
			function2();
		else if(strcmp(args[n],"<")==0)
			function3();
		n++;
	}
	if(flag==0)
	{
		if(strcmp(args[0],"pwd")==0)
		{
			getcwd(cwd, sizeof(cwd));
			printf("%s\n",cwd);
		}
		else if(strcmp(args[0],"cd")==0)
		{
			chdir(args[1]);
		}
		else if(strcmp(args[0],"echo")==0)
		{
		//	printf("heya\n");
			int position=1;
			char *word=args[position];
			for(;word!=NULL;position++)
			{
				printf("%s",word);
				word=args[position+1];

				//to print space
				//all delimiters will be replaced with space
				if(word!=NULL)
					printf(" ");
			}
			printf("\n");
		}
		else if (strcmp(args[0],"jobs")==0)
        	my_jobs();
        else if (strcmp(args[0],"fg")==0)
            my_fg(args);
        else if (strcmp(args[0],"killallbg")==0)
          	my_killallbg();
        else if(strcmp(args[0],"quit")==0)
          	my_quit();
        else if(strcmp(args[0],"kjob")==0)
        	my_kjob(args);
		else if(strcmp(args[0],"pinfo")==0)
		{
			int c;
			char buf[80],buff[20],buff2[20],pid[20];
			strcpy(pid,args[1]);
			strcpy(buff,"/proc/");
			strcpy(buff2,"/cmdline");
			strcat(buff,pid);
			strcat(buff,buff2);
			char *filename = buff;
			FILE* file = fopen(filename, "r");
			if(file)
			{
				printf("Executable file: ");
				while((c = getc(file)) != EOF)
				{
					putchar(c);
				}
				fclose(file);
			}
			printf("\n");
			if(args[1]!=NULL)
			{
				//printf("hello\n");
				char infoFile[50],line[100],temp;
				int r,file,j=0;
				strcpy(infoFile,"/proc/");
				strcat(infoFile,args[1]);
				strcat(infoFile,"/status");

				if((file=open(infoFile,O_RDONLY))!=-1)
				{
					while((r=read(file,&temp,sizeof(char)))!=0)
					{
						if(temp!='\n')
						{
							line[j]=temp;
							j++;
						}
						else
						{
							if (strstr(line,"State")!=NULL)
								printf("%s\n",line );
							else if (strstr(line,"VmSize")!=NULL)
								printf("%s\n",line );
							memset(line,0,sizeof(line));
							j=0;

						}
					}
				}
			}
		}
		else
		{
			eve_launch(args);
		}
	}
}


int
spawn_proc (int in, int out, struct command *cmd)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          close (in);
        }

      if (out != 1)
        {
          dup2 (out, 1);
          close (out);
        }

      if (execvp (cmd->argv [0], (char * const *)cmd->argv) == -1)
      	{

      		fprintf(stderr, "Heeeeeello\n");
      		exit(EXIT_FAILURE);
      	}
      	return 1;
    }

  return pid;
}

void fork_pipes (int b, struct command *cmd)
{
  int i,result;
  pid_t pid,ppid;
  int in, fd [2];
  in = 0;

  for (i = 0; i < b - 1; ++i)
    {
   //   printf("%d %d\n",i,b);
      pipe (fd);

      spawn_proc (in, fd [1], cmd + i);

      close (fd [1]);

      in = fd [0];
    }
     //  printf("hi3\n");

  if (in != 0)
    dup2 (in, 0);

	pid=fork();
	if(pid==0)
  	{
  		if(execvp (cmd[i].argv[0], (char * const *)cmd[i].argv)== -1)
  		{
  			fprintf(stderr, "Error here\n");
    		exit(EXIT_FAILURE);
  		}
  	}
  	else
  	{
  		ppid = waitpid(pid,&result,0);
  		while(!WIFEXITED(result) && !WIFSIGNALED(result))
  			ppid = waitpid(pid,&result,0);
  	}
 // printf("%d\n", a);
  //printf("nnn\n");
}

#define EVE_TOK_CDELIM ";\n"
#define EVE_TOK_CDELIM2 "|\n"

int eve_split_command(char* line)
{
	int counter=0;
	int bufsize = EVE_TOK_BUFSIZE, position = 0;
	char *token;
	char *token2;
	char *saveptr;
	char *saveptr2;
	char *list[100];
	struct command cmd[100];
	token = strtok_r(line, EVE_TOK_CDELIM,&saveptr);
	//printf("token1:%s\n",token);

	while (token != NULL)
	{
		token2 = strtok_r(token, EVE_TOK_CDELIM2,&saveptr2);
	//	printf("%s\n",token2);
		while(token2!=NULL)
		{
		//	printf("hh\n");
			list[counter] = token2;
			//(cmd[counter]).argv = eve_split_line(token2);
			counter++;
			token2 = strtok_r(NULL, EVE_TOK_CDELIM2,&saveptr2);
		}
		if(counter>1)
			{
			//	printf("fork\n");
				int gg = 0;
				while(gg<counter)
				{
					(cmd[gg]).argv = eve_split_line(list[gg]);
					gg++;
				}
				fork_pipes(counter,cmd);
			}
		else
		{
		//	printf("token2:%s\n",token);
			args=eve_split_line(token);
			compare();
		}
		token = strtok_r(NULL, EVE_TOK_CDELIM,&saveptr);
		counter=0;
		
	}
	

	return 1;
}
