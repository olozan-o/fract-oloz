/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarlo <oscarlo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 14:15:00 by oscarlo           #+#    #+#             */
/*   Updated: 2021/10/02 19:47:12 by oscarlo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H

# define FRACTAL_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "./minilibx-linux/mlx.h"

# define WIDTH		500
# define HEIGHT		500

# if __APPLE__
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_UP 126
#  define KEY_DOWN	125
#  define ESCAPE_KEY 53
#  define MOUSE_UP	4
#  define MOUSE_DOWN	5
# elif __linux__
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_UP 65365
#  define KEY_DOWN	65367
#  define ESCAPE_KEY 65307
#  define  MOUSE_UP   0X00000004
#  define  MOUSE_DOWN 0X00000005
# endif

# define KEY_UP			126
# define KEY_DOWN			125
# define KEY_LEFT			123
# define KEY_RIGHT		124

# define MAIN_PAD_ESC		53

typedef struct s_show
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*mlx_img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;

}		t_mlx_show;

typedef struct s_color
{
	int8_t	channel[4];
}		t_color;

typedef struct s_complex
{
	double	re;
	double	im;
}		t_cmplx;

typedef struct s_img
{
	void	*image;
	char	*data_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}		t_img;

typedef struct s_fract
{
	void	*mlx;
	void	*window;
	t_img	*image;
	int		max_it;
	int		color_shift;
	t_cmplx	min;
	t_cmplx	max;
	t_cmplx	factor;
	t_cmplx	c;
	t_cmplx	k;
	int		(*formula)(struct s_fract	*fractol);
}		t_fract;

double	ft_atof(char *src);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
int		exit_program(char *msg);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	*ft_alloc(int size);
t_cmplx	init_cmplx(double re, double im);
void	entree_public(t_fract *fractol);
t_img	*rideau(void *mlx);
t_fract	*start_the_dance(char *name, void *mlx);
void	put_it_on(t_fract *fractol);
int		do_mandelbrot(t_fract *fractol);
int		do_julia(t_fract *fractol);
t_color	get_color(int iteration, t_fract *fractol);
int		key_press(int key, t_fract *fractol);
int		zoom(int button, int x, int y, t_fract *fractol);

#endif
