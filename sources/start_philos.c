#include "philo_main.h"

int	show_data(t_data *data)
{
	printf("philos i = %d\n", data->philos_cnt);
	printf("death time = %d\n", data->death_time);
	printf("eat time = %d\n", data->eat_time);
	printf("sleep time = %d\n", data->sleep_time);
	printf("eat limit = %d\n", data->limit_to_eat);
	return (0);
}

int	init_forks(t_data *data, t_philo ***philos)
{
	int	count;

	count = data->philos_cnt;
	while (count--)
	{
		pthread_mutex_init(&data->forks[count], NULL);
		printf("fork #%d inited\n", count);
	}
	while (++count < data->philos_cnt)
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
			(*philos)[count]->right_fork = &data->forks[data->philos_cnt - 1];
			printf("fork %d in philo's %d right hand\n",
				data->philos_cnt - 1, count);
		}
	}
	return (0);
}

int	init_philos(t_data *data, t_philo ***philos)
{
	int	i;

	show_data(data);
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	*philos = (t_philo **)ft_calloc(data->philos_cnt, sizeof (t_philo *));
	data->forks = (pthread_mutex_t *)ft_calloc(data->philos_cnt,
			sizeof(pthread_mutex_t));
	if (data->forks && *philos)
	{
		i = -1;
		while (++i < data->philos_cnt)
		{
			(*philos)[i] = (t_philo *) ft_calloc(1, sizeof (t_philo));
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

int	start_philos(t_data *data)
{
	int		i;
	t_philo	**philos;

	if (!init_philos(data, &philos))
		return (0);
	i = -1;
	gettimeofday(&data->start_time, NULL);
	while (++i < data->philos_cnt)
		pthread_create(&philos[i]->thread, NULL, philosopher,
			(void *)philos[i]);
	i = -1;
	killer(philos);
	while (++i < data->philos_cnt)
		pthread_detach(philos[i]->thread);
	free(data->forks);
	free(philos);
	return (1);
}
