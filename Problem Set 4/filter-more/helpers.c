#include "helpers.h"
#include <math.h>
#include <cs50.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            int average_rgb = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average_rgb;
            image[i][j].rgbtGreen = average_rgb;
            image[i][j].rgbtBlue = average_rgb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width / 2; j++){
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
bool is_exceeding_bounds(int x, int y, int height, int width)
{
    if (x > height - 1){
        return true;
    }
    if (y > width - 1){
        return true;
    }
    if (x < 0){
        return true;
    }
    if (y < 0){
        return true;
    }
    return false;
}
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            copy[i][j] = image[i][j];
        }
    }
    // Get the pixel of an image
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            // We will need values around image[i][j] including i + or - 1 and j + or - 1
            int average_red = 0;
            int average_green = 0;
            int average_blue = 0;
            float count = 0.0;
            // Adding up all rgb values within the bounds
            average_red += copy[i][j].rgbtRed;
            average_green += copy[i][j].rgbtGreen;
            average_blue += copy[i][j].rgbtBlue;
            count++;
            if (!is_exceeding_bounds(i + 1, j + 1, height, width)){
                average_red += copy[i + 1][j + 1].rgbtRed;
                average_green += copy[i + 1][j + 1].rgbtGreen;
                average_blue += copy[i + 1][j + 1].rgbtBlue;
                count++;
            }
            if (!is_exceeding_bounds(i + 1, j, height, width)){
                average_red += copy[i + 1][j].rgbtRed;
                average_green += copy[i + 1][j].rgbtGreen;
                average_blue += copy[i + 1][j].rgbtBlue;
                count++;
            }
            if (!is_exceeding_bounds(i + 1, j - 1, height, width)){
                average_red += copy[i + 1][j - 1].rgbtRed;
                average_green += copy[i + 1][j - 1].rgbtGreen;
                average_blue += copy[i + 1][j - 1].rgbtBlue;
                count++;
            }
            if (!is_exceeding_bounds(i, j + 1, height, width)){
                average_red += copy[i][j + 1].rgbtRed;
                average_green += copy[i][j + 1].rgbtGreen;
                average_blue += copy[i][j + 1].rgbtBlue;
                count++;
            }
            if (!is_exceeding_bounds(i, j - 1, height, width)){
                average_red += copy[i][j - 1].rgbtRed;
                average_green += copy[i][j - 1].rgbtGreen;
                average_blue += copy[i][j - 1].rgbtBlue;
                count++;
            }
            if (!is_exceeding_bounds(i - 1, j + 1, height, width)){
                average_red += copy[i - 1][j + 1].rgbtRed;
                average_green += copy[i - 1][j + 1].rgbtGreen;
                average_blue += copy[i - 1][j + 1].rgbtBlue;
                count++;
            }
            if (!is_exceeding_bounds(i - 1, j, height, width)){
                average_red += copy[i - 1][j].rgbtRed;
                average_green += copy[i - 1][j].rgbtGreen;
                average_blue += copy[i - 1][j].rgbtBlue;
                count++;
            }
            if (!is_exceeding_bounds(i - 1, j - 1, height, width)){
                average_red += copy[i - 1][j - 1].rgbtRed;
                average_green += copy[i - 1][j - 1].rgbtGreen;
                average_blue += copy[i - 1][j - 1].rgbtBlue;
                count++;
            }
            image[i][j].rgbtRed = round(average_red / count);
            image[i][j].rgbtGreen = round(average_green / count);
            image[i][j].rgbtBlue = round(average_blue / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            copy[i][j] = image[i][j];
        }
    }
    // Now we can start with edge
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            // if the outer pixels are exceeding the bounds, the rgb values are considered 0.
            // Get Gx first where [i][j-1] is multiplied by -2 and the other j - 1 multiplied by - 1.
            // Get both Gx and Gy at the same time
            int Gx_red = 0;
            int Gy_red = 0;
            int Gx_green = 0;
            int Gy_green = 0;
            int Gx_blue = 0;
            int Gy_blue = 0;
            // Top left
            if (!is_exceeding_bounds(i - 1, j - 1, height, width)){
                Gx_red += copy[i - 1][j - 1].rgbtRed * -1;
                Gy_red += copy[i - 1][j - 1].rgbtRed * -1;
                Gx_green += copy[i - 1][j - 1].rgbtGreen * -1;
                Gy_green += copy[i - 1][j - 1].rgbtGreen * -1;
                Gx_blue += copy[i - 1][j - 1].rgbtBlue * -1;
                Gy_blue += copy[i - 1][j - 1].rgbtBlue * -1;
            }
            // Top middle
            if (!is_exceeding_bounds(i - 1, j, height, width)){
                Gx_red += copy[i - 1][j].rgbtRed * 0;
                Gy_red += copy[i - 1][j].rgbtRed * -2;
                Gx_green += copy[i - 1][j].rgbtGreen * 0;
                Gy_green += copy[i - 1][j].rgbtGreen * -2;
                Gx_blue += copy[i - 1][j].rgbtBlue * 0;
                Gy_blue += copy[i - 1][j].rgbtBlue * -2;
            }
            // Top right
            if (!is_exceeding_bounds(i - 1, j + 1, height, width)){
                Gx_red += copy[i - 1][j + 1].rgbtRed * 1;
                Gy_red += copy[i - 1][j + 1].rgbtRed * -1;
                Gx_green += copy[i - 1][j + 1].rgbtGreen * 1;
                Gy_green += copy[i - 1][j + 1].rgbtGreen * -1;
                Gx_blue += copy[i - 1][j + 1].rgbtBlue * 1;
                Gy_blue += copy[i - 1][j + 1].rgbtBlue * -1;
            }
            // Middle left
            if (!is_exceeding_bounds(i, j - 1, height, width)){
                Gx_red += copy[i][j - 1].rgbtRed * -2;
                Gy_red += copy[i][j - 1].rgbtRed * 0;
                Gx_green += copy[i][j - 1].rgbtGreen * -2;
                Gy_green += copy[i][j - 1].rgbtGreen * 0;
                Gx_blue += copy[i][j - 1].rgbtBlue * -2;
                Gy_blue += copy[i][j - 1].rgbtBlue * 0;
            }
            // Middle
            if (!is_exceeding_bounds(i, j, height, width)){
                Gx_red += copy[i][j].rgbtRed * 0;
                Gy_red += copy[i][j].rgbtRed * 0;
                Gx_green += copy[i][j].rgbtGreen * 0;
                Gy_green += copy[i][j].rgbtGreen * 0;
                Gx_blue += copy[i][j].rgbtBlue * 0;
                Gy_blue += copy[i][j].rgbtBlue * 0;
            }
            // Middle right
            if (!is_exceeding_bounds(i, j + 1, height, width)){
                Gx_red += copy[i][j + 1].rgbtRed * 2;
                Gy_red += copy[i][j + 1].rgbtRed * 0;
                Gx_green += copy[i][j + 1].rgbtGreen * 2;
                Gy_green += copy[i][j + 1].rgbtGreen * 0;
                Gx_blue += copy[i][j + 1].rgbtBlue * 2;
                Gy_blue += copy[i][j + 1].rgbtBlue * 0;
            }
            // Bottom left
            if (!is_exceeding_bounds(i + 1, j - 1, height, width)){
                Gx_red += copy[i + 1][j - 1].rgbtRed * -1;
                Gy_red += copy[i + 1][j - 1].rgbtRed * 1;
                Gx_green += copy[i + 1][j - 1].rgbtGreen * -1;
                Gy_green += copy[i + 1][j - 1].rgbtGreen * 1;
                Gx_blue += copy[i + 1][j - 1].rgbtBlue * -1;
                Gy_blue += copy[i + 1][j - 1].rgbtBlue * 1;
            }
            // Bottom middle
            if (!is_exceeding_bounds(i + 1, j, height, width)){
                Gx_red += copy[i + 1][j].rgbtRed * 0;
                Gy_red += copy[i + 1][j].rgbtRed * 2;
                Gx_green += copy[i + 1][j].rgbtGreen * 0;
                Gy_green += copy[i + 1][j].rgbtGreen * 2;
                Gx_blue += copy[i + 1][j].rgbtBlue * 0;
                Gy_blue += copy[i + 1][j].rgbtBlue * 2;
            }
            // Bottom right
            if (!is_exceeding_bounds(i + 1, j + 1, height, width)){
                Gx_red += copy[i + 1][j + 1].rgbtRed * 1;
                Gy_red += copy[i + 1][j + 1].rgbtRed * 1;
                Gx_green += copy[i + 1][j + 1].rgbtGreen * 1;
                Gy_green += copy[i + 1][j + 1].rgbtGreen * 1;
                Gx_blue += copy[i + 1][j + 1].rgbtBlue * 1;
                Gy_blue += copy[i + 1][j + 1].rgbtBlue * 1;
            }
            int G_red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int G_green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int G_blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));
            if (G_red > 255){
                G_red = 255;
            }
            if (G_green > 255){
                G_green = 255;
            }
            if (G_blue > 255){
                G_blue = 255;
            }
            image[i][j].rgbtRed = G_red;
            image[i][j].rgbtGreen = G_green;
            image[i][j].rgbtBlue = G_blue;
        }
    }
    return;
}
