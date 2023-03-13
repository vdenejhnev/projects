// need _GNU_SOURCE for the pipe2()
#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX 100
#define MAXCMD 10

int main() {
  char user_input[MAX];
  char *cmds[MAX/2 + 1]; /* commands, separated with '|' */
  char *args[MAXCMD][MAX/2 + 1]; /* commands + args */
  int p, s, j, k, i = 0, c = 0;
  int bg = 0;	// bg = 1 if background execution
  pid_t pid[MAXCMD];
  int fd[2] = { 0, 1 };

  while(1) {

    printf("> ");
    fflush(stdout);

    bg = 0;

    user_input[0] = '\0';

    scanf ("%[^\n]%*c", user_input);

    if (user_input[0] == '\n'||user_input[0] == '\0') exit(0);

    c = i = 0;
    cmds[c] = strtok(user_input,"|");
    while (cmds[c] != NULL) {
       c++; cmds[c] = strtok(NULL, "|");
    }
    if (c>MAXCMD) {
	fprintf(stderr,"Error: number of commands (%d) exceeds max (%d)\n",c,MAXCMD);
	exit(-1);
    }

    for (j=0;j<c;j++) {
       // printf("%d   %s\n",j,cmds[j]);
       i = 0;
       args[j][i] = strtok(cmds[j]," ");
       while (args[j][i] != NULL) {
	  i++; args[j][i] = strtok(NULL, " ");
       }
       // for (k=0;k<i;k++) printf(" - %s\n",args[j][k]); printf("\n");
    }

    if (args[0][0] == NULL) exit(0);
    if (strcmp(args[0][0], "exit") == 0) exit(0);

    if(strcmp(args[c-1][i-1], "&") == 0) {
        args[c-1][i-1] = NULL;
        bg = 1;
    }

    // fprintf(stderr,"\nbackground = %d\n\n",bg); fflush(stderr);

    for ( p = 0 ; p < c ; p++) {
	  int fc[2] = { 0, 1 };
	  // fprintf(stderr,"%d %s\n",p,args[p][0]); fflush(stderr);
	  if ( c - p != 1 ) {
	    pipe2(fc, O_CLOEXEC);
	  }
	  pid[p] = fork();
	  if (pid[p] < 0) { fprintf(stderr,"Fork %d failed!\n",p); _exit(-1); }
	  if (!pid[p]) {
             char *ff;
	     int io;
	     int mod = 0; // 1 = read, 2 = write, 3 = append
	     signal(SIGINT, SIG_IGN);
	     // fprintf(stderr,"p = %d, pid = %d\n",p,getpid()); fflush(stderr);
	     for (j = 0; j < MAX; j++) {
	        ff = args[p][j];
		if (ff == (char *)NULL) break;
		if (*ff == '<') {
		  ff = args[p][j+1];
		  if (ff == (char *)NULL) { fprintf(stderr,"Error: expect file name after input redirect!\n"); _exit(-1); }
		  mod = 1; args[p][j] = '\0' ; break;
		} else if (*ff == '>') {
		  mod = 2; if (*(ff+1) == '>') mod += 1;
		  ff = args[p][j+1];
		  if (ff == (char *)NULL) { fprintf(stderr,"Error: expect file name after output redirect!\n"); _exit(-1); }
		  args[p][j] = '\0' ;
		  break;
		}
		// fprintf(stderr,"- %s\n",ff); fflush(stderr);
	     }

	     printf("%s", ff);
	     fflush(stdout);
	     switch (mod) {
		     case 0: dup2(fd[0], STDIN_FILENO);
			     dup2(fc[1], STDOUT_FILENO);
			     break;
		     case 1: if ((io = open(ff, O_RDONLY)) < 0) {
				     fprintf(stderr,"Error: failed to read from \"%s\"\n",ff);
				     _exit(-1);
			     }
			     dup2(io,fd[0]);
			     dup2(fc[1], STDOUT_FILENO);
			     break;
		     case 2: if ((io = open(ff, O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0) {
				     fprintf(stderr,"Error: failed to write to \"%s\"\n",ff);
				     _exit(-1);
			     }
			     dup2(fd[0], STDIN_FILENO);
			     dup2(io, fc[1]);
			     break;
		     case 3: if ((io = open(ff, O_WRONLY | O_CREAT | O_APPEND, 0777)) < 0) {
				     fprintf(stderr,"Error: failed to append to \"%s\"\n",ff);
				     _exit(-1);
			     }
			     dup2(fd[0], STDIN_FILENO);
			     dup2(io, fc[1]);
			     break;
		    default: _exit(-1);
	     }
             // if (mod)  {fprintf(stderr,"io from or to: %s as %d\n",ff,io); fflush(stderr);}
	     s = execvp(args[p][0],args[p]);
	     if (s<0) {
		     fprintf(stderr,"failed to execvp %s\n",args[p][0]);
		     fflush(stderr);
		     _exit(-1);
	     }
	  }
	  // parent only
	  if (fc[1] != 1) close(fc[1]);
	  if (fd[0] != 0) close(fd[0]);
	  fd[0] = fc[0];
    }
    if (bg) {signal(SIGCHLD,SIG_IGN); bg=0;} else for ( p = 0 ; p < c ; p++) waitpid(pid[p],NULL,0);

  } // while


}

