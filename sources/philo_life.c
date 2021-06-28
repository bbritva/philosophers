// #include "philo_one.h"
#include "../includes/philo_one.h"

void	*born_philo(void *data)
{
	t_data *params;

	params = (t_data *)data;
	// params->index++;
	printf("Philo #%d: i'm alive\n", params->index);
	usleep(SLEEP_TIME);
	printf("Philo #%d: live is over=(\n", params->index);
	return(NULL);
}