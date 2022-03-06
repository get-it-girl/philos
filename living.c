#include <philo.h>

long	timing(void)
{
	struct timeval	tp;
	long			time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}

void *check(void *phil)
{
	t_philo *ph;

	while (1)
	{
		ph = (t_philo *) phil;
		pthread_mutex_lock(&ph->busy);
		if (timing() - ph->info->t_start >= ph->time_live)
		{
			print_mes(ph, "is dead\n");
			pthread_mutex_unlock(&ph->info->dead);
			pthread_mutex_unlock(&ph->busy);
			return (NULL);
		}
		pthread_mutex_unlock(&ph->busy);
		usleep(10000);
	}
}

void	ft_putnbr(long num)
{
	char	s[20];
	int		i;

	i = 0;

	while (n > 0)
	{
		s[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		write(fd, &s[i], 1);
		i--;
	}
}


void print_mes(t_philo *ph, char *str)
{
	int i;

	i = 0;
	pthread_mutex_lock(&ph->info->mes);
	ft_putnbr(timming() - ph->info->t_start);
	write(1, "\t", 1);
	if (ph->count_eat != ph->info->nbr_eat)
	{
		ft_putnbr(ph->index + 1);
		write(1, " ", 1);
	}
	while (str[i])
		write(1, &str[i++], 1);
	pthread_mutex_unlock(&ph->info->mes);
}


void *just_life(void *phil)
{
	t_philo *ph;
	pthread_t thread_2;

	ph = (t_philo *)phil;
	if (pthread_creat(&thread_2, NULL, &check, (void *)phil) != 0)
		return((void *)print_error("Thread error\n"));
	pthread_detach(thread_2);
	while (1)
	{
		take_f(phil);
		eat(phil);
		put_f(phil);
		print_mes(phil, "is thinking\n");
	}
}

int living(t_info *info)
{
	pthread_t thread_1;
	int i;

	info->t_start = timing();
	i = 0;
	// if (info->nbr_eat != 0 && (pthread_create(&thread_1, NULL, &count_life, info) != 0 ||
	// 	pthread_detach(thread_1) != 0))
	// 	return(print_error("Thread error\n"));
	while (i < info->nbr_philo)
	{
		if (pthread_create(&thread_1, NULL, &just_life, (void *)(&info->philos[i])) != 0 ||
			pthread_detach(thread_1) != 0)
			return (print_error("Thread error\n"));
		i++;
	}
	pthread_mutex_lock(&info->dead);
	pthread_mutex_unlock(&info->dead);
	return (0);
}