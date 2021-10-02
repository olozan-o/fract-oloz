/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarlo <oscarlo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:52:52 by oscarlo           #+#    #+#             */
/*   Updated: 2021/10/02 17:35:48 by oscarlo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	assign_and_sign(int *aux, double *sign, int *i, char *src)
{
	while (src[*i] == ' ' || (src[*i] >= 9 && src[*i] <= 13))
		*i = *i + 1;
	*aux = 0;
	*sign = 1;
	if (src[*i] == '-' || src[*i] == '+')
	{	
		if (src[*i] == '-')
			*sign = -1;
		*i = *i + 1;
	}
}

double	ft_atof(char *src)
{
	int		i;
	int		aux;
	double	res;
	double	sign;

	if (!src || !src[0])
		return (exit_program("[ -- Incorrect numeric value -- ]\n"));
	i = 0;
	res = 0;
	assign_and_sign(&aux, &sign, &i, src);
	while ((src[i] == '.' && !aux) || is_numeric(src[i]))
	{
		if (src[i] == '.' || aux || !src[i + 1])
			aux++;
		if (src[i] != '.')
			res = res * 10 + (src[i] - '0');
		i++;
	}
	if (src[i])
		return (exit_program("[ -- Incorrect numeric value -- ]\n"));
	res = (double) res * pow(10, -(--aux));
	return (res * sign);
}

t_cmplx	init_cmplx(double re, double im)
{
	t_cmplx	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

void	*ft_alloc(int size)
{
	void			*res;
	unsigned char	*it;

	res = malloc(size);
	if (res)
	{
		it = (unsigned char *)res;
		while (size--)
			*it++ = '\0';
	}
	return (res);
}
