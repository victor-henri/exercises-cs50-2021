#include "helpers.h"
#include <math.h>

// Converte a imagem para escala de cinza.
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

// Reflete a imagem horizontalmente.
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

// Embaça a imagem.
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
            //    Quadrantes
            //  | A | B | C |
            //  | D | E | F |
            //  | G | H | I |

            int blue_sum = 0;
            int green_sum = 0;
            int red_sum = 0;

            int avg_blue;
            int avg_green;
            int avg_red;

            // 4 partes - Superior e Inferior.
            if ((y == 0 || y == height - 1) && (x == 0 || x == width - 1))
            {
                if (y == height - 1) // Inferior.
                {
                    for (int l = - 1; l < 1; l++)
                    {
                        if (x == width - 1) // Quadrante I.
                        {
                            for (int c = - 1; c < 1; c++)
                            {
                                blue_sum += image[y + l][x + c].rgbtBlue;
                                green_sum += image[y + l][x + c].rgbtGreen;
                                red_sum += image[y + l][x + c].rgbtRed;
                            }
                        }
                        else // Quadrante G.
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
                else // Superior
                {
                    for (int l = 0; l < 2; l++)
                    {
                        if (x == width - 1) // Quadrante C
                        {
                            for (int c = - 1; c < 1; c++)
                            {
                                blue_sum += image[y + l][x + c].rgbtBlue;
                                green_sum += image[y + l][x + c].rgbtGreen;
                                red_sum += image[y + l][x + c].rgbtRed;
                            }
                        }
                        else // Quadrante A
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
            // 6 partes - Superior e Inferior
            else if ((y == 0 || y == height - 1) && (x >= 1 || x <= width - 2))
            {
                if (y == height - 1) // Quadrante H
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
                else // Quadrante B
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
            // 6 Partes - Direita e Esquerda.
            else if ((y >= 1 || y <= height - 2) && (x == 0 || x == width - 1))
            {
                if (x == width - 1) // Quadrante F
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
                else // Quadrante D
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
            // 9 partes - Todos
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

// Detecta bordas
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int gx_blue, gx_green, gx_red;
    int gy_blue, gy_green, gy_red;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            gx_blue = 0; gx_green = 0; gx_red = 0;
            gy_blue = 0; gy_green = 0; gy_red = 0;

            for (int l = - 1; l < 2; l++)
            {
                for (int c = - 1; c < 2; c++)
                {
                    if (y + l < 0 || y + l > height - 1)
                    {
                        continue;
                    }

                    if (x + c < 0 || x + c > width - 1)
                    {
                        continue;
                    }

                    gx_blue += image[y + l][x + c].rgbtBlue * gx[l + 1][c + 1];
                    gx_green += image[y + l][x + c].rgbtGreen * gx[l + 1][c + 1];
                    gx_red += image[y + l][x + c].rgbtRed * gx[l + 1][c + 1];

                    gy_blue += image[y + l][x + c].rgbtBlue * gy[l + 1][c + 1];
                    gy_green += image[y + l][x + c].rgbtGreen * gy[l + 1][c + 1];
                    gy_red += image[y + l][x + c].rgbtRed * gy[l + 1][c + 1];

                }
            }

            int sum_blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));
            int sum_green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int sum_red = round(sqrt(gx_red * gx_red + gy_red * gy_red));

            if(sum_blue > 255)
            {
                sum_blue = 255;
            }
            if(sum_green > 255)
            {
                sum_green = 255;
            }
            if(sum_red > 255)
            {
                sum_red = 255;
            }

            image_tmp[y][x].rgbtBlue = sum_blue;
            image_tmp[y][x].rgbtGreen = sum_green;
            image_tmp[y][x].rgbtRed = sum_red;
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
