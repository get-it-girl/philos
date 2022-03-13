#include"philo.h"

void take_f(t_philo *ph)
{
	pthread_mutex_lock(&ph->info->forks[ph->left_fork]);
	print_mes(ph, "has taken a fork\n");
	pthread_mutex_lock(&ph->info->forks[ph->right_fork]);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = timing();
	while ((timing() - start_time) < time_in_ms)
		usleep(time_in_ms);
}
void put_f(t_philo *ph)
{
	pthread_mutex_unlock(&ph->info->forks[ph->left_fork]);
	print_mes(ph, "is sleeping\n");
	pthread_mutex_unlock(&ph->info->forks[ph->right_fork]);
	ft_usleep(ph->info->to_sleep);
}


void eat(t_philo *ph)
{
	int i;
	i=0;

	pthread_mutex_lock(&ph->busy);
	ph->count_eat++;
	// ph->last_eat = timing();
	ph->time_live = timing() + ph->info->to_die;
	print_mes(ph, "is eating\n");
	ft_usleep(ph->info->to_eat);
	pthread_mutex_unlock(&ph->busy);
	// pthread_mutex_unlock(&ph->must_eat);
}