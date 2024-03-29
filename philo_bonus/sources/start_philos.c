#include "philo_main.h"

int	init_philos(t_data *data, t_philo ***philos)
{
	int	i;

	data->started_count = 0;
	data->pids = (int *)ft_calloc(data->philos_cnt, sizeof (int));
	*philos = (t_philo **)ft_calloc(data->philos_cnt, sizeof (t_philo *));
	if (data->pids && *philos)
	{
		sem_unlink("forks");
		sem_unlink("print");
		data->forks = sem_open("forks", O_CREAT, 0666, data->philos_cnt);
		data->print_sem = sem_open("print", O_CREAT, 0666, 1);
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
	while (++i < data->philos_cnt)
	{
		data->pids[i] = fork();
		if (!data->pids[i])
		{
			philosopher((void *) philos[i]);
			break ;
		}
	}
	waitpid(-1, NULL, 0);
	return (1);
}
