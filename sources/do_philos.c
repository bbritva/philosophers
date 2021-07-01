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
	pthread_t	        *p;
	int			        i;
	

	show_data(data);
	p = (pthread_t *)ft_calloc(data->philos_count, sizeof(pthread_t));
	data->last_eat_time = (struct timeval *)ft_calloc(data->philos_count,
		sizeof(struct timeval));
	data->forks = (pthread_mutex_t *)ft_calloc(data->philos_count,
		sizeof(pthread_mutex_t));
	if (p && data->forks && data->last_eat_time)
	{
		data->flag = IS_ALIVE;
		i = 0;
		while (i < data->philos_count)
		{
			pthread_create(&p[i], NULL, born_philo, (void *)data);
			i++;
		}
//		pthread_create(&killer, NULL, kill_somebody, (void *)data);
		kill_somebody(data);
		i = 0;
		while (i < data->philos_count)
		{
			pthread_join(p[i], NULL);
			i++;
		}
		free(p);
	}
	printf("hi from philos\n");
	return(0);
}