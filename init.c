#include"philo.h"

void	start_life(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->dead, NULL);
	pthread_mutex_init(&info->mes, NULL);
	pthread_mutex_lock(&info->dead);
	while (i < info->nbr_philo)
	{
		info->philos[i].index = i;
		info->philos[i].left_fork = i;
		info->philos[i].right_fork = (i + 1) % info->nbr_philo;
		info->philos[i].info = info;
		info->philos[i].eating = 0;
		info->philos[i].time_live = timing() + info->to_die;
		pthread_mutex_init(&info->philos[i].busy, NULL);
		pthread_mutex_init(&info->philos[i].must_eat, NULL);
		pthread_mutex_lock(&info->philos[i].must_eat);
		i++;
	}
}

int	init_forks(t_info *info)
{
	int	i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nbr_philo);
	if (!info->forks)
		return (print_error("Malloc error\n"));
	while (i < info->nbr_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	if ((ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0
			|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0))
		return (1);
	return (0);
}

int	init_info(t_info *info, int argc, char **argv)
{
	if (check_args(argc, argv) == 1)
		return (print_error("Incorrect arguments\n") + 1);
	info->nbr_philo = ft_atoi(argv[1]);
	info->to_die = ft_atoi(argv[2]);
	info->to_eat = ft_atoi(argv[3]);
	info->to_sleep = ft_atoi(argv[4]);
	info->forks = NULL;
	if (argc == 6 && argv[5] >= 0)
		info->nbr_eat = ft_atoi(argv[5]);
	else
		info->nbr_eat = 0;
	info->philos = malloc(sizeof(t_philo) * info->nbr_philo);
	if (!info->philos)
		return (print_error("Malloc error\n"));
	start_life(info);
	if (init_forks (info))
		return (1);
	return (0);
}
