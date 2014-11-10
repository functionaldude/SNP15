#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int running;
int exit_code;

char command[256];
char args[10][256];
char dir_name[256];

struct pipe_desc{
  int fds[2];
  char filename[255];
  char mode; //w -> write, a -> append
  char direction; //l -> '>'; r -> '<'; i -> '|'
};


void handle_dir(char * input, int mode){
  if (mode == 0) {
    unsigned long len = strlen(input);
    if (input[len-1] != '/') {
      input[len] ='/';
      input[len+1] = '\0';
      len++;
    }
    if (input[0] != '.' && input[1] != '/') {
      for (int i = (int)strlen(input); i != -2; i--) {
        input[i+2] = input[i];
      }
      input[0] = '.';
      input[1] = '/';
    }
  }
  else if (mode == 1){
    int i = (int)strlen(input);
    input[--i] = '\0';
    while (input[i] != '/') {
      input[i] = '\0';
      i--;
    }
  }
}

void handle_command(char* buffer,int buffer_size)
{
  int c = 0;
  int argsCount = -1;
  int lastIndex = 0;

  for(c = 0; c < buffer_size; c++)
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

  struct pipe_desc* pipes = NULL;
  int pipe_count = 0;
  for (int i = 0; i < argsCount; i++) {
    if (strcmp(args[i], "<") == 0) {
      if (pipes == NULL) {
        pipes = calloc(1, sizeof(struct pipe_desc));
      } else {
        pipes = realloc(pipes, sizeof(pipes) + sizeof(struct pipe_desc));
      }
      pipes[pipe_count].direction = 'l';
      pipes[pipe_count].mode = 'w';
      strcpy(pipes[pipe_count].filename, args[i+1]);
      pipe_count++;
      break;
    }
    else if (strcmp(args[i], "<<") == 0){
      if (pipes == NULL) {
        pipes = calloc(1, sizeof(struct pipe_desc));
      } else {
        pipes = realloc(pipes, sizeof(pipes) + sizeof(struct pipe_desc));
      }
      pipes[pipe_count].direction = 'l';
      pipes[pipe_count].mode = 'a';
      strcpy(pipes[pipe_count].filename, args[i+1]);
      pipe_count++;
      break;
    }
    else if (strcmp(args[i], ">") == 0){
      if (pipes == NULL) {
        pipes = calloc(1, sizeof(struct pipe_desc));
      } else {
        pipes = realloc(pipes, sizeof(pipes) + sizeof(struct pipe_desc));
      }
      pipes[pipe_count].direction = 'r';
      pipes[pipe_count].mode = 'w';
      strcpy(pipes[pipe_count].filename, args[i+1]);
      pipe_count++;
      break;
    }
    else if (strcmp(args[i], ">>") == 0){
      if (pipes == NULL) {
        pipes = calloc(1, sizeof(struct pipe_desc));
      } else {
        pipes = realloc(pipes, sizeof(pipes) + sizeof(struct pipe_desc));
      }
      pipes[pipe_count].direction = 'r';
      pipes[pipe_count].mode = 'a';
      strcpy(pipes[pipe_count].filename, args[i+1]);
      pipe_count++;
      break;
    }
    else if (strcmp(args[i], "|") == 0){
      if (pipes == NULL) {
        pipes = calloc(1, sizeof(struct pipe_desc));
      } else {
        pipes = realloc(pipes, sizeof(pipes) + sizeof(struct pipe_desc));
      }
      pipes[pipe_count].direction = 'i';
      pipes[pipe_count].mode = 0x00;
      strcpy(pipes[pipe_count].filename, args[i+1]);
      pipe_count++;
      break;
    }
  }

  if (strcmp(command, "exit") == 0){
    c=4;
    while (buffer[c] ==' '){
      c++;
    }
    exit_code=atoi(&buffer[c]);
    printf("Exiting Shell with exit_code %d\n",exit_code); 
    running=0;
  }
  else if (strcmp(command, "cd") == 0){
    if (strcmp(args[0], "..") == 0) {
      handle_dir(dir_name, 1);
    } else {
      strcpy(dir_name, args[0]);
      handle_dir(dir_name, 0);
    }
    chdir(dir_name);
    getcwd(dir_name, sizeof(dir_name));
  }
  else if (strcmp(command, "") != 0){
    int pid = fork();
    switch (pid) {
      case -1:
        //fork error
        perror("FORK ERROR");
        return;
      case 0:
        //child
        for (int i = 0; i < pipe_count; i++) {
          if (pipes[i].direction != 'i') {
            FILE* fp = fopen(pipes[i].filename, "w");
            if (fp == NULL) {
              perror("Error opening file");
              exit(-1);
            }
            pipes[i].fds[0] = fileno(fp);
            if (pipes[pipe_count].direction == 'l') {
              dup2(pipes[i].fds[0], STDIN_FILENO);
            } else {
              dup2(pipes[i].fds[0], STDOUT_FILENO);
            }
          } else {
            pipe(pipes[i].fds);
            pid = fork();
            switch (pid) {
              case -1:
                perror("Fork error");
                exit(-1);
                break;
              case 0:
                //second
                close(pipes[i].fds[1]);
                dup2(STDIN_FILENO, pipes[i].fds[0]);
                execlp(pipes[i].filename, pipes[i].filename);
              default:
                close(pipes[i].fds[0]);
                dup2(STDOUT_FILENO, pipes[i].fds[1]);
                break;
            }
          }
        }
        //command exec
        argsCount -= 2*pipe_count;
        switch (argsCount) {
          case 0:
            execlp(command, command, NULL);
            break;
          case 1 :
            execlp(command, command, args[0], NULL);
            break;
          case 2:
            execlp(command, command, args[0], args[1], NULL);
            break;
          case 3:
            execlp(command, command, args[0], args[1], args[2], NULL);
            break;
          case 4:
            execlp(command, command, args[0], args[1], args[2], args[3], NULL);
            break;
          case 5:
            execlp(command, command, args[0], args[1], args[2], args[3], args[4], NULL);
            break;
          case 6:
            execlp(command, command, args[0], args[1], args[2], args[3], args[4], args[5], NULL);
            break;
          case 7:
            execlp(command, command, args[0], args[1], args[2], args[3], args[4], args[5], args[6], NULL);
            break;
          case 8:
            execlp(command, command, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], NULL);
            break;
          case 9:
            execlp(command, command, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], NULL);
            break;
          default:
            execlp(command, command, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], NULL);
            break;
        }
        exit(0);
      default:
        //parent
        wait(&pid);
        break;
    }
  }
}

int main(int argc, char *argv[]) 
{
  char buffer[256];
  memset(buffer, 0x00, sizeof(buffer));
  memset(dir_name, 0x00, sizeof(dir_name));
  memset(command, 0x00, sizeof(command));
  char cwd[256]="/";
  exit_code=0;
  running = 1;
  getcwd(dir_name, sizeof(dir_name)); //get working directory
  printf("SWEB-Pseudo-Shell starting...\n");
  do
  {
    printf("%s %s%s","SWEB:",cwd,"> ");
    fgets(buffer,255,stdin);
    buffer[255]=0;
    handle_command(buffer,sizeof(buffer));
    memset(buffer, 0x00, sizeof(buffer));
  }while (running);

  return exit_code;
}
