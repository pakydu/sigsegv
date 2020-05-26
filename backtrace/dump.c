#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <execinfo.h>


#define BACKTRACE_SIZE 16

void dump(void)
{
    int j, nptrs;

    void *buffer[BACKTRACE_SIZE];
    char **strings;

char buff[64] = {0x00};
	
sprintf(buff,"cat /proc/%d/maps", getpid());
	
system((const char*) buff);

    nptrs = backtrace(buffer, BACKTRACE_SIZE);
    printf("backtrace() returned %d address\n", nptrs);

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL)
    {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < nptrs; j++)
    {
        unsigned int *tmp = buffer[j];
        printf("[%02x](%p) %s\n",j, tmp, strings[j]);

    }

    free(strings);
}

void signal_handler(int signo)
{
    printf("\n===================== catch singal %d ========\n", signo);
    printf("Dump stack start \n");
    dump();
    printf("Dump stack end.. .\n");

    signal(signo, SIG_DFL);
    raise(signo);//int pid = getpid(); kill(pid, sign0);
}