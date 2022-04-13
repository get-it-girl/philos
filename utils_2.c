/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmika <wmika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:43:07 by wmika             #+#    #+#             */
/*   Updated: 2022/04/13 20:44:44 by wmika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mes(t_philo *ph, char *str)
{
	static int	dead = 0;

	pthread_mutex_lock(&ph->info->mes);
	if (dead == 0)
	{		
		if (ft_strncmp(str, "died\n", 6) == 0
			|| ft_strncmp(str, "Reached", 6) == 0)
			dead = 1;
		if (ft_strncmp(str, "Reached", 6) == 0)
			ft_putnbr((get_time() - ph->info->start));
		else
		{
			ft_putnbr((get_time() - ph->info->start));
			write(1, "\t", 1);
			ft_putnbr(ph->index + 1);
		}
		write(1, "\t", 1);
		while (*str)
			write(1, str++, 1);
	}
	pthread_mutex_unlock(&ph->info->mes);
}

int	print_error(char *str)
{
	while (*str)
		write(1, str++, 1);
	return (1);
}

void	ft_putnbr(long n)
{
	char	s[20];
	int		i;

	i = 0;
	if (n == 0)
		write(1, "0", 2);
	while (n > 0)
	{
		s[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		write(1, &s[i], 1);
		i--;
	}
}
