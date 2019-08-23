#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

const int MAX = 100;

enum PipeRedirect {PIPE, REDIRECT, NEITHER};

PipeRedirect parse(int, char**, char**, char**);

void pipe_command(char**, char**);

int read_args(char**);

void redirect_command(char**, char**);

void run_command(int, char**);

bool quit(string);
