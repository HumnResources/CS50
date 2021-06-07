#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int check_bounds(int row, int col, int height, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Placeholder values to calculate avg, could inline but this is more readable
    int b, g, r, avg;

    // Iterate over the image's pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Store the values of each color channel for average.
            b = image[i][j].rgbtBlue;
            g = image[i][j].rgbtGreen;
            r = image[i][j].rgbtRed;

            avg = round((b+g+r) / 3.0f);

            // Sets all the values to the same, this creates a grey color
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;

    // Iterate over each row of pixels, they remain in the same order
    for (int i = 0; i < height; i++)
    {
        // Iterate over each pixel, only going through half the row is needed
        for (int j = 0; j < width; j++)
        {
            if (j == width / 2)
            {
                break;
            }

            // Get opposite pixel number
            // Subtract 1 because it's zero indexed
            // The width value is accounting for a zero
            int n = (width - 1) - j;

            // Store the color values to tmp variable
            tmp = image[i][j];

            // Update the current pixel too that of it's opposite
            image[i][j] = image[i][n];

            // Update opposite pixel to "current" pixel
            image[i][n] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // BOX BLUR
    // avg color value of all 9 pixels forming a grid around said pixel

    // We set a group of offsets, each representing
    // the index of the location in the matrix relative to
    // a center tile. 8 neighbors
    #define MAX_NEIGHBOR 8
    int offsetsX[MAX_NEIGHBOR] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int offsetsY[MAX_NEIGHBOR] = {1, 1, 1, 0, 0, -1, -1, -1};

    // Initialize one pointer for reuse for convenience
    RGBTRIPLE *pxl = NULL;

    // Create buffer to write copy because we need the original color values
    RGBTRIPLE buffer[height][width];

    float sumBlue, sumGreen, sumRed;

    // Set to 1 to include itself
    int nAdjacent = 1;

    // Iterate over the image's pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset meta data for each pixel
            sumBlue = 0.0f;
            sumGreen = 0.0f;
            sumRed = 0.0f;
            nAdjacent = 1;

            // Update pointer to direct to currently selected neighbour
            pxl = &image[i][j];

            // Add neighbour color value to sum
            sumBlue += pxl->rgbtBlue;
            sumGreen += pxl->rgbtGreen;
            sumRed += pxl->rgbtRed;

            // Check the current index neigbours
            for (int k = 0; k < MAX_NEIGHBOR; k++)
            {
                // Bounds checking
                // We add the current offset to each pair of indicies
                // To get relative neighbours.
                if (check_bounds(i + offsetsX[k], j + offsetsY[k], height, width) != 0)
                {
                    continue;
                }

                // Update pointer to direct to currently selected neighbour
                pxl = &image[i + offsetsX[k]][j + offsetsY[k]];

                // Add neighbour color value to sum
                sumBlue += pxl->rgbtBlue;
                sumGreen += pxl->rgbtGreen;
                sumRed += pxl->rgbtRed;

                nAdjacent++;
            }

            // adds the current values to the total and calculates average
            buffer[i][j].rgbtBlue = round(sumBlue / nAdjacent);
            buffer[i][j].rgbtGreen = round(sumGreen / nAdjacent);
            buffer[i][j].rgbtRed = round(sumRed / nAdjacent);
        }
    }

    // replace the image with our new, blurred one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer[i][j];
        }
    }

    return;
}

// @return : 1 indicatees false
int check_bounds(int row, int col, int height, int width)
{
    // Very simple check to see if the numbers are within
    // array indexing bounds.
    if ((row < 0 || row >= height) || (col < 0 || col >= width))
        return 1;

    return 0;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int offsetsX[MAX_NEIGHBOR] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int offsetsY[MAX_NEIGHBOR] = {1, 1, 1, 0, 0, -1, -1, -1};

    // Kernels for weighing the color delta
    // Omit 0 to keep index the same as neighbours
    int Gx[MAX_NEIGHBOR] = {-1, 0, 1, -2, 2, -1, 0, 1};
    int Gy[MAX_NEIGHBOR] = {-1, -2, -1, 0, 0, 1, 2, 1};

    // Create buffer to write copy because we need the original color values
    RGBTRIPLE buffer[height][width];

    // Initialize one pointer for reuse for convenience
    RGBTRIPLE *pxl = NULL;

    // Sets variables to store the calculations from
    // the scoring of the surrounding pixels
    float sumBlueGX = 0.0f;
    float sumBlueGY = 0.0f;
    float sumGreenGX = 0.0f;
    float sumGreenGY = 0.0f;
    float sumRedGX = 0.0f;
    float sumRedGY = 0.0f;
    float sum = 0;

    // Iterate over the image's pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check the current index neigbours - Inclusive of itself
            for (BYTE k = 0; k < MAX_NEIGHBOR; k++)
            {
                int tmpRow = i + offsetsX[k];
                int tmpCol = j + offsetsY[k];

                // Bounds checking
                // We add the current offset to each pair of indicies
                // To get relative neighbours.
                if (check_bounds(tmpRow, tmpCol, height, width) != 0)
                {
                    continue;
                }

                // Update pointer to direct to currently selected neighbour
                pxl = &image[tmpRow][tmpCol];

                // Perform calculations based off the provided kernels that weigh or score the pixels
                sumBlueGX += (Gx[k] * pxl->rgbtBlue);
                sumBlueGY += (Gy[k] * pxl->rgbtBlue);

                sumGreenGX += (Gx[k] * pxl->rgbtGreen);
                sumGreenGY += (Gy[k] * pxl->rgbtGreen);

                sumRedGX += (Gx[k] * pxl->rgbtRed);
                sumRedGY += (Gy[k] * pxl->rgbtRed);
            }

            // Squaring ensures a positive number
            // Sobel operation formula : sqrt(GX^2) + sqrt(GY^2)
            // Absolute w/ checks also works well here
            // Ternary conditional to double check if its valid range

            // Get red sobel value
            // sum = round(fabs(sumBlueGX) + fabs(sumBlueGY));
            sum = sqrt(pow(sumBlueGX, 2) + pow(sumBlueGY, 2));
            sum = (sum > 255) ? 255 : sum;
            // sum = (sum < 0) ? 0 : sum;
            buffer[i][j].rgbtBlue = round(sum);

            // Get green sobel value
            // sum = round(fabs(sumGreenGX) + fabs(sumGreenGY));
            sum = sqrt(pow(sumGreenGX, 2) + pow(sumGreenGY, 2));
            sum = (sum > 255) ? 255 : sum;
            // sum = (sum < 0) ? 0 : sum;
            buffer[i][j].rgbtGreen = round(sum);


            // Get red sobel value
            // sum = round(fabs(sumRedGX) + fabs(sumRedGY));
            sum = sqrt(pow(sumRedGX, 2) + pow(sumRedGY, 2));
            sum = (sum > 255) ? 255 : sum;
            // sum = (sum < 0) ? 0 : sum;
            buffer[i][j].rgbtRed = round(sum);

            // Reset the values as this pixel has been set.
            sumBlueGX = 0.0f;
            sumBlueGY = 0.0f;
            sumGreenGX = 0.0f;
            sumGreenGY = 0.0f;
            sumRedGX = 0.0f;
            sumRedGY = 0.0f;
        }
    }

    // replace the image with our new, outlined one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer[i][j];
        }
    }
}



