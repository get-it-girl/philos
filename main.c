/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmika <wmika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:28:59 by wmika             #+#    #+#             */
/*   Updated: 2022/04/13 20:29:00 by wmika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cleaner(t_info *info)
{
	int	i;

	i = 0;
	if (info->philos)
	{
		while (i < info->nbr)
		{
			pthread_mutex_destroy(&info->philos[i].busy);
			pthread_mutex_destroy(&info->philos[i++].eat);
		}
		free(info->philos);
		pthread_mutex_destroy(&info->death);
		pthread_mutex_destroy(&info->mes);
	}
	if (info->forks)
	{
		i = 0;
		while (i < info->nbr)
			pthread_mutex_destroy(&info->forks[i++]);
		free(info->forks);
	}
	if (info->threads)
		free(info->threads);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (print_error("Wrong amount of arguments.\n"));
	if (init(&info, argc, argv) == 1)
		return (cleaner(&info));
	if (life(&info) == 2)
		return (cleaner(&info));
	pthread_mutex_lock(&info.death);
	pthread_mutex_unlock(&info.death);
	return (0);
}
