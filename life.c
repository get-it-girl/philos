/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmika <wmika@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:29:26 by wmika             #+#    #+#             */
/*   Updated: 2022/04/13 20:44:13 by wmika            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tp;
	long			time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}

void	*check(void *philos)
{
	t_philo	*ph;

	ph = (t_philo *)philos;
	while (1)
	{
		pthread_mutex_lock(&ph->busy);
		if (get_time() >= ph->life_time)
		{
			mes(ph, "died\n");
			pthread_mutex_unlock(&ph->info->death);
			pthread_mutex_unlock(&ph->busy);
			return (NULL);
		}
		pthread_mutex_unlock(&ph->busy);
		if (ph->info->nbr != 1)
			usleep(10000);
		else
			ft_usleep(ph->info->to_die - 1);
	}
	return (NULL);
}

void	*phil_life(void *philos)
{
	t_philo		*ph;
	pthread_t	th1;

	ph = (t_philo *)philos;
	if (pthread_create(&th1, NULL, &check, (void *)(ph))
		|| pthread_detach(th1))
	{
		print_error("Thread error.\n");
		return ((void *)1);
	}
	while (1)
	{
		take_fork(ph);
		eat(ph);
		put_fork(ph);
	}
	return ((void *)0);
}

void	*limit_food(void *data)
{
	t_info	*info;
	int		count;
	int		i;

	count = 0;
	info = (t_info *)data;
	while (count <= info->must_eat)
	{
		i = 0;
		while (i < info->nbr)
		{
			pthread_mutex_lock(&info->philos[i].eat);
			i++;
		}
		count++;
	}
	mes(&info->philos[0], "Reached allowed amount of food\n");
	pthread_mutex_unlock(&info->death);
	return ((void *)0);
}

int	life(t_info *info)
{
	pthread_t	th;
	int			i;

	i = 0;
	pthread_mutex_lock(&info->death);
	info->threads = malloc(sizeof(pthread_t) * info->nbr);
	if (!info->threads)
		return (print_error("Malloc error.\n"));
	info->start = get_time();
	if (info->must_eat != -1
		&& (pthread_create(&th, NULL, &limit_food, (void *)(info)) != 0
		|| pthread_detach(th)))
		return (print_error("Thread error\n"));
	while (i < info->nbr)
	{
		info->philos[i].life_time = info->start + info->to_die;
		if (pthread_create(&info->threads[i], NULL, &phil_life, \
			(void *) &(info->philos[i])))
			return (print_error("Thread error.\n"));
		pthread_detach(info->threads[i]);
		usleep(400);
		i++;
	}
	return (0);
}
