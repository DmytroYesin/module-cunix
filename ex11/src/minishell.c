#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../include/hash.h"
#include "../include/linked_list.h"
#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

int fexit(hashtable_t *env, char **args);
int fenv(hashtable_t *env, char **args);
int fexport(hashtable_t *env, char **args);
int fecho(hashtable_t *env, char **args);

char *builtin_str[] = {
  "exit",
  "env",
  "export",
  "echo"
};

int fecho(hashtable_t *env, char **args)
{
  int n = 1;
  while(args[n] != NULL)
  {
    if(args[n][0] == '$')
    {
      write(1, hash_get(env, args[n]+1), strlen(args[n])+1);
      n++;
      continue;
    }
    write(1, args[n], strlen(args[n])+1);
    n++;
  }
  write(1, "\n", 1);
  return 1;
}

int fexport(hashtable_t *env, char **args)
{
  char *var, *var_point, *value_point;
  value_point = strtok(args[1], "=");
  var = malloc((strlen(value_point)+1)* sizeof(char));
  strcpy(var, value_point);
  while (value_point != NULL)
  {
    var_point = malloc((strlen(value_point)+1)*sizeof(char));
    strcpy(var_point, value_point);
    value_point = strtok(NULL, "=");
  }
  if (!strcmp(var, var_point))
    return 1;

      hash_set(env, var, var_point);
  write(1,"\n",1);
  return 1;
}

int fenv(hashtable_t *env, char **args)
{
  hash_print(env);
  write(1,"\n",1);
  return 1;
}


int num_b_ins()
{
  return sizeof(builtin_str) / sizeof(char *);
}


int fexit(hashtable_t *env, char **args)
{
  return 0;
}

int f_lok(hashtable_t *env, char **args)
{
  pid_t pid;
  int status;
  pid = fork();
  if (pid == 0)
  {
    if (execvp(args[0], args) == -1)
    {
      perror("msh");
    }
    exit(EXIT_FAILURE);
  }
  else if (pid < 0)
  {
    perror("msh");
  }
  else
  {
    do
    {
      waitpid(pid, &status, WUNTRACED);
    }
    while(!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}

int m_execute(hashtable_t *env, char **args)
{
  if (args[0] == NULL)
  {
    return 1;
  }
    if (strcmp(args[0], builtin_str[0]) == 0)
    {
      return fexit(env, args);
    }
    else if (strcmp(args[0], builtin_str[1]) == 0)
    {
      return fenv(env, args);
    }
    else if (strcmp(args[0], builtin_str[2]) == 0)
    {
      return fexport(env, args);
    }
    else if (strcmp(args[0], builtin_str[3]) == 0)
    {
      return fexport(env, args);
    }
 return f_lok(env, args);
}

char *m_read(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int sym;
  if(!buffer)
  {
    fprintf(stderr, "allocation error\n");
    exit(EXIT_FAILURE);
  }
  while(1)
  {
    sym = getchar();
    if (sym == EOF)
    {
      exit(EXIT_SUCCESS);
    } else if (sym == '\n')
    {
      buffer[position] = '\0';
      return buffer;
    }
    else
    {
      buffer[position] = sym;
    }
    position++;
    if (position >= bufsize)
    {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer)
      {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

char **split_l(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, pos = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens)
  {
    fprintf(stderr, "allocation error\n");
    exit(EXIT_FAILURE);
  }
  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL)
  {
    tokens[pos] = token;
    pos++;
    if (pos >= bufsize)
    {
      bufsize += LSH_TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens)
      {
		  free(tokens_backup);
      fprintf(stderr, "allocation error\n");
      exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[pos] = NULL;
  return tokens;
}

int main(int argc, char **argv, char **envv)
{
char *line;
char **args;
hashtable_t *ht;
ht = hash_create(128);
int status;
do {
   printf("$_> ");
   line = m_read();
   args = split_l(line);
   status = m_execute(ht, args);
   free(line);
   free(args);
   }
while (status);
  return EXIT_SUCCESS;
}

