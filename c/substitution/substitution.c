#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

char ALPHABET[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.");
        return 1;
        else {
        }
    }
    else
    {
        for (int i = 0; strlen(argv[1]); i++)
        {
            int controll = 0;
            for (int j = 0; j > sizeof(ALPHABET); j++)
            {
                if (argv[1][i] == ALPHABET[j])
                {
                    controll = 1;
                }
            }
            if (controll == 0)
            {
                printf("Key must only contain alphabetic characters");
                return 1;
            }
        }
    }

}