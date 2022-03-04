#include<philo.h>

int print_error(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (1);
}

// не забыть почистить выделенное место под структуру

int main(int argc, char **argv)
{
	t_info info;
	
	if (init_info(&info, argc, argv) == 1)
		return (1);
	if (living(&info))
		return (1);
}