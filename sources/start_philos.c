// #include "philo_one.h"
#include "../includes/philo_main.h"

int show_data(t_data *data)
{
	printf("philos i = %d\n", data->philos_count);
	printf("death time = %d\n", data->death_time);
	printf("eat time = %d\n", data->eat_time);
	printf("sleep time = %d\n", data->sleep_time);
	printf("eat limit = %d\n", data->limit_to_eat);
	return(0);
}

int		init_forks(t_data *data, t_philo ***philos)
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
		(*philos)[count]->left_fork = &data->forks[count];
		printf("fork %d in philo's %d left hand\n", count, count);
		if (count)
		{
			(*philos)[count]->right_fork = &data->forks[count - 1];
			printf("fork %d in philo's %d right hand\n", count - 1, count);
		}
		else
		{
			(*philos)[count]->right_fork = &data->forks[data->philos_count - 1];
			printf("fork %d in philo's %d right hand\n", data->philos_count - 1, count);
		}
	}
	return (0);
}

int 	init_philos(t_data *data, t_philo ***philos)
{
	int i;

	show_data(data);
	pthread_mutex_init(&data->mutex, NULL);
	*philos = (t_philo **)ft_calloc(data->philos_count, sizeof (t_philo *));
	data->forks = (pthread_mutex_t *)ft_calloc(data->philos_count,
		sizeof(pthread_mutex_t));
	if (data->forks && *philos)
	{
		i = -1;
		while (++i < data->philos_count)
		{
			(*philos)[i] = (t_philo *) ft_calloc(1, sizeof (t_philo));
			if ((*philos)[i])
			{
				(*philos)[i]->index = i;
				(*philos)[i]->params = data;
			}
		}
		init_forks(data, philos);
		data->flag = IS_ALIVE;
		return (1);
	}
	return (0);
}


int		start_philos(t_data *data)
{
	int			i;
	t_philo		**philos;

	if (!init_philos(data, &philos))
		return (0);
	i = -1;
	gettimeofday(&data->start_time, NULL);
	while (++i < data->philos_count)
		pthread_create(&philos[i]->thread, NULL, philosopher,
					   (void *)philos[i]);
	i = -1;
	while (++i < data->philos_count)
		pthread_join(philos[i]->thread, NULL);
//	free(data->forks);
//	free(data->philos);
	return(1);
}