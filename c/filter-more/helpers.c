#include "helpers.h"
#include <math.h>
#include <stdlib.h>

float check_final(float toCheck);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j ++)
        {
            float avr = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0;
            image[i][j].rgbtBlue = round(avr);
            image[i][j].rgbtRed = round(avr);
            image[i][j].rgbtGreen = round(avr);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        // only iterate over half the list, we can get the other half by using width - j - 1
        for(int j = 0; j < (width / 2); j ++)
        {
            // store tmp values
            uint8_t tmpRed = image[i][j].rgbtRed;
            uint8_t tmpGreen = image[i][j].rgbtGreen;
            uint8_t tmpBlue = image[i][j].rgbtBlue;

            // switch right to left
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            // switch tmp to right
            image[i][width - j - 1].rgbtRed = tmpRed;
            image[i][width - j - 1].rgbtGreen = tmpGreen;
            image[i][width - j - 1].rgbtBlue = tmpBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate over every pixel
    RGBTRIPLE(*tmp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j ++)
        {
            int32_t avgRed = 0;
            int32_t avgGreen = 0;
            int32_t avgBlue = 0;
            float divisor = 0.0;
            for(int a = (i - 1); a <= (i + 1); a++)
            {
                // only if the row is in the array
                if(!(a < 0 || a > height - 1))
                {
                    for(int b = (j - 1); b <= (j + 1); b++)
                    {
                        // only add if b is inside the array
                        if(!(b < 0 || b > width - 1))
                        {
                            // add values to avg
                            avgRed += image[a][b].rgbtRed;
                            avgGreen += image[a][b].rgbtGreen;
                            avgBlue += image[a][b].rgbtBlue;
                            divisor++;
                        }
                    }
                }
            }
            // don't apply values if we havent calculated them
            if(divisor != 0)
            {
                tmp[i][j].rgbtRed = round(avgRed / divisor);
                tmp[i][j].rgbtGreen = round(avgGreen / divisor);
                tmp[i][j].rgbtBlue = round(avgBlue / divisor);
            }
        }
    }
    // copy tmp into image
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j ++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }
    return;
}