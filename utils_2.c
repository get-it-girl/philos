#include"philo.h"

long	timing(void)
{
	struct timeval	tp;
	long			time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}

void	*check(void *phil)
{
	t_philo	*ph;

	ph = (t_philo *) phil;
	while (1)
	{
		pthread_mutex_lock(&ph->busy);
		if (ph->eating != 1 && timing() >= ph->time_live)
		{
			print_mes(ph, "died\n");
			pthread_mutex_unlock(&ph->info->dead);
			pthread_mutex_unlock(&ph->busy);
			return (NULL);
		}
		pthread_mutex_unlock(&ph->busy);
		usleep(10000);
	}
}

void	ft_putnbr(long n)
{
	char	s[20];
	int		i;

	i = 0;
	if (n == 0)
		write(1, "0", 2);
	while (n > 0)
	{
		s[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		write(1, &s[i], 1);
		i--;
	}
}
