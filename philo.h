
#ifndef PHILO_H
# define PHILO_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <pthread.h>

typedef struct s_info
{
	long t_start;
	int	nbr_philo;
	int to_die;
	int to_eat;
	int to_sleep;
	int nbr_eat;
	t_philo *philos;
	pthread_mutex_t *forks;
	pthread_mutex_t dead;
}	t_info;

typedef struct s_philo
{
	int left_fork;
	int right_fork;
	int last_eat;
	int time_live;
	int count_eat;
	int index;
	t_info *info;
	pthread_mutex_t busy;
	pthread_mutex_t must_eat;
}	t_philo;


int print_error(char *str);
int	init_info(t_info *info, int argc, char **argv);
int	ft_atoi(const char *str);



#endif
