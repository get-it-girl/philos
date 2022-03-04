#include <philo.h>

long	timing(void)
{
	struct timeval	tp;
	long			time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}


int living(t_info *info)
{
	info->t_start = timing();
	
}