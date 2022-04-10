#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

#include<stdio.h>

struct	s_info;

typedef struct s_philo
{
	int index;
	long life_time;
	int left;
	int right;
	struct s_info *info;
	pthread_mutex_t busy;
	pthread_mutex_t eat;
} t_philo;

typedef struct s_info
{
	long start;
	int	nbr;
	int to_die;
	int to_eat;
	int to_sleep;
	int must_eat;
	t_philo *philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t death;
	pthread_mutex_t mes;
}	t_info;

int	init(t_info *info, int argc, char **argv);
int print_error(char *str);
int	ft_atoi(const char *str);
long get_time(void);
void	ft_putnbr(long n);
void take_fork(t_philo	*ph);
void put_fork( t_philo *ph);
void eat(t_philo *ph);
int life(t_info *info);
void	mes(t_philo *ph, char *str);
void	ft_usleep(int time_in_ms);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void *limit_food(void *data);

#endif