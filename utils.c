# include "philo.h"

int print_error(int flag)
{
	if (flag == 1)
		printf("Wrong amount of arguments\n");
	if (flag == 2)
		printf("Incorrect arguments\n");
	if (flag == 3)
		printf("Initializing mutex errror\n");
	if (flag == 4)
		printf("Threads error\n");
	return (1);
}

void	ft_usleep(int time_in_ms, t_info *info)
{
	long int	start_time;
	long int	now_time;

	start_time = get_time();
	now_time = get_time();
	while (info->dead == 0 
		&& (now_time - start_time) <= time_in_ms)
	{
		usleep(1);
		now_time = get_time();
	}
}

void messege(t_philos *ph, char *str)
{
	pthread_mutex_lock(&(ph->info->mes));
	if (!(ph->info->dead))
	{
		printf("%lli\t", get_time() - ph->info->start_time);
		printf("%i\t%s", ph->index, str);
	}
	pthread_mutex_unlock(&(ph->info->mes));
}

int	ft_atoi(char *str)
{
	long int nbr;
	int minus;
	int i;

	nbr = 0;
	minus = 1;
	while((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		minus = -1;
	else if (*str == '+')
		str++;
	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * 10 + (str[i++] - '0');
		else
			return (-1);
	}
	return ((int)(nbr * minus));
}

long	get_time(void)
{
	struct timeval	tp;
	long			time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}