#include "mona.h"

void pipe_catcher(int signo)
{
    if(signo == SIGPIPE)
    {
	printf("Broken pipe, no worries\n");
    }
}
