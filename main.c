#include "philo.h"



// ЗАДАЧИИ

/*
1. обработать вариант с одним философом, чтобы не выходил за время проверки в 10 секунд !!!!!!!

2. Протестить еще раз все хорошеньшбко на бесконечность и на ограничение по еде
3. Проверить норму
4. сделать клинер с условиями когда что клинить
5. разнести все 
*/
int main(int argc, char **argv)
{
	t_info info;

	if (argc < 5 || argc > 6)
		return(print_error("Wrong amount of arguments.\n"));
	if (init(&info, argc, argv) == 1)
		return (print_error("Incorrect arguments.\n"));
	if (life(&info))
		return (1);
	pthread_mutex_lock(&info.death);
	pthread_mutex_unlock(&info.death);
	return (0);
}