#include "philo_main.h"

int	init_forks(t_data *data, t_philo ***philos)
{
	int	count;

	count = data->philos_cnt;
	while (count--)
	{
		pthread_mutex_init(&data->forks[count], NULL);
	}
	while (++count < data->philos_cnt)
	{
		(*philos)[count]->left_fork = &data->forks[count];
		if (count)
			(*philos)[count]->right_fork = &data->forks[count - 1];
		else
			(*philos)[count]->right_fork = &data->forks[data->philos_cnt - 1];
	}
	return (0);
}

int	init_philos(t_data *data, t_philo ***philos)
{
	int	i;

	data->started_count = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->odd_mutex, NULL);
	*philos = (t_philo **)ft_calloc(data->philos_cnt, sizeof (t_philo *));
	data->forks = (pthread_mutex_t *)ft_calloc(data->philos_cnt,
			sizeof(pthread_mutex_t));
	if (data->forks && *philos)
	{
		i = -1;
		while (++i < data->philos_cnt)
		{
			(*philos)[i] = (t_philo *) ft_calloc(1, sizeof (t_philo));
			pthread_mutex_init(&(*philos)[i]->death_mutex, NULL);
			if ((*philos)[i])
			{
				(*philos)[i]->index = i;
				(*philos)[i]->params = data;
			}
		}
		init_forks(data, philos);
		return (1);
	}
	return (0);
}

int	free_philos(t_philo **philos)
{
	int	i;

	if (philos && *philos)
	{
		i = philos[0]->params->philos_cnt;
		while (i)
			free(philos[--i]);
		free(philos);
		return (1);
	}
	return (0);
}

int	start_philos(t_data *data)
{
	int		i;
	t_philo	**philos;

	if (!init_philos(data, &philos))
		return (0);
	i = -1;
	gettimeofday(&data->start_time, NULL);
	pthread_mutex_lock(&data->odd_mutex);
	while (++i < data->philos_cnt)
		pthread_create(&philos[i]->thread, NULL, philosopher,
			(void *)philos[i]);
	i = -1;
	while (++i < data->philos_cnt)
		pthread_join(philos[i]->thread, NULL);
	if (data->full_cnt == data->limit_to_eat)
		printf("%-8ld:%s", delta_time(data->start_time), ALL_FULL);
	free_philos(philos);
	return (1);
}
