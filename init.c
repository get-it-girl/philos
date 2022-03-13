#include"philo.h"

void start_life(t_info *info)
{
	int i;

	i = 0;
	pthread_mutex_init(&info->dead, NULL);
	pthread_mutex_init(&info->mes, NULL);
	pthread_mutex_lock(&info->dead);
	while (i < info->nbr_philo)
	{
		info->philos[i].index = i;
		info->philos[i].left_fork = i;
		info->philos[i].right_fork = (i + 1) % info->nbr_philo;
		info->philos[i].last_eat = timing();
		info->philos[i].count_eat = 0;
		info->philos[i].info = info;
		info->philos[i].is_dead = 0;
		info->philos[i].time_live = info->to_die;
		pthread_mutex_init(&info->philos[i].busy, NULL);
		// pthread_mutex_init(&info->philos[i].must_eat, NULL);
		// pthread_mutex_lock(&info->philos[i].must_eat);
		i++;
	}
}

int init_forks(t_info *info)
{
	int i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nbr_philo);
	if (!info->forks)
		return (print_error("Malloc error\n"));
	while(i < info->nbr_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	return (0);
}


int	init_info(t_info *info, int argc, char **argv)
{
	if ((argv[1] <= 0 || argv[2] <= 0 || argv[3] <= 0 || argv[4] <= 0))
		return (print_error("Incorrect arguments\n"));
	info->nbr_philo = ft_atoi(argv[1]);
	info->to_die = ft_atoi(argv[2]);
	info->to_eat = ft_atoi(argv[3]);
	info->to_sleep = ft_atoi(argv[4]);
	info->forks	= NULL;
	if (argc == 6 && argv[5] >= 0)
		info->nbr_eat = ft_atoi(argv[5]);
	else
		info->nbr_eat = 0;
	info->philos = malloc(sizeof(t_philo) * info->nbr_philo);
	if (!info->philos)
		return (print_error("Malloc error\n"));
	start_life(info);
	if (init_forks(info))
		return(1);
	return (0);
}
