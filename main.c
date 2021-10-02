/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarlo <oscarlo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:48:28 by oscarlo           #+#    #+#             */
/*   Updated: 2021/10/02 17:29:48 by oscarlo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	exit_program(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(0);
	return (0);
}

void	entree_public(t_fract *fractol)
{
	fractol->max_it = 30;
	fractol->min = init_cmplx(-2.0, -2.0);
	fractol->max.re = 2.0;
	fractol->max.im = fractol->min.im
		+ (fractol->max.re - fractol->min.re) * HEIGHT / WIDTH;
	fractol->k = init_cmplx(-0.4, 0.6);
	fractol->color_shift = 0;
}

t_img	*rideau(void *mlx)
{
	t_img		*image;

	image = (t_img *)ft_alloc(sizeof(t_img));
	if (!image)
		exit_program("\nIMAGE INITIATION ERROR\n\n");
	image->image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image->image)
		exit_program("\nIMAGE INITIATION ERROR\n\n");
	image->data_addr = mlx_get_data_addr(
			image->image,
			&(image->bits_per_pixel),
			&(image->size_line),
			&(image->endian));
	return (image);
}

int	deal_with_arguments(int argc, char **argv)
{
	if (argc <= 1 || (argc < 4 && !ft_strncmp(argv[1], "julia\0", 6)))
	{
		ft_putstr_fd("[ -- Incorrect number of arguments -- ]\n", 1);
		ft_putstr_fd("Usage:\nMandelbrot set --> ./fract-oloz mandelbrot\n", 1);
		exit_program("Julia set --> ./fract-oloz julia #f #f\n");
	}
	if (!ft_strncmp(argv[1], "julia\0", 6))
		return (2);
	if (!ft_strncmp(argv[1], "mandelbrot\0", 11))
		return (1);
	ft_putstr_fd("Usage:\nMandelbrot set --> ./fract-oloz mandelbrot\n", 1);
	exit_program("Julia set --> ./fract-oloz julia #f #f\n");
	return (0);
}

int	main(int argc, char **argv)
{
	void	*the_show;
	t_fract	*main_obj;

	the_show = mlx_init();
	if (deal_with_arguments(argc, argv) == 1)
	{
		main_obj = start_the_dance("Mandelbrot", the_show);
		put_it_on(main_obj);
	}
	else if (deal_with_arguments(argc, argv) == 2)
	{
		main_obj = start_the_dance("Julia", the_show);
		main_obj->k = init_cmplx(
				ft_atof(argv[2]),
				ft_atof(argv[3]));
		put_it_on(main_obj);
	}
	mlx_loop(the_show);
	return (0);
}
