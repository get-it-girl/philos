
# include "philo.h"

int m_init(t_info *info)
{
	int i;

	i = 0;
	while (i < info->nbr_ph)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(info->busy), NULL))
		return (1);
	if (pthread_mutex_init(&(info->mes), NULL))
		return (1);
	return (0);
}

void ph_init(t_info *info)
{
	int i;

	i = 0;
	while (i < info->nbr_ph)
	{
		info->philos[i].index = i;
		info->philos[i].nbr_meals = 0;
		info->philos[i].left_fork = i;
		info->philos[i].right_fork = (i + 1) % info->nbr_ph;
		info->philos[i].last_ate = 0;
		info->philos[i].info = info;
		i++;
	}
}

int	init(t_info *info, char **argv)
{
	info->nbr_ph = ft_atoi(argv[1]);
	info->to_die = ft_atoi(argv[2]);
	info->to_eat = ft_atoi(argv[3]);
	info->to_sleep = ft_atoi(argv[4]);
	info->nbr_meals = -1;
	info->dead = 0;
	info->finished = 0;
	if (info->nbr_ph < 0 || info->to_die < 60 
		|| info->to_eat < 60 || info->to_sleep < 60
		|| info->nbr_ph > 200)
		return (2);
	if (argv[5])
	{
		info->nbr_meals = ft_atoi(argv[5]);
		if (info->nbr_meals <= 0)
			return(2);
	}
	if (m_init(info))
		return (3);
	ph_init(info);
	return (0);
}