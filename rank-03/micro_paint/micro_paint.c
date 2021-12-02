#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct s_canvas
{
	int width;
	int height;
	char background;
	char *canvas;
}				t_canvas;
typedef struct s_rectangle
{
		char type;
		float x;
		float y;
		float x2;
		float y2;
		char character;
}				t_rectangle;

int	get_canvas_info(FILE *file, t_canvas *canvas)
{
	const int scan_value = fscanf(file, "%d %d %c\n",
	&canvas->width,&canvas->height, &canvas->background);

	if (scan_value != 3
	|| canvas->width <= 0 || canvas->width > 300
	|| canvas->height <= 0 || canvas->height > 300)
		return (0);
	canvas->canvas = malloc(canvas->width * canvas->height + 1);
	memset(canvas->canvas, canvas->background, canvas->width * canvas->height);
	canvas->canvas[canvas->width * canvas->height] = '\0';
	return (1);
}

int	get_rectangle_info(FILE *file, t_rectangle *rectangle)
{
	int scan_value;
	float width;
	float height;
	
	scan_value = fscanf(file, "%c %f %f %f %f %c\n",
	&rectangle->type, &rectangle->x, &rectangle->y, &width, &height, &rectangle->character);

	if (scan_value == EOF)
		return (-1);
	if (scan_value != 6 || width <= 0.0 || height <= 0.0
	|| (rectangle->type != 'R' && rectangle->type != 'r'))
		return (0);
	rectangle->x2 = rectangle->x + width;
	rectangle->y2 = rectangle->y + height;
	return (1);
}

void	draw_rectangle(t_rectangle rectangle, t_canvas canvas)
{
	for (int y = 0; y < canvas.height; y++)
	{
		for (int x = 0; x < canvas.width; x++)
		{

			if (x >= rectangle.x && x <= rectangle.x2 && y >= rectangle.y && y <= rectangle.y2)
			{
				if (rectangle.type == 'R'
				|| x - rectangle.x < 1.0 || rectangle.x2 - x < 1.0
				|| y - rectangle.y < 1.0 || rectangle.y2 - y < 1.0)
					canvas.canvas[y * canvas.width + x] = rectangle.character;
			}
		
		}
	}
}

int	read_draw_rectangles(FILE *file, t_canvas canvas)
{
	int scan_value;
	t_rectangle rectangle;

	while ((scan_value = get_rectangle_info(file, &rectangle)) == 1)
	{
		draw_rectangle(rectangle, canvas);
	}
	if (scan_value == -1)
	{
		for (int i = 0; canvas.canvas[i]; i++)
		{
			if (i && i % canvas.width == 0)
				write(1, "\n", 1);
			write(1, &canvas.canvas[i], 1);
		}
		write(1, "\n", 1);
		return (1);
	}
	else
		return (0);
}

int main(int argc, char *argv[])
{
	int return_value = 1;
	FILE *file = NULL;
	t_canvas canvas;

	canvas.canvas = NULL;
	if (argc == 2)
	{
		file = fopen(argv[1], "r");
		if (file && get_canvas_info(file, &canvas) && read_draw_rectangles(file, canvas))
		{
			return_value = 0;
		}
		else
			write(1, "Error: Operation file corrupted\n", 32);
	}
	else
		write(1, "Error: argument\n", 16);

	if (canvas.canvas)
		free(canvas.canvas);
	if (file)
		fclose(file);
	return (return_value);
}