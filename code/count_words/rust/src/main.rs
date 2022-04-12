
fn count_words(path: &str) -> Result<i32, std::io::Error> {
    
    let content = std::fs::read_to_string(path)?;

    let mut inword = false;
    let mut count = 0;
    
    for c in content.chars() {
        if c.is_alphanumeric() {
            if !inword {
                inword = true;
                count += 1;
            }
        } else {
            inword = false;
        }
    }
    
    Ok(count)
}

fn main() {
    
    
    let empty_words1 = count_words("files/empty.txt").unwrap();
    let empty_words2 = count_words("files/empty_with_space.txt").unwrap();
    let ten_words = count_words("files/10_words.txt").unwrap();  
    let single_word = count_words("files/single_word_end.txt").unwrap();      
    if empty_words1 != 0 || empty_words2 != 0 || ten_words != 10 || single_word != 1 {
        std::process::exit(1);
    }
}
