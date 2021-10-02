/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_the_fractal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarlo <oscarlo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:48:46 by oscarlo           #+#    #+#             */
/*   Updated: 2021/10/02 19:54:57 by oscarlo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	do_julia(t_fract *fractol)
{
	int		iteration;
	t_cmplx	z;

	iteration = 0;
	z = init_cmplx(fractol->c.re, fractol->c.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
		&& iteration < fractol->max_it)
	{
		z = init_cmplx(
				pow(z.re, 2.0) - pow(z.im, 2.0) + fractol->k.re,
				2.0 * z.re * z.im + fractol->k.im);
		iteration++;
	}
	return (iteration);
}

int	do_mandelbrot(t_fract *fractol)
{
	int		iteration;
	t_cmplx	z;

	iteration = 0;
	z = init_cmplx(fractol->c.re, fractol->c.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
		&& iteration < fractol->max_it)
	{
		z = init_cmplx(
				pow(z.re, 2.0) - pow(z.im, 2.0) + fractol->c.re,
				2.0 * z.re * z.im + fractol->c.im);
		iteration++;
	}
	return (iteration);
}

static void	put_pixel(t_fract *fractol, int x, int y, t_color color)
{
	int	i;

	i = (x * fractol->image->bits_per_pixel / 8)
		+ (y * fractol->image->size_line);
	fractol->image->data_addr[i] = color.channel[3];
	fractol->image->data_addr[++i] = color.channel[2];
	fractol->image->data_addr[++i] = color.channel[1];
	fractol->image->data_addr[++i] = color.channel[0];
}

void	put_it_on(t_fract *fractol)
{
	int			y;
	int			x;
	t_color		color;

	y = 0;
	fractol->factor = init_cmplx(
			(fractol->max.re - fractol->min.re) / (WIDTH - 1),
			(fractol->max.im - fractol->min.im) / (HEIGHT - 1));
	while (y < HEIGHT)
	{
		fractol->c.im = fractol->max.im - y * fractol->factor.im;
		x = 0;
		while (x < WIDTH)
		{
			fractol->c.re = fractol->min.re + x * fractol->factor.re;
			color = get_color(fractol->formula(fractol), fractol);
			put_pixel(fractol, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->window,
		fractol->image->image, 0, 0);
}

t_fract	*start_the_dance(char *name, void *mlx)
{
	t_fract	*fractol;

	fractol = (t_fract *)ft_alloc(sizeof(t_fract));
	if (!fractol)
		exit_program("\n\nERRROR INITIATING FRACTAL\n");
	fractol->mlx = mlx;
	fractol->window = mlx_new_window(mlx, WIDTH, HEIGHT, name);
	if (!fractol->window)
		exit_program("\n\nERROR INITIATING WINDOW\n");
	fractol->image = rideau(mlx);
	if (!ft_strncmp(name, "Julia", 5))
		fractol->formula = &do_julia;
	else if (!ft_strncmp(name, "Mandelbrot", 10))
		fractol->formula = &do_mandelbrot;
	entree_public(fractol);
	mlx_hook(fractol->window, 2, 0, key_press, fractol);
	mlx_hook(fractol->window, 17, (1L << 17), exit_program,
		"Thank you dear, hope you liked it.\n");
	mlx_hook(fractol->window, 4, 0, zoom, fractol);
	return (fractol);
}
