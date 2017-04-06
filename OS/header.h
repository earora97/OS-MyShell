#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/resource.h>
#include<pwd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<signal.h>

#define EVE_TOK_BUFSIZE 64
#define EVE_TOK_DELIM " \t\n\r"
#define EVE_TOK_CDELIM ";\n"
typedef struct running_jobs
{
  char jobName[100];
  pid_t pid;
  struct running_jobs * next;
}running_jobs;

void sig_chld(int signo);
int eve_launch(char **args);
char *eve_read_line(void);
char **eve_split_line(char *line);
void compare();
int eve_split_command(char* line);
int make_int(char * str);
void function();
void function2();
void function3();
void my_jobs();
void my_fg(char ** args);
void my_killallbg();
int add_job(pid_t pid, char * name);
int delete_job(pid_t pid);
void my_quit();
void my_kjob(char **args);
void ctrlC();
void ctrlD();