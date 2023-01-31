#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int blue = image[h][w].rgbtBlue;
            int green = image[h][w].rgbtGreen;
            int red = image[h][w].rgbtRed;

            int average_value = round((blue + green + red) / 3.0);

            image[h][w].rgbtBlue = average_value;
            image[h][w].rgbtGreen = average_value;
            image[h][w].rgbtRed = average_value;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int sepiaRed = round(.393 * image[y][x].rgbtRed
                               + .769 * image[y][x].rgbtGreen
                               + .189 * image[y][x].rgbtBlue);

            int sepiaGreen = round(.349 * image[y][x].rgbtRed
                                 + .686 * image[y][x].rgbtGreen
                                 + .168 * image[y][x].rgbtBlue);

            int sepiaBlue = round(.272 * image[y][x].rgbtRed
                                + .534 * image[y][x].rgbtGreen
                                + .131 * image[y][x].rgbtBlue);

            if (sepiaRed > 255)
            {sepiaRed = 255;}
            if (sepiaGreen > 255)
            {sepiaGreen = 255;}
            if (sepiaBlue > 255)
            {sepiaBlue = 255;}

            image[y][x].rgbtRed = sepiaRed;
            image[y][x].rgbtGreen = sepiaGreen;
            image[y][x].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        int swaps = width / 2;

        for (int w = 0; w < swaps; w++)
        {
            int blue = image[h][w].rgbtBlue;
            int green = image[h][w].rgbtGreen;
            int red = image[h][w].rgbtRed;

            image[h][w].rgbtBlue = image[h][width - (w + 1)].rgbtBlue;
            image[h][w].rgbtGreen = image[h][width - (w + 1)].rgbtGreen;
            image[h][w].rgbtRed = image[h][width - (w + 1)].rgbtRed;

            image[h][width - (w + 1)].rgbtBlue = blue;
            image[h][width - (w + 1)].rgbtGreen = green;
            image[h][width - (w + 1)].rgbtRed = red;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copia em branco para inserir valores sem afetar o original.
    RGBTRIPLE image_tmp[height][width];

    for (int l = 0; l < height; l++)
    {
        for (int c = 0; c < width; c++)
        {
            image_tmp[l][c].rgbtBlue = 0;
            image_tmp[l][c].rgbtGreen = 0;
            image_tmp[l][c].rgbtRed = 0;
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //    QUADRANTS
            //  | A | B | C |
            //  | D | E | F |
            //  | G | H | I |

            int blue_sum = 0;
            int green_sum = 0;
            int red_sum = 0;

            int avg_blue;
            int avg_green;
            int avg_red;

            // 4 pieces - Bottom and Top.
            if ((y == 0 || y == height - 1) && (x == 0 || x == width - 1))
            {
                if (y == height - 1) // Bottom
                {
                    for (int l = - 1; l < 1; l++)
                    {
                        if (x == width - 1) // I
                        {
                            for (int c = - 1; c < 1; c++)
                            {
                                blue_sum += image[y + l][x + c].rgbtBlue;
                                green_sum += image[y + l][x + c].rgbtGreen;
                                red_sum += image[y + l][x + c].rgbtRed;
                            }
                        }
                        else // G
                        {
                            for (int c = 0; c < 2; c++)
                            {
                                blue_sum += image[y + l][x + c].rgbtBlue;
                                green_sum += image[y + l][x + c].rgbtGreen;
                                red_sum += image[y + l][x + c].rgbtRed;
                            }
                        }
                    }
                }
                else // Top
                {
                    for (int l = 0; l < 2; l++)
                    {
                        if (x == width - 1) // C
                        {
                            for (int c = - 1; c < 1; c++)
                            {
                                blue_sum += image[y + l][x + c].rgbtBlue;
                                green_sum += image[y + l][x + c].rgbtGreen;
                                red_sum += image[y + l][x + c].rgbtRed;
                            }
                        }
                        else // A
                        {
                            for (int c = 0; c < 2; c++)
                            {
                                blue_sum += image[y + l][x + c].rgbtBlue;
                                green_sum += image[y + l][x + c].rgbtGreen;
                                red_sum += image[y + l][x + c].rgbtRed;
                            }
                        }
                    }
                }

                avg_blue = round(blue_sum / 4.0);
                avg_green = round(green_sum / 4.0);
                avg_red = round(red_sum / 4.0);

                image_tmp[y][x].rgbtBlue = avg_blue;
                image_tmp[y][x].rgbtGreen = avg_green;
                image_tmp[y][x].rgbtRed = avg_red;

            }
            // Six pieces - Bottom and Top.
            else if ((y == 0 || y == height - 1) && (x >= 1 || x <= width - 2))
            {
                if (y == height - 1) // H
                {
                    for (int l = - 1; l < 1; l++)
                    {
                        for (int c = - 1; c < 2; c++)
                        {
                            blue_sum += image[y + l][x + c].rgbtBlue;
                            green_sum += image[y + l][x + c].rgbtGreen;
                            red_sum += image[y + l][x + c].rgbtRed;
                        }
                    }
                }
                else // B
                {
                    for (int l = 0; l < 2; l++)
                    {
                        for (int c = - 1; c < 2; c++)
                        {
                            blue_sum += image[y + l][x + c].rgbtBlue;
                            green_sum += image[y + l][x + c].rgbtGreen;
                            red_sum += image[y + l][x + c].rgbtRed;
                        }
                    }
                }

                avg_blue = round(blue_sum / 6.0);
                avg_green = round(green_sum / 6.0);
                avg_red = round(red_sum / 6.0);

                image_tmp[y][x].rgbtBlue = avg_blue;
                image_tmp[y][x].rgbtGreen = avg_green;
                image_tmp[y][x].rgbtRed = avg_red;

            }
            // Six pieces - Right and Left.
            else if ((y >= 1 || y <= height - 2) && (x == 0 || x == width - 1))
            {
                if (x == width - 1) // F
                {
                    for (int l = - 1; l < 2; l++)
                    {
                        for (int c = - 1; c < 1; c++)
                        {
                            blue_sum += image[y + l][x + c].rgbtBlue;
                            green_sum += image[y + l][x + c].rgbtGreen;
                            red_sum += image[y + l][x + c].rgbtRed;
                        }
                    }
                }
                else // D
                {
                    for (int l = - 1; l < 2; l++)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            blue_sum += image[y + l][x + c].rgbtBlue;
                            green_sum += image[y + l][x + c].rgbtGreen;
                            red_sum += image[y + l][x + c].rgbtRed;
                        }
                    }
                }

                avg_blue = round(blue_sum / 6.0);
                avg_green = round(green_sum / 6.0);
                avg_red = round(red_sum / 6.0);

                image_tmp[y][x].rgbtBlue = avg_blue;
                image_tmp[y][x].rgbtGreen = avg_green;
                image_tmp[y][x].rgbtRed = avg_red;

            }
            // Nine pieces - All
            else
            {
                for (int l = - 1; l < 2; l++)
                {
                    for (int c = - 1; c < 2; c++)
                    {
                        blue_sum += image[y + l][x + c].rgbtBlue;
                        green_sum += image[y + l][x + c].rgbtGreen;
                        red_sum += image[y + l][x + c].rgbtRed;
                    }
                }

                avg_blue = round(blue_sum / 9.0);
                avg_green = round(green_sum / 9.0);
                avg_red = round(red_sum / 9.0);

                image_tmp[y][x].rgbtBlue = avg_blue;
                image_tmp[y][x].rgbtGreen = avg_green;
                image_tmp[y][x].rgbtRed = avg_red;
            }
        }
    }

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtBlue = image_tmp[a][b].rgbtBlue;
            image[a][b].rgbtGreen = image_tmp[a][b].rgbtGreen;
            image[a][b].rgbtRed = image_tmp[a][b].rgbtRed;
        }
    }
}
