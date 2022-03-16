
#ifndef PHILO_H
# define PHILO_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <pthread.h>
#include <sys/time.h>

struct s_info;


typedef struct s_philo
{
	int left_fork;
	int right_fork;
	time_t time_live;
	int count_eat;
	int index;
	int eating;
	struct s_info *info;
	pthread_mutex_t busy;
	pthread_mutex_t must_eat;
}	t_philo;

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
	pthread_mutex_t mes;
}	t_info;



int print_error(char *str);
int	init_info(t_info *info, int argc, char **argv);
int	ft_atoi(const char *str);
void print_mes(t_philo *ph, char *str);
int living(t_info *info);
void take_f(t_philo *ph);
void put_f(t_philo *ph);
void eat(t_philo *ph);
void print_mes(t_philo *ph, char *str);
long	timing(void);
void	ft_putnbr(long n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
