#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int running;
int exit_code;

char command[256];
char executable[256];
char args[10][256];

void handle_command(char* buffer,int buffer_size)
{
  int c = 0;
  int argsCount = -1;
  int lastIndex = 0;

  for(c=0; c<buffer_size; c++)
  {
    if(argsCount > 10)
    {
      argsCount = 10;
      printf("Argument Count is limited to 10 (no dynamic memory allocation) all other arguments will be ignored\n");
      break;
    }
    if(buffer[c] == '\r' || buffer[c] == '\n' || buffer[c] == ' ')
    {
      if(argsCount == -1)
      {
        memcpy(command, buffer + lastIndex, c - lastIndex);
        command[c - lastIndex] = 0;
      }
      else
      {
        memcpy(args[argsCount], buffer + lastIndex, c - lastIndex);
        args[argsCount][c - lastIndex] = 0;
      }
      argsCount++;
      lastIndex = c + 1;
      
      
    }
  }

  if (strcmp(command, "exit") == 0)
  {
    c=4;
    while (buffer[c] ==' ')
      c++;
    exit_code=atoi(&buffer[c]);
    printf("Exiting Shell with exit_code %d\n",exit_code); 
    running=0;
  }
  else if (strcmp(command, "") != 0)
  {
    printf("TODO: fork/exec\n");
  }
}

int main(int argc, char *argv[]) 
{
  char buffer[256];
  char cwd[256]="/";
  exit_code=0;
  running = 1;
  printf("SWEB-Pseudo-Shell starting...\n");
  do 
  {
    printf("%s %s%s","SWEB:",cwd,"> ");
    fgets(buffer,255,stdin);
    buffer[255]=0;
    handle_command(buffer,256);
    int a;
    for (a = 0; a < 256; ++a)
      buffer[a]=0;
    
  } while (running);

  return exit_code;
}
