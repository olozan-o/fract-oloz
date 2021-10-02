/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2-str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarlo <oscarlo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:36:16 by oscarlo           #+#    #+#             */
/*   Updated: 2021/10/02 17:37:26 by oscarlo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	if ((!s1 && !s2) || n == 0)
		return (0);
	else if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while (p1[i] != '\0' && p2[i] != '\0' && i < n - 1
		&& p1[i] == p2[i])
		i++;
	return (p1[i] - p2[i]);
}

void	ft_putnbr_fd(int nb, int fd)
{
	char	chiffre;

	if (nb == -2147483648)
		write(fd, "-2147483648", 11);
	else if (nb < 0)
	{
		nb = -nb;
		write(fd, "-", 1);
	}
	if (nb >= 0)
	{
		if (nb >= 10)
			ft_putnbr_fd(nb / 10, fd);
		chiffre = '0' + (nb % 10);
		write(fd, &chiffre, 1);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	size;

	size = 0;
	while (*(s + size))
		size++;
	write(fd, s, size);
}
