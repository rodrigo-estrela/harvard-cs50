#include "helpers.h"
#include <math.h>

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        float sepiaRed, originalRed;
        float sepiaGreen, originalGreen;
        float sepiaBlue, originalBlue;
        for (int j = 0; j < width; j++)
        {
            //Original values
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;
            
            sepiaRed = 0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue;
            image[i][j].rgbtRed  = (sepiaRed < 255.0) ? round(sepiaRed) : 255;
            
            sepiaGreen = 0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue;
            image[i][j].rgbtGreen = (sepiaGreen < 255.0) ? round(sepiaGreen) : 255;
            
            sepiaBlue = 0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue;
            image[i][j].rgbtBlue = (sepiaBlue < 255.0) ? round(sepiaBlue) : 255;
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
