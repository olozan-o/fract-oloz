/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarlo <oscarlo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 00:18:47 by oscarlo           #+#    #+#             */
/*   Updated: 2021/10/02 17:35:33 by oscarlo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	move(int key, t_fract *fractol)
{
	t_cmplx	delta;

	delta = init_cmplx(fabs(fractol->max.re - fractol->min.re),
			fabs(fractol->max.im - fractol->min.im));
	if (key == KEY_LEFT)
	{
		fractol->min.re -= delta.re * 0.05;
		fractol->max.re -= delta.re * 0.05;
	}
	else if (key == KEY_RIGHT)
	{
		fractol->min.re += delta.re * 0.05;
		fractol->max.re += delta.re * 0.05;
	}
	else if (key == KEY_UP)
	{
		fractol->min.im += delta.im * 0.05;
		fractol->max.im += delta.im * 0.05;
	}
	else if (key == KEY_DOWN)
	{
		fractol->min.im -= delta.im * 0.05;
		fractol->max.im -= delta.im * 0.05;
	}
	put_it_on(fractol);
}

int	key_press(int key, t_fract *fractol)
{
	if (key == MAIN_PAD_ESC)
		exit(0);
	else if (key == KEY_LEFT || key == KEY_RIGHT
		|| key == KEY_UP || key == KEY_DOWN)
		move(key, fractol);
	return (0);
}

static double	do_inter(double start, double end, double interp)
{
	return (start + ((end - start) * interp));
}

int	zoom(int button, int x, int y, t_fract *fractol)
{
	t_cmplx		mouse;
	double		interp;
	double		zoom;

	if (button == MOUSE_UP || button == MOUSE_DOWN)
	{
		mouse = init_cmplx(
				(double)x / (WIDTH / (fractol->max.re - fractol->min.re))
				+ fractol->min.re,
				(double)y / (HEIGHT / (fractol->max.im - fractol->min.im))
				* -1 + fractol->max.im);
		if (button == MOUSE_UP)
			zoom = 0.80;
		else
			zoom = 1.20;
		interp = 1.0 / zoom;
		fractol->min.re = do_inter(mouse.re, fractol->min.re, interp);
		fractol->min.im = do_inter(mouse.im, fractol->min.im, interp);
		fractol->max.re = do_inter(mouse.re, fractol->max.re, interp);
		fractol->max.im = do_inter(mouse.im, fractol->max.im, interp);
		put_it_on(fractol);
	}
	return (0);
}

t_color	get_color(int iteration, t_fract *fractol)
{
	t_color	color;
	double	t;

	t = (double)iteration / fractol->max_it;
	color.channel[0] = 0;
	color.channel[(0 + fractol->color_shift) % 3 + 1]
		= (int8_t)(9 * (1 - t) * pow(t, 3) * 255);
	color.channel[(1 + fractol->color_shift) % 3 + 1]
		= (int8_t)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	color.channel[(2 + fractol->color_shift) % 3 + 1]
		= (int8_t)(8.5 * pow((1 - t), 3) * t * 255);
	return (color);
}
