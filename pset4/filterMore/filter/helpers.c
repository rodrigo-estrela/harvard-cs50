#include "helpers.h"
#include <stdbool.h>
#include <math.h>

//Constant
#define SIZE 3

// Kernels
int Gx[SIZE][SIZE] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int Gy[SIZE][SIZE] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

//prototypes
int sobel(RGBTRIPLE box[SIZE][SIZE], char channel);
int computeG(int kernel[SIZE][SIZE], RGBTRIPLE box[SIZE][SIZE], char channel);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int average = 0.0;
        for (int j = 0; j < width; j++)
        {
            average = round(((float)image[i][j].rgbtRed + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, mid = (width / 2); j < mid; j++)
        {
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp; 
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE originalImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalImage[i][j] = image[i][j];
        }
    }
    
    for (int i = 0; i < height; i++)
    {

        
        int lineStart = 0;
        int lineEnd = 0;
        lineStart = (i == 0) ? 0 : (i - 1);
        lineEnd = (i == (height - 1)) ? i : (i + 1);
        for (int j = 0; j < width; j++)
        {
            int columnStart = 0;
            int columnEnd = 0;
            columnStart = (j == 0) ? 0 : (j - 1);
            columnEnd = (j == (width - 1)) ? j : (j + 1);
            
            float totalRed = 0.0;
            float totalGreen = 0.0;
            float totalBlue = 0.0;
            for (int k = lineStart; k <= lineEnd; k++)
            {
                for (int l = columnStart; l <= columnEnd; l++)
                {
                    totalRed += originalImage[k][l].rgbtRed;
                    totalGreen += originalImage[k][l].rgbtGreen;
                    totalBlue += originalImage[k][l].rgbtBlue;
                }
            }
            int totalOfPixels = (columnEnd - columnStart + 1) * (lineEnd - lineStart + 1);
            image[i][j].rgbtRed = round(totalRed / totalOfPixels);
            image[i][j].rgbtGreen = round(totalGreen / totalOfPixels);
            image[i][j].rgbtBlue = round(totalBlue / totalOfPixels);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE originalImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalImage[i][j] = image[i][j];
        }
    }

    RGBTRIPLE blackPixel;
    blackPixel.rgbtRed = 0;
    blackPixel.rgbtGreen = 0;
    blackPixel.rgbtBlue = 0;
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE box[SIZE][SIZE];


        for (int j = 0; j < width; j++)
        {

            //first row
            box[0][0] = (i == 0) || (j == 0) ? blackPixel : originalImage[i - 1][j - 1];
            box[0][1] = (i == 0) ? blackPixel : originalImage[i - 1][j];
            box[0][2] = (i == 0) || (j == (width - 1)) ? blackPixel : originalImage[i - 1][j + 1];

            //Second row
            box[1][0] = (j == 0) ? blackPixel : originalImage[i][j - 1];
            box[1][1] = originalImage[i][j];
            box[1][2] = (j == (width - 1)) ? blackPixel : originalImage[i][j + 1];

            //Third row
            box[2][0] = (i == (height - 1)) || (j == 0) ? blackPixel : originalImage[i + 1][j - 1];
            box[2][1] = (i == (height - 1)) ? blackPixel : originalImage[i + 1][j];
            box[2][2] = (i == (height - 1)) || (j == (width - 1)) ? blackPixel : originalImage[i + 1][j + 1];

            int redChannel = 0;
            redChannel = sobel(box, 'r');
            image[i][j].rgbtRed = redChannel > 255 ? 255 : redChannel;

            int greenChannel = 0;
            greenChannel = sobel(box, 'g');
            image[i][j].rgbtGreen = greenChannel > 255 ? 255 : greenChannel;

            int blueChannel = 0;
            blueChannel = sobel(box, 'b');
            image[i][j].rgbtBlue = blueChannel > 255 ? 255 : blueChannel;
        }
    }

    return;
}

// Sopel operator
int sobel(RGBTRIPLE box[SIZE][SIZE], char channel)
{
    int x = computeG(Gx, box, channel);
    int y = computeG(Gy, box, channel);

    return round(sqrt(pow(x, 2) + pow(y, 2)));
}


// Compute G value
int computeG(int kernel[SIZE][SIZE], RGBTRIPLE box[SIZE][SIZE], char channel)
{
    int n = 0;
    switch (channel)
    {
        case 'r':
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    n += kernel[i][j] * box[i][j].rgbtRed;
                }
            }
            break;

        case 'g':
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    n += kernel[i][j] * box[i][j].rgbtGreen;
                }
            }
            break;

        case 'b':
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    n += kernel[i][j] * box[i][j].rgbtBlue;
                }
            }
            break;

        default:
            break;
    }

    return n;
}
