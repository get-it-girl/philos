#include"philo.h"

void take_f(t_philo *ph)
{
	pthread_mutex_lock(&ph->info->forks[ph->left_fork]);
	print_mes(ph, "has taken a fork\n");
	pthread_mutex_lock(&ph->info->forks[ph->right_fork]);
	print_mes(ph, "has taken a fork\n");
}

void	ft_usleep(int time_in_ms)
{
	long int	start_time;
	long int	now_time;

	start_time = timing();
	now_time = timing();
	while ((now_time - start_time) < time_in_ms)
	{
		usleep(1);
		now_time = timing();
	}
}
void put_f(t_philo *ph)
{
	pthread_mutex_unlock(&ph->info->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->info->forks[ph->right_fork]);
	print_mes(ph, "is sleeping\n");
	ft_usleep(ph->info->to_sleep);
}


void eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->busy);
	ph->eating = 1;
	ph->count_eat++;
	ph->time_live = timing() + ph->info->to_die;
	print_mes(ph, "is eating\n");
	ft_usleep(ph->info->to_eat);
	ph->eating = 0;
	pthread_mutex_unlock(&ph->busy);
	pthread_mutex_unlock(&ph->must_eat);
}