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

int		init_forks(t_data *data)
{
	int count;

	count = data->philos_count;
	while(count--)
	{
		pthread_mutex_init(&data->forks[count], NULL);
		printf("fork #%d inited\n", count);
	}
	while (++count < data->philos_count)
	{
		data->philos[count].left_fork = &data->forks[count];
		printf("fork %d in philo's %d left hand\n", count, count);
		if (count)
		{
			data->philos[count].right_fork = &data->forks[count - 1];
			printf("fork %d in philo's %d right hand\n", count - 1, count);
		}
		else
		{
			data->philos[count].right_fork = &data->forks[data->philos_count - 1];
			printf("fork %d in philo's %d right hand\n", data->philos_count - 1, count);
		}
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
		init_forks(data);
		data->flag = IS_ALIVE;
		i = -1;
		gettimeofday(&data->start_time, NULL);
		while (++i < data->philos_count)
			pthread_create(&data->philos[i].thread, NULL, philos_life,
						   (void *) data);
		pthread_create(&killer, NULL, kill_somebody, (void *) data);
		i = 0;
		while (i < data->philos_count)
		{
			pthread_join(data->philos[i++].thread, NULL);
		}
		pthread_join(killer, NULL);
//		free(data->forks);
//		free(data->philos);
	}
	printf("hi from philos\n");
	return(0);
}