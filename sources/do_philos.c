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

int		init_forks(pthread_mutex_t *forks, int count)
{
	while(count--)
	{
		pthread_mutex_init(&forks[count], NULL);
	}
	return (0);
}

int		do_philos(t_data *data)
{
	int			i;
	pthread_t 	killer;

	show_data(data);
	pthread_mutex_init(&data->mutex, NULL);
	data->philos = (t_philo *)ft_calloc(data->philos_count, sizeof (t_philo));
	data->forks = (pthread_mutex_t *)ft_calloc(data->philos_count,
		sizeof(pthread_mutex_t));
	if (data->forks && data->philos)
	{
		init_forks(data->forks, data->philos_count);
		data->flag = IS_ALIVE;
		i = -1;
		gettimeofday(&data->start_time, NULL);
		printf("%ld\n", delta_time(data->start_time));
		while (++i < data->philos_count)
			pthread_create(&data->philos[i].thread, NULL, philos_life,
						   (void *) data);
		pthread_create(&killer, NULL, kill_somebody, (void *) data);
		pthread_join(killer, NULL);
		i = 0;
		while (i < data->philos_count)
		{
			pthread_join(data->philos[i++].thread, NULL);
		}
		free(data->philos);
		free(data->forks);
	}
	printf("hi from philos\n");
	return(0);
}