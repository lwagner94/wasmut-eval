
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int count_words(const char *path) {
    FILE* f = fopen(path, "r");
    if (f == NULL) {
        goto out;
    }

    if (fseek (f, 0, SEEK_END) != 0) {
        goto out;
    }
    long length = ftell (f);

    if (length == -1) {
        goto out;
    }

    if (fseek (f, 0, SEEK_SET) != 0) {
        goto out;
    }

    char* buffer = malloc (length);
    if (!buffer) {
        goto out;
    }
    if ( fread (buffer, 1, length, f) != length) {
        goto out;
    }

    int counted = 0;
    bool inword = false;

    for (int i = 0; i < length; i++) {
        char c = buffer[i];

        if (isalnum(c)) {
            if (!inword) {
                inword = true;
                counted++;
            }
        } else {
            inword = false;
        }
    }

    return counted;

out:
    fclose(f);
    free(buffer);
    return -1;
}

int main(int argc, char *argv[]) {
    int empty_words1 = count_words("files/empty.txt");
    int empty_words2 = count_words("files/empty_with_space.txt");
    int ten_words = count_words("files/10_words.txt");  
    int single_word = count_words("files/single_word_end.txt");      
    return empty_words1 != 0 || empty_words2 != 0 || 
        ten_words != 10 || single_word != 1;
}