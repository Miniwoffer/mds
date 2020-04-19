#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "markdown.h"


int pipe_fd[2];
pid_t pid;

int argc = 0;
char **args = NULL;

void cmd_add(char *cmd)
{
	argc++;
	args = reallocarray(args, sizeof(char*), argc+1);
	args[argc-1] = strdup(cmd);
	args[argc] = NULL;
}

void cmd_start()
{
	if(!argc) return;
	pipe(pipe_fd);
	fflush(stdout);
	pid = fork();

	if(pid == 0)
	{
		//child
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execvp(args[0], args);
		exit(0);
	}
	else if(pid > 0)
	{
		//parent
		close(pipe_fd[0]);
	} else {
		// Fork failed
		printf("{Gerror]: %s\n",strerror(errno));
	}

}

void cmd_write(char *buf, size_t count)
{
	if(argc) {
		write(pipe_fd[1], buf, count);
	}
	else{
		printf("%s",buf);
	}
}

void cmd_stop()
{
	if(!argc) {
		printf("\n```\n");
		return;
	}
	close(pipe_fd[1]);
	wait(0);
	waitpid(pid, NULL, 0);
	// Free cmd data
	for(int i = 0; i < argc; i++){
		free(args[i]);
	}
	free(args);
	args = NULL;
	argc = 0;
	fflush(stdout);
	 printf("\n```\n");
}

int main(void)
{
	while(yyparse());
	return 0;
}
