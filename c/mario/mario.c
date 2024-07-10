#include <cs50.h>
#include <stdio.h>

// prints an given amount of spaces
void PrintGaps(int gap)
{
    for (int i = 0; i < gap; i++)
    {
        printf(" ");
    }
}

// prints an given amount of bicks twice, seperated by 2 spaces
void PrintBricks(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    PrintGaps(2);

    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        PrintGaps(height - i - 1);
        PrintBricks(i + 1);
    }
}