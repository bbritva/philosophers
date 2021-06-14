// #include "philo_one.h"
#include "../includes/philo_one.h"

int show_data(t_data *data)
{
	printf("philos count = %d\n", data->philos_count);
	printf("death time = %d\n", data->death_time);
	printf("eat time = %d\n", data->eat_time);
	printf("sleep time = %d\n", data->sleep_time);
	printf("eat limit = %d\n", data->limit_to_eat);
	return(0);
}

int		do_philos(t_data *data)
{
	show_data(data);
	printf("hi from philos\n");
	return(0);
}