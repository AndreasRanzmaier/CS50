#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Coleman-Liau index
// avrerage letters and sentences per 100 words
int avr_letters(string text);
int avr_sentences(string text);

int get_letter_count(string text);
int get_word_count(string text);
int get_sentence_count(string text);

char ALPHABET[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char PUNCTUATION[] = {'.', '!', '?'};
int main(void)
{
    string text = get_string("Text: ");

    float L = (float)get_letter_count(text) / (float)get_word_count(text) * 100.0f;
    float S = (float)get_sentence_count(text) / (float)get_word_count(text) * 100.0f;
    int Index = round(0.0588 * L - 0.296 * S - 15.8);
    if (Index < 1)
    {
        printf("Before Grade 1\n");

    }
    else if (Index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", Index);
    }
}

int get_letter_count(string text)
{
    // only a-z and A-Z is a letter no !@_
    int result = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        for (int j = 0; j < sizeof(ALPHABET); j++)
        {
            if (tolower(text[i]) == ALPHABET[j])
            {
                result++;
            }
        }
    }
    return result;
}

int get_sentence_count(string text)
{
    int result = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        for (int j = 0; j < sizeof(PUNCTUATION); j++)
        {
            if (text[i] == PUNCTUATION[j])
            {
                result++;
            }
        }
    }

    return result;
}

int get_word_count(string text)
{
    int result = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            result++;
        }
    }
    return result;
}