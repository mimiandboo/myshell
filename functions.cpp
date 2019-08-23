#include "general.h"

PipeRedirect parse(int argc, char** argv, char** cmd1, char** cmd2){
	PipeRedirect result = NEITHER;

	int fork = -1;

	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], "|") == 0){
			result = PIPE;
			fork = i;
		}
		else if(strcmp(argv[i], ">>") == 0){
			result = REDIRECT;
			fork = i;
		}
	}
	
	if(result != NEITHER){
		for(int i = 0; i < fork; i++){
			cmd1[i] = argv[i];
		}
		
		int count = 0;
		for(int i = fork + 1; i < argc; i++){
			cmd2[count] = argv[i];
			count++;
		}

		cmd1[fork] = NULL;
		cmd2[count] = NULL;
	}

	return result;
}

void pipe_command(char** cmd1, char** cmd2){
	int descriptors[2];
	pipe(descriptors);
	pid_t pid;

	if(fork() == 0){
		dup2(descriptors[0], 0);
		close(descriptors[1]);
		
		execvp(cmd2[0], cmd2);
		perror("execvp failed");
	}
	else if((pid = fork()) == 0){
		dup2(descriptors[1], 1);
		close(descriptors[0]);

		execvp(cmd1[0], cmd1);
		perror("execvp failed");
	}
	else{
		waitpid(pid, NULL, 0);
	}
}

int read_args(char **argv){
	char *cstr;
	string arg;
	int argc = 0;

	while(cin >> arg){
		if(quit(arg)){
			cout << "exiting shell.\n";
			exit(0);
		}
		
		cstr = new char[arg.size() + 1];
		strcpy(cstr, arg.c_str());
		argv[argc] = cstr;
		
		argc++;
		
		if(cin.get() == '\n'){
			break;
		}
	}

	argv[argc] = NULL;
	return argc;
}

void redirect_command(char** cmd, char** file){
	int descriptors[2];
	int count;
	int fd;
	char c;
	pid_t pid;

	pipe(descriptors);

	if(fork() == 0){
		fd = open(file[0], O_RDWR | O_CREAT, 0666);
		
		if(fd < 0){
			printf("error: %s\n", strerror(errno));
			return;
		}
		
		dup2(descriptors[0], 0);
		close(descriptors[1]);
	
		while((count = read(0, &c, 1)) > 0){
			write(fd, &c, 1);
		}

		execlp("echo", "echo", NULL);
	}
	else if((pid = fork()) == 0){
		dup2(descriptors[1], 1);
		close(descriptors[0]);
		
		execvp(cmd[0], cmd);
		perror("execvp failedd");
	}
	else{
		waitpid(pid, NULL, 0);
		close(descriptors[0]);
		close(descriptors[1]);
	}
}

void run_command(int argc, char** argv){
	pid_t pid;
	const char *amp;
	amp = "&";
	bool found_amp = false;
	
	if(strcmp(argv[argc - 1], amp) == 0){
		found_amp = true;
	}

	pid = fork();
	
	if(pid < 0){
		perror("error (pid < 0)");
	}
	else if(pid == 0){
		if(found_amp){
			argv[argc - 1] = NULL;
			argc--;
		}
		
		execvp(argv[0], argv);
		perror("execvp error");
	}
	else if(!found_amp){
		waitpid(pid, NULL, 0);
	}
}

bool quit(string input){
	for(int i = 0; i < input.length(); i++){
		input[i] = tolower(input[i]);
	}
	
	return (input == "quit" || input == "exit");
}
