// #include "philo_one.h"
#include "../includes/philo_one.h"

void	*born_philo(void *data)
{
	t_data  *params;
	int     my_index;

	params = (t_data *)data;
	pthread_mutex_lock(&params->mutex);
	my_index = ++params->index;
    pthread_mutex_unlock(&params->mutex);
	printf("Philo #%d: i'm alive\n", my_index);
	usleep(params->sleep_time);
	printf("Philo #%d: live is over=(\n", my_index);
	return(NULL);
}