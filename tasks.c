#include"philo.h"

void take_f(t_philo *ph)
{
	pthread_mutex_lock(&ph->info->forks[ph->left_fork]);
	print_mess(ph, "took left fork\n");
	pthread_mutex_lock(&ph->info->forks[ph->right_fork]);
	print_mess(ph, "took right fork\n");
}

void put_f(t_philo *ph)
{
	pthread_mutex_unlock(&ph->info->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->info->forks[ph->right_fork]);
	print_mess(ph, "is sleeping\n");
	usleep((time_t)ph->info->to_sleep);
}

void eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->busy);
	ph->count_eat++;
	ph->last_eat = timmng();
	ph->time_live = ph->last_eat + ph->info->to_die;
	print_mes(ph, "is eating\n");
	usleep((time_t)ph->info->to_eat);
	pthread_mutex_unlock(&ph->busy);
	pthread_mutex_unlock(&ph->must_eat);
}