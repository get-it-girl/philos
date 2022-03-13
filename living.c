#include"philo.h"

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

	ph = (t_philo *) phil;
	while (1)
	{
		pthread_mutex_lock(&ph->busy);
		// pthread_mutex_lock(&ph->info->mes);
		// ft_putnbr(timing());
		// write(1, " - ", 4);
		// ft_putnbr(ph->info->t_start);
		// write(1, " = ", 4);
		// ft_putnbr(ph->time_live);
		// write(1, "\n", 1);
		// pthread_mutex_unlock(&ph->info->mes);
		if (timing() >= ph->time_live)
		{
			print_mes(ph, "died\n");
			ph->is_dead = 1;
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


void print_mes(t_philo *ph, char *str)
{
	int i;
	static int dead = 0;

	i = 0;
	pthread_mutex_lock(&ph->info->mes);
	if (dead == 0)
	{
		if (ft_strncmp(str, "died\n", 5) == 0)
			dead = 1;
		ft_putnbr((long)(timing() - ph->info->t_start));
		write(1, "\t", 1);
		ft_putnbr(ph->index + 1);
		write(1, "\t", 1);
		while (str[i])
			write(1, &str[i++], 1);
	}
	pthread_mutex_unlock(&ph->info->mes);
}


void *just_life(void *phil)
{
	t_philo *ph;
	pthread_t thread_2;

	ph = (t_philo *)phil;
	ph->last_eat = timing();
	ph->time_live = ph->last_eat + ph->info->to_die;
	// ft_putnbr(ph->last_eat);
	// write(1, "\n", 1);
	if (pthread_create(&thread_2, NULL, &check, (void *)phil) != 0)
	{
		print_error("Thread error\n");
		return((void *)1);
	}	
	pthread_detach(thread_2);
	while (1)
	{
		take_f(phil);
		eat(phil);
		put_f(phil);
		print_mes(phil, "is thinking\n");
	}
	return ((void *)0);
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
		if (pthread_create(&thread_1, NULL, &just_life, (void *)(&info->philos[i])) != 0)
			return (print_error("Thread error\n"));
		pthread_detach(thread_1);
		// usleep(600);
		i++;
	}

	return (0);
}