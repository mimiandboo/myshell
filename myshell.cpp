#include <iostream>
#include <cstring>
#include <stdio.h>
#include <array>
#include "general.h"

using namespace std;

int main(){
	char *argv[MAX], *cmd1[MAX], *cmd2[MAX];

	PipeRedirect pipe_redirect;
	int argc;

	while(true){
		cout << "myshell $\n";
		argc = read_args(argv);
		
		pipe_redirect = parse(argc, argv, cmd1, cmd2);

		if(pipe_redirect == PIPE){
			pipe_command(cmd1, cmd2);
		}
		else if(pipe_redirect == REDIRECT){
			redirect_command(cmd1, cmd2);
		}
		else{
			run_command(argc, argv);
		}

		for(int i = 0; i < argc; i++){
			argv[i] = NULL;
		}

				

		//char array[100];
		//strcpy(array, input.c_str());
	
		//char * pch;
		//pch = strtok(array, " ;|");
	
		/*while(pch != NULL){
			cout << pch << "\n";
			pch = strtok(NULL, " ;|");
		}
	
		cout << envp[9] << "\n";*/
	}
	
	return 0;
}
