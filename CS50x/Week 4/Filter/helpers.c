#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loops through the columns and then rows of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // sums up all the values of RGB color and then divides them by 3 to gen and average value, which round to be an integer
            int value = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // assigns the new values to the pixels of the image
            image[i][j].rgbtBlue = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtRed = value;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // loops through the columns and then rows of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // stores the original value of each pixel
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;

            // calculates the value for sepia filter with the original value
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

            // checks if no pixels are more than 255 or less than 0
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            else if (sepiaBlue < 0)
            {
                sepiaBlue = 0;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            else if (sepiaGreen < 0)
            {
                sepiaGreen = 0;
            }

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            else if (sepiaRed < 0)
            {
                sepiaRed = 0;
            }

            // assigns the newly calculated values to each pixel
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // sets up 3 temporary storages for pixels
    int temp[3];

    // loops through the columns and then rows of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // saves the pixel information of RGB to the temporary location
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;

            // while the riginal data is stored in temp, taking data from pixel width - j - 1 and stores them at j pixel place
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            // take sthe stored values from temp and assigns them to the pixel copied in previos step
            image[i][width - j - 1].rgbtBlue = temp[0];
            image[i][width - j - 1].rgbtGreen = temp[1];
            image[i][width - j - 1].rgbtRed = temp[2];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // loops through the image and copies every pixel to copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // loops through the columns and then rows of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // sets integers for each color + count to know how many times we need to divide
            int counter = 0;
            int blue = 0;
            int green = 0;
            int red = 0;

            // starts for loop three pixels, two around our chosen one (for columns)
            for (int k = -1; k < 2; k++)
            {
                // starts for loop three pixels, two around our chosen one (for rows)
                for (int l = -1; l < 2; l++)
                {
                    // checks if the pixels are inside the image
                    if ((i + k) >= 0 && (i + k) < height && (j + l) >= 0 && (j + l) < width)
                    {
                        // adds up the values of the pixels
                        counter++;
                        blue += copy[i + k][j + l].rgbtBlue;
                        green += copy[i + k][j + l].rgbtGreen;
                        red += copy[i + k][j + l].rgbtRed;
                    }
                }
            }

            // makes average by dividing the sums by the count of pixels and the rounds it to be integer and assigns to the original
            image[i][j].rgbtBlue = round((float) blue / counter);
            image[i][j].rgbtGreen = round((float) green / counter);
            image[i][j].rgbtRed = round((float) red / counter);
        }
    }
    return;
}
