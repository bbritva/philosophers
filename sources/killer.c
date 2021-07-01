#include "philo_one.h"

void	*kill_somebody(void *data)
{
	t_data	*params;
	int		i;
	struct timeval t;

	if (data)
	{
		params = (t_data *)data;
		i = 0;
		while(params->flag & IS_ALIVE)
		{
			while (i < params->philos_count)
			{
				gettimeofday(&t, NULL);
				if ((t.tv_usec - params->last_eat_time[i].tv_usec) > params->death_time * 1000 * K)
				{
					//					params->flag = params->flag & ~(IS_ALIVE);
					printf("Philo #%d has been shot\n", i);
					params->flag = 0;
				}
				i++;
			}
			if (!(params->flag & IS_ALIVE))
				break ;
		}
	}
	return (0);
}
