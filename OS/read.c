//READ
/* #define EVE_RL_BUFSIZE 1024
   char *eve_read_line(void)
   {
   int bufsize=EVE_RL_BUFSIZE;
   int position=0;
   char *buffer=malloc(sizeof(char)*bufsize);
   int c;

//unable to allocate buffer
if(!buffer)
{
fprintf(stderr, "eve: allocation error\n");
exit(1);
}

//read character by character
while(1)
{
c=getchar();
//end of list of arguments, make last character=null
if(c==EOF||c=='\n')
{
buffer[position]='\0';
return buffer;
}
//keep reading
else
buffer[position]=c;

position++;

//we exceeded the buffer, reallocate it
if(position >= bufsize)
{
bufsize += EVE_RL_BUFSIZE;
buffer = realloc(buffer,bufsize);
if(!buffer)
{
fprintf(stderr, "eve: allocation error\n");
exit(1);
}
}
}
}
//END READING
 */
