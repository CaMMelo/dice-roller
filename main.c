#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "parser.h"

char* progname = NULL;

int
main(int argc, char** argv)
{
    srand(time(NULL));

    char *line, *s;

    progname = argv[0];

    int done = 0;

    do
    {
        line = readline("<20> ");

        if(!line)
            continue;

        add_history(s);
        int result = parse(line);
        printf("-- %d\n", result);
        free(line);

    } while(!done);
}