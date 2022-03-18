#include"philo.h"

int	print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (1);
}

int	cleaner(t_info *info)
{
	int	i;

	i = 0;
	if (info->philos)
	{
		while (i < info->nbr_philo)
		{
			pthread_mutex_destroy(&info->philos[i].busy);
			pthread_mutex_destroy(&info->philos[i].must_eat);
			i++;
		}
		free(info->philos);
		pthread_mutex_destroy(&info->dead);
		pthread_mutex_destroy(&info->mes);
	}
	if (info->forks)
	{
		i = 0;
		while (i < info->nbr_philo)
			pthread_mutex_destroy(&info->forks[i++]);
		free(info->forks);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		out;

	if (argc > 4)
	{
		out = init_info(&info, argc, argv);
		if (out == 1)
			return (cleaner(&info));
		if (out == 2)
			return (1);
		if (living(&info) == 1)
			return (cleaner(&info));
		pthread_mutex_lock(&info.dead);
		pthread_mutex_unlock(&info.dead);
		cleaner(&info);
	}
	else
		return (print_error("Wrong amount of arguments\n"));
	return (0);
}
