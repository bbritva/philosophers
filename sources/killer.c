#include "philo_one.h"

void	*killer(void *data)
{
	t_data	*params;
	int		i;
	
	if (data)
	{
		params = (t_data *)data;
		i = 0;
		while (i < params->philos_count)
		{
			if (time(0) - params->last_eat_time[i] > params->death_time)
				
		}
	}
}
