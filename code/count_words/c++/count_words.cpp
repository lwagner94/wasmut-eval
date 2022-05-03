
#include <string>
#include <iostream>
#include <fstream>

// Count the words in the file "path" 
// and return the number of words.
int count_words(std::string path) {
    std::ifstream file(path);

    if (!file.good()) {
        return -1;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));

    bool inword = false;
    int counted = 0;

    for (auto &ch : content) {
        if (isalnum(ch)) {
            if (!inword) {
                inword = true;
                counted++;
            }
        } else {
            inword = false;
        }
    }

    return counted;
}

int main(int argc, char *argv[]) {
    int empty_words1 = 
        count_words("files/empty.txt");
    int empty_words2 = 
        count_words("files/empty_with_space.txt");
    int ten_words = 
        count_words("files/10_words.txt");  
    int single_word = 
        count_words("files/single_word_end.txt");      
    return empty_words1 != 0 || empty_words2 != 0 || 
        ten_words != 10 || single_word != 1;
}