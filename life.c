# include "philo.h"


void cycle_1(t_philos *ph)
{
	pthread_mutex_lock(&ph->info->forks[ph->left_fork]);
	messege(ph, "has taken a left fork\n");
	pthread_mutex_lock(&ph->info->forks[ph->right_fork]);
	messege(ph, "has taken a right fork\n");
	pthread_mutex_lock(&(ph->info->busy));
	messege(ph, "is eating\n");
	ph->last_ate = get_time();
	pthread_mutex_lock(&(ph->info->busy));
	ft_usleep(ph->info->to_eat, ph->info);
	ph->nbr_meals++;
	pthread_mutex_unlock(&ph->info->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->info->forks[ph->right_fork]);
}

void cycle_2(t_philos *ph)
{
	messege(ph, "is sleeping\n");
	ft_usleep(ph->info->to_sleep, ph->info);
	messege(ph, "is thinling\n");
}

void *exist(void *ph_info)
{
	t_philos *ph;

	ph = (t_philos *)ph_info;
	if (ph->index % 2)
		usleep(15000);
	while (!(ph->info->dead))
	{
		cycle_1(ph);
		if (ph->info->finished)
			break;
		cycle_2(ph);		
	}
	return (NULL);
}


int life(t_info *info)
{
	int i;
	t_philos *ph;

	i = 0;
	ph = info->philos;
	info->start_time = get_time();
	while (i < info->nbr_ph)
	{
		if (pthread_create(&ph[i].ph_thread, NULL, *exist, (void *)&ph[i]))
			return (1);
		ph[i].last_ate = get_time();
		i++;
	}
	// checker 
	// endofgame
	return (0);
}