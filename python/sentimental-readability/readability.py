from cs50 import get_string

def main():
    text = get_string("Text: ")

    l = letter_count(text) / word_count(text) * 100
    s = sentence_count(text) / word_count(text) * 100
    index = round(0.0588 * l - 0.296 * s - 15.8)
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade: {index}")

def letter_count(text):
    result = 0
    for l in text:
        if l.isalpha() == True:
            result += 1
    return result

def word_count(text):
    result = 1
    for l in text:
        if l == " ":
            result += 1
    return result

def sentence_count(text):
    result = 0
    punctuation = ['?','.','!']
    for l in text:
        if l in punctuation:
            result += 1
    return result

if __name__ == "__main__":
    main()