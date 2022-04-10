#include "philo.h"

void take_fork(t_philo	*ph)
{
	pthread_mutex_lock(&ph->info->forks[ph->left]);
	pthread_mutex_lock(&ph->info->forks[ph->right]);
	mes(ph, "has taken a fork\n");
}

void	ft_usleep(int time_in_ms)
{
	long int	start_time;
	long int	now_time;

	start_time = get_time();
	now_time = get_time();
	while ((now_time - start_time) <= time_in_ms)
	{
		usleep(1);
		now_time = get_time();
	}
}

void put_fork( t_philo *ph)
{
	pthread_mutex_unlock(&ph->info->forks[ph->left]);
	pthread_mutex_unlock(&ph->info->forks[ph->right]);
	mes(ph, "is sleeping\n");
	ft_usleep(ph->info->to_sleep);
	mes(ph, "is thinking\n");
}

void eat(t_philo *ph)
{	
	pthread_mutex_lock(&ph->busy);
	ph->life_time = get_time() + ph->info->to_die;
	mes(ph, "is eating\n");
	ft_usleep(ph->info->to_eat);
	pthread_mutex_unlock(&ph->busy);
	if (ph->info->must_eat != -1)
		pthread_mutex_unlock(&ph->eat);
}