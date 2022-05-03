package main

import (
	"bufio"
	"os"
	"unicode"
)

func count_words(path string) int {

	file, err := os.Open(path)

	if err != nil {
		return -1
	}

	scanner := bufio.NewScanner(file)

	var text string

	for scanner.Scan() {
		text = text + scanner.Text() + " "
	}

	in_word := false
	count := 0

	for _, rune := range text {

		if unicode.IsLetter(rune) || unicode.IsDigit(rune) {
			if !in_word {
				in_word = true
				count++
			}
		} else {
			in_word = false
		}
	}
	return count
}

func main() {
	empty_words1 :=
		count_words("../files/empty.txt")
	empty_words2 :=
		count_words("../files/empty_with_space.txt")
	ten_words :=
		count_words("../files/10_words.txt")
	single_word :=
		count_words("../files/single_word_end.txt")

	if empty_words1 != 0 || empty_words2 != 0 ||
		ten_words != 10 || single_word != 1 {
		os.Exit(1)
	} else {
		os.Exit(0)
	}
}
