#include<header.h>
extern char **args;
int chldrun=0;
int count=0;
int foreground=0;

void sig_chld(int signo)
{
	chldrun=0;
	pid_t pid;
	int stat;
	pid=wait(&stat);
	if(pid==-1)
		return;
	printf("Process with pid %d terminated now\n",pid);
	delete_job(pid);
	return;
}

char **eve_split_line(char *line)
{

	int bufsize=EVE_TOK_BUFSIZE, position=0;
	char **tokens=malloc(bufsize*sizeof(char *));
	char *token;
	char * dfgh;
//	strcpy(dfgh,line);

	//can't allocate buffer
	if(!tokens)
	{
		fprintf(stderr, "Allocation\n");
		exit(1);
	}

	//save arguments in a 2-d array tokens
	token=strtok(line, EVE_TOK_DELIM);
	while(token!=NULL)
	{
		tokens[position]=token;
		//	printf("%s:",token);
		position++;

		//if buffer full, reallocate buffer
		if(position>=bufsize)
		{
			bufsize += EVE_TOK_BUFSIZE;
			tokens=realloc(tokens, bufsize*sizeof(char*));
			if(!tokens)
			{
				fprintf(stderr, "Allocation error\n");
				exit(1);
			}
		}

		//read next argument
		token=strtok(NULL, EVE_TOK_DELIM);
	}
//	printf("Allo%s\n",dfgh);
	tokens[position]=NULL;
	count=position-1;
	//	printf("\n");
	return tokens;
}

int eve_launch(char **args)
{
	pid_t pid,wpid;
	int status,background=0,i;
	if(chldrun==0){
		signal(SIGCHLD, sig_chld);
		chldrun=1;}
	pid=fork();

		for(i=0;args[i]!=NULL || args[i]!='\0';i++)
		{
			if(strcmp(args[i],"&")==0)
			{
				background=1;
				args[i]=NULL;
			}			
		}


	//childprocess
	if(pid==0)
	{
		if(execvp(args[0],args)==-1)
			fprintf(stderr,"error executing the command\n");
		chldrun=0;
	}
	//couldn't fork
	else if(pid<0)
	{
		fprintf(stderr,"error: fork\n");
		chldrun=0;
	}

	//parent process
	else
	{
		
		//int i;
		//search if '&' is given as an argument
		for(i=0;args[i]!=NULL || args[i]!='\0';i++)
		{
			if(/*strcmp(args[i],"&")==0*/background)
			{
				add_job(pid,args[0]);
				//chldpid=pid;
				return 1;
			}
			else
				foreground = 1;
		}

		do{
			wpid=waitpid(pid, &status,WUNTRACED);
		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
		chldrun=0;
	}

	return 1;

}


char *eve_read_line(void)
{
	char *line = NULL;
	ssize_t bufsize = 0;
	int temp = getline(&line, &bufsize, stdin);
	if(temp== -1)
		ctrlD();
	return line;
}

running_jobs *rjobs=NULL;
int add_job(pid_t pid, char * name)
{
	running_jobs *new=(running_jobs*)malloc(sizeof(running_jobs));
	new->pid=pid;
	strcpy(new->jobName,name);
	new->next=NULL;
	if (rjobs==NULL)
	{
		rjobs=new;
	}
	else
	{
		running_jobs *temp=rjobs;

		for (;temp->next!=NULL;temp=temp->next);
		temp->next=new;
	}
}

int delete_job(pid_t pid)
{
	foreground=0;
	if (rjobs==NULL) {
		return 1;
	}
	if (rjobs->pid==pid) {
		running_jobs *del=rjobs;
		rjobs=rjobs->next;
		free(del);
		return 0;
	}
	running_jobs *temp=rjobs,*prev;
	for (prev=rjobs;temp->pid!=pid || temp==NULL;temp=temp->next)
	{
		if (temp!=rjobs) {
		prev=prev->next;
	}
	}
	//running_jobs *del=temp->next;
	if(temp!=NULL)
	{
	prev->next=temp->next;
	free(temp);
}
}
