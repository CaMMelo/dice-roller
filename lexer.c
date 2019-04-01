#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

#define NEXT_STATE(state, chr) dfa[state][symbol_table[(chr)]]

extern int symbol_table[256];
extern int dfa_action[6];
extern int dfa[6][15];

char* lexeme = NULL;

enum _token_t
tokenize(char* stream)
{
    static char* ptr;
    
    if(stream)
    {
        ptr = stream;
        return NONE;
    }

    while(*ptr)
    {
        char* init = ptr;
        int current_state = 0;

        while(ptr && NEXT_STATE(current_state, *ptr))
        {
            current_state = NEXT_STATE(current_state, *ptr);
            ptr++;
        }

        int size = ptr - init;
        lexeme = malloc(size * sizeof(char));
        strncpy(lexeme, init, size);

        switch(dfa_action[current_state])
        {
            case 0:
                free(lexeme);
                ptr++;
                break;
            case 1:
                return NUMBER;
            case 2:
                return D_TOKEN;
            case 3:
                return SUM;
            case 4:
                return SUB;
        }
    }
}