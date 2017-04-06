void compare()
{
	flag=0;
	n = count;
	printf("count:%d\n", n);
	while(n>0)
	{
		printf("g:%d\n",n);
		if(strcmp(args[n],">")==0)
			function();
		else if(strcmp(args[n],">>")==0)
			function2();
		else if(strcmp(args[n],"<")==0)
			function3();
		n--;
	}
	if(flag==0)
	{
		if(strcmp(args[0],"fg")==0)
		{
			my_fg(args);
		}
		else if(strcmp(args[0],"kjob")==0)
        {
        	my_kjob(args);
        }
		if(strcmp(args[0],"quit")==0)
		{
			my_quit();
		}
		if(strcmp(args[0],"killallbg")==0)
		{
			my_killallbg();
		}
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
		else if(strcmp(args[0],"pinfo")==0)
		{
			int c;
			char buf[80],buff[20],buff2[20],pid[20];
			strcpy(pid,args[1]);
			strcpy(buff,"/proc/");
			strcpy(buff2,"/cmdline");
			strcat(buff,pid);
			strcat(buff,buff2);
			//	printf("buff::%s\n",buff);
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
