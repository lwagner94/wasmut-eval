#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS (1)
#define FAILURE (0)


#define dbg(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)

enum TokenKind {
    TOKEN_STRING,
    TOKEN_IDENTIFIER,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_SEMICOL
};


struct Token {
    enum TokenKind kind;
    char *value;
};


struct SimpleConf {
  
};



int simpleconf_load(struct SimpleConf** sc, char *s);
int simpleconf_get(struct SimpleConf* sc, char *section, char* key, int* value);
int simpleconf_free(struct SimpleConf** sc);


int save_to_tokenlist(struct Token** tokenlist, int* len, int* capacity, struct Token token) {
    if (*len >= *capacity) {
        int new_capacity = *capacity * 2;
        *tokenlist = realloc(*tokenlist, sizeof(struct Token) * new_capacity);
        *capacity = new_capacity;
    }
    // printf("%d %d\n", *len, *capacity);
    
    (*tokenlist)[*len] = token;
    *len += 1;
    return SUCCESS;
}


void consume_whitespace(char **s) {
    while (**s == ' ' || **s == '\t') {
        (*s)++;
    }
}

int lex_identifier(char** s, struct Token** tokenlist, int* len, int* capacity) {
    char *identifier = *s;
    while (isalpha(**s)) {
        (*s)++;
    }

    int id_length = *s - identifier;

    struct Token token = {
        .kind = TOKEN_IDENTIFIER,
        .value = malloc(id_length + 1)
    };

    strncpy(token.value, identifier, id_length);

    dbg("<IDENTIFER(\"%s\")>\n", token.value);

    return save_to_tokenlist(tokenlist, len, capacity, token);
}

int lex_semicolon(char** s, struct Token** tokenlist, int* len, int* capacity) {
    struct Token token = {
        .kind = TOKEN_SEMICOL,
        .value = NULL
    };

    dbg("<SEMICOLON>\n");

    *s += 1;

    return save_to_tokenlist(tokenlist, len, capacity, token);
}

int lex_lbrace(char** s, struct Token** tokenlist, int* len, int* capacity) {
    struct Token token = {
        .kind = TOKEN_LBRACE,
        .value = NULL
    };

    dbg("<LBRACE>\n");

    *s += 1;

    return save_to_tokenlist(tokenlist, len, capacity, token);
}

int lex_rbrace(char** s, struct Token** tokenlist, int* len, int* capacity) {
    struct Token token = {
        .kind = TOKEN_RBRACE,
        .value = NULL
    };

    dbg("<RBRACE>\n");

    *s += 1;

    return save_to_tokenlist(tokenlist, len, capacity, token);
}

int tokenize(char* s, struct Token** tokens, int* token_len) {
    *token_len = 0;
    int token_capacity = 2;
    *tokens = malloc(sizeof(struct Token) * token_capacity);


    if (!*tokens) {
        return FAILURE;
    }


    if (s == NULL) {
        return FAILURE;
    }

    dbg("tokenize: %s\n", s);

    while (*s) {
        consume_whitespace(&s);

        if (*s == '\0') {
            break;
        }

        if (*s == '{') {
            lex_lbrace(&s, tokens, token_len, &token_capacity);
        
        } else if (*s == '}') {
            lex_rbrace(&s, tokens, token_len, &token_capacity);
        } else if (isalpha(*s)) {
            lex_identifier(&s, tokens, token_len, &token_capacity);
        } else if (*s == ';') {
            lex_semicolon(&s, tokens, token_len, &token_capacity);
        }
    }
}

int simpleconf_load(struct SimpleConf** sc, char *s) {

    *sc = malloc(sizeof(struct SimpleConf));
    if (*sc == NULL) {
        return FAILURE;
    }

    struct Token* tokens;
    int token_len;
    tokenize(s, &tokens, &token_len);



    return SUCCESS;
}


int simpleconf_free(struct SimpleConf** sc) {
    free(*sc);
    *sc = NULL;
    return SUCCESS;
}

int main() {
    struct SimpleConf* sc = NULL;

    simpleconf_load(&sc, "{}; asdf ");

    simpleconf_free(&sc);
    
    return 0;
}