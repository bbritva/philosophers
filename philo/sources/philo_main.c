#include "philo_main.h"

int	mutex_destroyer(t_data *data)
{
	int	i;

	if (data)
	{
		pthread_mutex_destroy(&(data->print_mutex));
		pthread_mutex_destroy(&(data->odd_mutex));
		i = -1;
		while (++i > data->philos_cnt)
			pthread_mutex_destroy(&(data->forks[i]));
		free(data->forks);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (data)
	{
		if (parse_params(argc, argv, data))
		{
			start_philos(data);
			mutex_destroyer(data);
		}
		else
			printf("params error\n");
		free(data);
	}
	return (0);
}
