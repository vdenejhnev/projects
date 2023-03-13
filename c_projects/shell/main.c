#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>


int **fd, Number_of_processes, *Number_of_arguments, flag_in, flag_append_out, flag_trunc_out, background_flag, back_num=0;
char *full_command=NULL, **simple_command, ***arguments, *file_in=NULL, *file_out=NULL;


void Allocate_all_memory_and_reinitialize_flags();
void Checking_syntax();
int Checking_the_background_mode();
void Cheking_input_and_output_redirection();
void Close_pipes();
void File_opening_error(int fd);
void Fork_call_error(pid_t pid);
void Free_all_allocated_memory();
void Initial_initializing_all_flags();
int Number_of_arguments_in_a_simple_command(char *string);
int Number_of_simbol(char *str, char ch);
void Open_pipes();
void Parsing_a_full_command_into_simple_commands();
void Parsing_simple_commands_into_arguments();
void Pipe_call_error(int p);
void Take_full_command();
void Waiting(int flag);




void File_opening_error(int fd)
{
    if (fd==-1)
    {
        fprintf(stderr, "Error: File opening failure \n");
        close(fd);
        exit(1);
    }
    return;
}

void Fork_call_error(pid_t pid)
{
	if (pid==-1)
	{
		fprintf(stderr, "Error: Failed to calling fork() \n");
		kill(0, SIGKILL);
		exit(1);
	}
}

void Pipe_call_error(int p)
{
	if (p==-1)
	{
		fprintf(stderr, "Error: Failed to calling pipe() \n");
		exit(1);
	}
}

void Checking_syntax()
{
	int flag=0;
	char *pointer_from=NULL, *pointer_to=NULL;
	if (Number_of_simbol(full_command, '&')>1)
	{
		fprintf(stderr, "Error in the command syntax \n");
		exit(1);
	}
	if (Number_of_simbol(full_command, '<')>1)
	{
		fprintf(stderr, "Error in the command syntax \n");
		exit(1);
	}
	if (Number_of_simbol(full_command, '>')>2)
	{
		fprintf(stderr, "Error in the command syntax \n");
		exit(1);
	}
	if (pointer_from=strrchr(full_command, '&'))
		for(int i=1;i<strlen(pointer_from);i++)
		{
			if (pointer_from[i]!=' ')
				flag=1;
		}
	if (flag)
	{
		fprintf(stderr, "Error in the command syntax \n");
		exit(1);
	}
	flag=0;
	pointer_from=full_command;
	if (Number_of_simbol(full_command, '|')>0)
	{
		pointer_to=strchr(pointer_from+1, '|');
		if (pointer_from[0]=='|')
		{
			fprintf(stderr, "Error in the command syntax \n");
			exit(1);
		}
		while (pointer_from!=strrchr(full_command, '|'))
		{
			for(int i=1;i<(strlen(pointer_from)-strlen(pointer_to));i++)
			{
				if ((pointer_from[i]!=' ')&&(pointer_from[i]!='<')&&(pointer_from[i]!='>')&&(pointer_from[i]!='&'))
					flag=1;
			}
			if (!flag)
			{
				fprintf(stderr, "Error in the command syntax \n");
				exit(1);
			}
			flag=0;
			pointer_from=strchr(pointer_to, '|');
			pointer_to=strchr(pointer_from+1, '|');
			if (!pointer_to)
				break;
		}
		for(int i=1;i<strlen(pointer_from);i++)
		{
			if ((pointer_from[i]!=' ')&&(pointer_from[i]!='<')&&(pointer_from[i]!='>')&&(pointer_from[i]!='&'))
				flag=1;
		}
		if (!flag)
		{
			fprintf(stderr, "Error in the command syntax \n");
			exit(1);
		}
	}
	else
	{
		for(int i=0;i<(strlen(pointer_from));i++)
		{
			if ((pointer_from[i]!=' ')&&(pointer_from[i]!='<')&&(pointer_from[i]!='>')&&(pointer_from[i]!='&'))
				flag=1;
		}
		if (!flag)
		{
			fprintf(stderr, "Error in the command syntax \n");
			exit(1);
		}
	}
}




