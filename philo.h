
#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

struct s_info;

typedef struct s_philos
{
	int				index;
	int				nbr_meals;
	int				left_fork;
	int				right_fork;
	long long		last_ate;
	struct s_info	*info;
	pthread_t		ph_thread;
}	t_philos;

typedef struct	s_info
{
	int nbr_ph;
	int to_die;
	int to_eat;
	int to_sleep;
	int nbr_meals;
	int dead;
	int finished;
	long long start_time;
	pthread_mutex_t	busy;
	pthread_mutex_t forks[200];
	pthread_mutex_t mes;
	t_philos philos[200];
}	t_info;

int	init(t_info *info, char **argv);


int print_error(int flag);
int	ft_atoi(char *str);
long	get_time(void);
void	ft_usleep(int time_in_ms, t_info *info);
void messege(t_philos *ph, char *str);

int life(t_info *info);


#endif

