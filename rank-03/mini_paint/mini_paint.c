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
typedef struct s_circle
{
		char type;
		float x;
		float y;
		float radius;
		char character;
}				t_circle;

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

int	get_circle_info(FILE *file, t_circle *circle)
{
	int scan_value;

	scan_value = fscanf(file, "%c %f %f %f %c\n",
	&circle->type, &circle->x, &circle->y, &circle->radius, &circle->character);

	if (scan_value == EOF)
		return (-1);
	if (scan_value != 5 || circle->radius <= 0.0
	|| (circle->type != 'C' && circle->type != 'c'))
		return (0);
	return (1);
}

float	ft_square(float number)
{
	return (number * number);
}

float	ft_absf(float number)
{
	return ((number < 0) ? -number : number);
}

void	draw_circle(t_circle circle, t_canvas canvas)
{
	for (int y = 0; y < canvas.height; y++)
	{
		for (int x = 0; x < canvas.width; x++)
		{
			const float distance = sqrtf(ft_square(x - circle.x) + ft_square(y - circle.y));
			if (distance <= circle.radius)
			{
				if (circle.type == 'C' || (ft_absf(distance - circle.radius)) < 1.0)
					canvas.canvas[y * canvas.width + x] = circle.character;
			}
		
		}
	}
}

int	read_draw_circles(FILE *file, t_canvas canvas)
{
	int scan_value;
	t_circle circle;

	while ((scan_value = get_circle_info(file, &circle)) == 1)
	{
		draw_circle(circle, canvas);
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
		if (file && get_canvas_info(file, &canvas) && read_draw_circles(file, canvas))
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