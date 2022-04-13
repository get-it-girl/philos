/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmika <wmika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:28:50 by wmika             #+#    #+#             */
/*   Updated: 2022/04/13 20:28:51 by wmika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_info *info, int argc, char **argv)
{
	(void)argc;
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 60
		|| ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (1);
	if (argc == 6 && ft_atoi(argv[5]) > 0)
		info->must_eat = ft_atoi(argv[5]);
	else
		info->must_eat = -1;
	info->nbr = ft_atoi(argv[1]);
	info->to_die = ft_atoi(argv[2]);
	info->to_eat = ft_atoi(argv[3]);
	info->to_sleep = ft_atoi(argv[4]);
	return (0);
}

int	init_info(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(t_philo) * info->nbr);
	if (!info->philos)
		return (print_error("Malloc error.\n"));
	i = 0;
	while (i < info->nbr)
	{
		info->philos[i].index = i;
		info->philos[i].left = i;
		info->philos[i].right = (i + 1) % info->nbr;
		info->philos[i].info = info;
		pthread_mutex_init(&(info->philos[i].busy), NULL);
		pthread_mutex_init(&(info->philos[i].eat), NULL);
		i++;
	}
	pthread_mutex_init(&(info->death), NULL);
	pthread_mutex_init(&(info->mes), NULL);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nbr);
	if (!info->forks)
		return (print_error("Malloc error.\n"));
	while (--i >= 0)
		pthread_mutex_init(&(info->forks[i]), NULL);
	return (0);
}

int	init(t_info *info, int argc, char **argv)
{
	if (init_args(info, argc, argv) || init_info(info))
		return (print_error("Incorrect arguments.\n"));
	return (0);
}
