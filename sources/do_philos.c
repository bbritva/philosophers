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
	int		i;
	

	show_data(data);
	data->philos = (t_philo *)ft_calloc(data->philos_count, sizeof (t_philo));
	data->forks = (pthread_mutex_t *)ft_calloc(data->philos_count,
		sizeof(pthread_mutex_t));
	if (data->forks && data->philos)
	{
		data->flag = IS_ALIVE;
		i = -1;
		while (++i < data->philos_count)
			pthread_create(&data->philos[i].thread, NULL, philos_life,
						   (void *) data);
		usleep(1000);
		kill_somebody(data);
		i = 0;
		while (i < data->philos_count)
			pthread_join(data->philos[i++].thread, NULL);
		free(data->philos);
		free(data->forks);
	}
	printf("hi from philos\n");
	return(0);
}