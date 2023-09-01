// implement a linux shell in c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void exe_cmd(char *cmd)
{
  // Tokenize the command into arguments
  char *args[100];
  int arg_count = 0;
  char *token = strtok(cmd, " \t\n");
  while (token != NULL)
  {
    args[arg_count++] = token;
    token = strtok(NULL, " \t\n");
  }
  args[arg_count] = NULL;

  // Create a child process to execute the command
  pid_t pid = fork();
  if (pid == -1)
  {
    perror("fork");
    exit(1);
  }
  else if (pid == 0)
  {
    // Child process
    execvp(args[0], args);
    perror("execvp");
    exit(1);
  }
  else
  {
    // Parent process
    int status;
    waitpid(pid, &status, 0);
  }
}

int main()
{
  char input[MAX_INPUT_SIZE];

  while (1)
  {
    printf("Shell> ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
      perror("fgets");
      exit(1);
    }

    // Remove the newline character
    input[strlen(input) - 1] = '\0';

    if (strcmp(input, "exit") == 0)
    {
      printf("Exiting the shell.\n");
      break;
    }

    exe_cmd(input);
  }

  return 0;
}
