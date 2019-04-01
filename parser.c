#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"

enum _token_t current_token;

void
consume_token(enum _token_t tok)
{
    if(tok == current_token)
        current_token = tokenize(NULL);
    else
        printf("DEU RUIM MALANDRO!\n");
}

int
roll(int times, int nfaces)
{
    int result = 0;
    for(int i=0; i<times; i++)
        result += random() % nfaces + 1;
    return result;
}

int
rdice()
{
    if(current_token == D_TOKEN)
    {
        consume_token(D_TOKEN);
        int nfaces = atoi(lexeme);
        consume_token(NUMBER);
        return nfaces;
    }

    return 0;
}

int
dice()
{
    if(current_token == NUMBER)
    {
        int times = atoi(lexeme);
        consume_token(NUMBER);
        int nfaces = rdice();
        return nfaces > 0 ? roll(times, nfaces) : times;
    }
    else
    {
        consume_token(D_TOKEN);
        int nfaces = atoi(lexeme);
        consume_token(NUMBER);
        return roll(1, nfaces);
    }
}

int
rexp(int val)
{
    if(current_token == SUM)
    {
        consume_token(SUM);
        int a = dice();
        int b = rexp(a);

        return val + b;
    }
    else if(current_token == SUB)
    {
        consume_token(SUB);
        int a = dice();
        int b = rexp(a);

        return val - b;
    }

    return val;
}

int
_exp()
{
    int a = dice();
    return rexp(a);
}

int
parse(char* stream)
{
    tokenize(stream);
    current_token = tokenize(NULL);
    return _exp();
}