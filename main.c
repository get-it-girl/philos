# include "philo.h"

int main(int argc, char **argv)
{
	t_info info;
	int tmp;

	if (argc < 5 || argc > 6)
		return (print_error(1));
	tmp = init(&info, argv);
	if (tmp != 0)
		return (print_error(tmp));
	if (life(&info))
		return (print_error(4));
	return (0);
}