#ifndef __DFA_H__
#define __DFA_H__

enum _token_t {
    NONE, NUMBER, D_TOKEN, SUM, SUB
};

extern char* lexeme;

enum _token_t
tokenize(char*);

#endif // __DFA_H__