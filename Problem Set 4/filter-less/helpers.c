#include "helpers.h"
#include <math.h>
#include <cs50.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Get the pixel of an image
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            // Getting a hold of the rgb of RGBTRIPLE image[i][j]
            // Finding the average rgb value
            int average_rgb = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average_rgb;
            image[i][j].rgbtGreen = average_rgb;
            image[i][j].rgbtBlue = average_rgb;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Get the pixel of an image
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            // Change original colors to sepia
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255){
                sepiaRed = 255;
            }
            if (sepiaGreen > 255){
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255){
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image;
    // Get the pixel of an image
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width / 2; j++){
            // Swap beginning of row with end of row
            temp_image = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp_image;
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