void Open_pipes()
{
	int p;
	for(int i=0;i<Number_of_processes-1;i++)
	{
		p=pipe(fd[i]);
		Pipe_call_error(p);
	}
}

void Close_pipes()
{
	for(int i=0;i<Number_of_processes-1;i++)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

void Waiting(int flag)
{
	if (flag)
	{
		wait(NULL);
	}
	else
	{
		for(int i=0;i<Number_of_processes;i++)
		{
			wait(NULL);
		}
	}
}




void Initial_initializing_all_flags()
{
	flag_in=0;
	flag_append_out=0;
	flag_trunc_out=0;
	background_flag=0;
}

int Number_of_simbol(char *str, char ch)
{
	int k=0;
	int i=0;
	while (i<strlen(str))
	{
		if (str[i++]==ch)
			k+=1;
	}
	return k;
}

int Number_of_arguments_in_a_simple_command(char *string)
{
	char *copy;
	int i=0;
	copy=(char *)malloc((strlen(string)+1)*sizeof(char));
	strcpy(copy, string);
	char *str=strtok(copy, " ");
	while (str!=NULL)
	{
		if ((Number_of_simbol(str, '&'))||(Number_of_simbol(str, '<'))||(Number_of_simbol(str, '>')))
			break;
		str=strtok(NULL, " ");
		i+=1;
	}
	free(copy);
	return (i+1);
}

void Take_full_command()
{
	unsigned basis=4;
	unsigned size=0;
	unsigned i=0;
	char ch;
	full_command=(char*)malloc(size+=basis);
	if (!full_command)
	{
		fprintf(stderr, "Error: Failed to allocate memory \n");
		exit(1);
	}

	while (((ch=getchar())!=EOF)&&(ch!='\n')&&(ch!='\0'))
	{
		full_command[i++]=ch;
		if (i==size)
			full_command=(char*)realloc(full_command, size+=basis);
	}
	full_command[i]='\0';
	full_command=(char*)realloc(full_command, (i+1)*sizeof(ch));

	//printf("%s", full_command);
}

void Cheking_input_and_output_redirection()
{
	char *pointer;
	int j=1;
	if (Number_of_simbol(full_command, '>'))
	{
		if (Number_of_simbol(full_command, '>')==1)
			flag_trunc_out=1;
		else if (Number_of_simbol(full_command, '>')==2)
			flag_append_out=1;
		pointer=strrchr(full_command, '>');
		unsigned basis=4;
		unsigned size=0;
		unsigned i=0;
		char ch;
		file_out=(char*)malloc(size+=basis);
		if (!file_out)
		{
			fprintf(stderr, "Error: Failed to allocate memory \n");
			exit(1);
		}
		while ((ch=pointer[j++])==' '){}
		while ((ch!=' ')&&(ch!=EOF)&&(ch!='\n')&&(ch!='\0')&&(ch!='<')&&(ch!='&'))
		{
			file_out[i++]=ch;
			if (i==size)
				file_out=(char*)realloc(file_out, size+=basis);
			ch=pointer[j++];
		}
		file_out[i]='\0';
		file_out=(char*)realloc(file_out, (i+1)*sizeof(ch));
		if (!strlen(file_out))
		{
			fprintf(stderr, "Error in the command syntax \n");
			exit(1);
		}
	}
	j=1;
	if (Number_of_simbol(full_command, '<'))
	{
		flag_in=1;
		pointer=strrchr(full_command, '<');
		unsigned basis=4;
		unsigned size=0;
		unsigned i=0;
		char ch;
		file_in=(char*)malloc(size+=basis);
		if (!file_in)
		{
			fprintf(stderr, "Error: Failed to allocate memory \n");
			exit(1);
		}
		while ((ch=pointer[j++])==' '){}
		while ((ch!=' ')&&(ch!=EOF)&&(ch!='\n')&&(ch!='\0')&&(ch!='<')&&(ch!='&'))
		{
			file_in[i++]=ch;
			if (i==size)
				file_in=(char*)realloc(file_in, size+=basis);
			ch=pointer[j++];
		}
		file_in[i]='\0';
		file_in=(char*)realloc(file_in, (i+1)*sizeof(ch));
		if (!strlen(file_in))
		{
			fprintf(stderr, "Error in the command syntax \n");
			exit(1);
		}
	}
}

int Checking_the_background_mode()
{
	if (Number_of_simbol(full_command, '&'))
		return 1;
	else
		return 0;
}

void Parsing_a_full_command_into_simple_commands()
{
	int i=0;
	char *str=strtok(full_command, "|");
	while (str!=NULL)
	{
		simple_command[i]=(char *)malloc((strlen(str)+1)*sizeof(char));
		if (!simple_command[i])
		{
			fprintf(stderr, "Error: Failed to allocate memory \n");
			exit(1);
		}
		strcpy(simple_command[i], str);
		str=strtok(NULL, "|");
		i+=1;
	}
}

void Parsing_simple_commands_into_arguments()
{
	for(int j=0;j<Number_of_processes;j++)
	{
		int i=0;
		char *str=strtok(simple_command[j], " ");
		while (str!=NULL)
		{
			arguments[j][i]=(char *)malloc((strlen(str)+1)*sizeof(char));
			if (!arguments[j][i])
			{
				fprintf(stderr, "Error: Failed to allocate memory \n");
				exit(1);
			}


            strcpy(arguments[j][i], str);
			//printf("%s \n", str);
			//printf("[%d][%d] %s\n", j, i, arguments[j][i]);
			str=strtok(NULL, " ");
            i+=1;
			if (i==(Number_of_arguments[j]-1))
				break;
		}
		arguments[j][Number_of_arguments[j]-1]=NULL;
	}
}

void Allocate_all_memory_and_reinitialize_flags()
{
	Take_full_command();


	Checking_syntax();

	Cheking_input_and_output_redirection();

	background_flag=Checking_the_background_mode();

	Number_of_processes=Number_of_simbol(full_command, '|')+1;

	fd=(int **)malloc((Number_of_processes-1)*sizeof(int *));
	if (!fd)
	{
		fprintf(stderr, "Error: Failed to allocate memory \n");
		exit(1);
	}
	for(int i=0;i<Number_of_processes-1;i++)
	{
		fd[i]=(int *)malloc(2*sizeof(int));
		if (!fd[i])
		{
			fprintf(stderr, "Error: Failed to allocate memory \n");
			exit(1);
		}
	}

	simple_command=(char **)malloc((Number_of_processes)*sizeof(char *));
	if (!simple_command)
	{
		fprintf(stderr, "Error: Failed to allocate memory \n");
		exit(1);
	}

	Parsing_a_full_command_into_simple_commands();

	Number_of_arguments=(int *)malloc(Number_of_processes*sizeof(int));

	for(int i=0;i<Number_of_processes;i++)
		Number_of_arguments[i]=Number_of_arguments_in_a_simple_command(simple_command[i]);

	arguments=(char ***)malloc((Number_of_processes)*sizeof(char **));
	if (!arguments)
	{
		fprintf(stderr, "Error: Failed to allocate memory \n");
		exit(1);
	}
	for(int i=0;i<Number_of_processes;i++)
	{
		arguments[i]=(char **)malloc((Number_of_arguments[i])*sizeof(char *));
		if (!arguments[i])
		{
			fprintf(stderr, "Error: Failed to allocate memory \n");
			exit(1);
		}
	}

	Parsing_simple_commands_into_arguments();
}

void Free_all_allocated_memory()
{
	if (flag_in)
		free(file_in);
	if (flag_append_out||flag_trunc_out)
		free(file_out);
	if (full_command)
		free(full_command);
	for(int i=0;i<Number_of_processes-1;i++)
		free(fd[i]);
	free(fd);
	for(int i=0;i<Number_of_processes;i++)
		free(simple_command[i]);
	free(simple_command);
	for (int i=0;i<Number_of_processes;i++)
	{
		for(int j=0;j<Number_of_arguments[i]-1;j++)
			free(arguments[i][j]);
		free(arguments[i]);
	}
	free(arguments);
	free(Number_of_arguments);
}

int main(int argc, char **argv)
{
	int fd_in_bg, fd_out_bg, fd_in, fd_out;
	pid_t pid;
	char ch=' ';
	while (1)
	{
		printf("> ");
		Initial_initializing_all_flags();
		Allocate_all_memory_and_reinitialize_flags();
		if (!background_flag)
		{
			Open_pipes();

			for(int i=0;i<Number_of_processes;i++)
			{
				pid=fork();
				Fork_call_error(pid);
				if (pid==0)
				{
					if (i==0)
					{
						if (flag_in)
						{

                            if(arguments[i][0] == NULL) {
                                int item = 1;
                                while(arguments[i][item] != NULL) {
                                    //printf("%s\n", arguments[i][item]);
                                    //fflush(stdout);
                                    arguments[i][item - 1] = arguments[i][item];
                                    //printf("%s\n", arguments[i][item - 1]);
                                    item+=1;
                                }
                                arguments[i][item - 1] = NULL;
                            }


							fd_in=open(file_in, O_RDONLY, 0660);
							File_opening_error(fd_in);
							dup2(fd_in, 0);
							close(fd_in);

							//execvp(arguments[i][1], arguments[i]);
						}
						if (Number_of_processes==1)
						{
							if (flag_trunc_out || flag_append_out)
							{
								if (flag_trunc_out)
									fd_out=open(file_out, O_WRONLY|O_CREAT|O_TRUNC, 0660);
								else if (flag_append_out)
									fd_out=open(file_out, O_APPEND|O_CREAT|O_WRONLY, 0660);
								File_opening_error(fd_out);
								dup2(fd_out, 1);
								close(fd_out);
							}
                            execvp(arguments[i][0], arguments[i]);
                            fprintf(stderr, "Error: Failed to calling exec() \n");
                            exit(1);
						}
						dup2(fd[i][1], 1);
						Close_pipes();
						execvp(arguments[i][0], arguments[i]);
						fprintf(stderr, "Error: Failed to calling exec() \n");
						exit(1);
					}
					else if ((i>0)&&(i<(Number_of_processes-1)))
					{
						dup2(fd[i-1][0], 0);
						dup2(fd[i][1], 1);
						Close_pipes();
						execvp(arguments[i][0], arguments[i]);
						fprintf(stderr, "Error: Failed to calling exec() \n");
						exit(1);
					}
					else if (i==(Number_of_processes-1))
					{
						if (flag_trunc_out || flag_append_out)
						{
							if (flag_trunc_out)
								fd_out=open(file_out, O_WRONLY|O_CREAT|O_TRUNC, 0660);
							else if (flag_append_out)
								fd_out=open(file_out, O_APPEND|O_CREAT|O_WRONLY, 0660);
							File_opening_error(fd_out);
							dup2(fd_out, 1);
							close(fd_out);
						}
						dup2(fd[i-1][0], 0);
						Close_pipes();
						execvp(arguments[i][0], arguments[i]);
						fprintf(stderr, "Error: Failed to calling exec() \n");
						exit(1);
					}
				}
			}
			Close_pipes();
			Waiting(background_flag);
			Free_all_allocated_memory();
		} else {
			back_num+=1;
			pid=fork();
			Fork_call_error(pid);
			if (pid==0)
			{
				//Son process
				signal(SIGINT, SIG_IGN);
				pid=fork();
				Fork_call_error(pid);
				if (pid==0)
				{
					//Granson process
					signal(SIGINT, SIG_IGN);
					Open_pipes();
					for(int i=0;i<Number_of_processes;i++)
					{
						pid=fork();
						Fork_call_error(pid);
						if (pid==0)
						{
							if (i==0)
							{
								if (flag_in)
								{
								    if(arguments[i][0] == NULL) {
                                        int item = 1;
                                        while(arguments[i][item] != NULL) {
                                            //printf("%s\n", arguments[i][item]);
                                            //fflush(stdout);
                                            arguments[i][item - 1] = arguments[i][item];
                                            //printf("%s\n", arguments[i][item - 1]);
                                            item+=1;
                                        }
                                        arguments[i][item - 1] = NULL;
                                    }

									fd_in=open(file_in, O_RDONLY, 0660);
									File_opening_error(fd_in);
									dup2(fd_in, 0);
									close(fd_in);
									execlp(arguments[i][0], arguments[i][0], NULL);
								}
								else
								{
									fd_in_bg=open("/dev/null", O_RDONLY, 0666);
									File_opening_error(fd_in_bg);
									dup2(fd_in_bg, 0);
									close(fd_in_bg);
								}
								if (Number_of_processes==1)
								{
									if (flag_trunc_out || flag_append_out)
									{
										if (flag_trunc_out)
											fd_out=open(file_out, O_WRONLY|O_CREAT|O_TRUNC, 0660);
										else if (flag_append_out)
											fd_out=open(file_out, O_APPEND|O_CREAT|O_WRONLY, 0660);
										File_opening_error(fd_out);
										dup2(fd_out, 1);
										close(fd_out);
									}
									else
									{
										fd_out_bg=open("/dev/null", O_WRONLY, 0666);
										File_opening_error(fd_out_bg);
										dup2(fd_out_bg, 1);
										close(fd_out_bg);
									}
										execvp(arguments[i][0], arguments[i]);
										fprintf(stderr, "Error: Failed to calling exec() \n");
										exit(1);
								}
								dup2(fd[i][1], 1);
								Close_pipes();
								execvp(arguments[i][0], arguments[i]);
								fprintf(stderr, "Error: Failed to calling exec() \n");
								exit(1);
							}
							else if ((i>0)&&(i<(Number_of_processes-1)))
							{
								dup2(fd[i-1][0], 0);
								dup2(fd[i][1], 1);
								Close_pipes();
								execvp(arguments[i][0], arguments[i]);
								fprintf(stderr, "Error: Failed to calling exec() \n");
								exit(1);
							}
							else if (i==(Number_of_processes-1))
							{
								if (flag_trunc_out || flag_append_out)
								{
									if (flag_trunc_out)
										fd_out=open(file_out, O_WRONLY|O_CREAT|O_TRUNC, 0660);
									else if (flag_append_out)
										fd_out=open(file_out, O_APPEND|O_CREAT|O_WRONLY, 0660);
									File_opening_error(fd_out);
									dup2(fd_out, 1);
									close(fd_out);
								}
								else
								{
									fd_out_bg=open("/dev/null", O_WRONLY, 0666);
									File_opening_error(fd_out_bg);
									dup2(fd_out_bg, 1);
									close(fd_out_bg);
								}
								dup2(fd[i-1][0], 0);
								Close_pipes();
								execvp(arguments[i][0], arguments[i]);
								fprintf(stderr, "Error: Failed to calling exec() \n");
								exit(1);
							}
						}
					}
					Close_pipes();
					Waiting(0);
					Free_all_allocated_memory();
					exit(0);
				}
				exit(0);
			}
			printf("[%d] background process was started by a process with PID = %d \n", back_num, pid);
			Waiting(background_flag);
		}
	}
	exit(0);
}
