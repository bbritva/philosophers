#include "philo_main.h"

int	put_message(t_philo *philo, char *message)
{
	long delta;

	if(!philo)
		return (0);
	delta = delta_time(philo->params->start_time);
	printf("%-8ld: Philo #%2d %s\n", delta, philo->index + 1, message);
	return (1);
}

long delta_time(struct timeval last_eat_time)
{
	struct timeval curr_time;

	gettimeofday(&curr_time, 0);
	return ((curr_time.tv_sec - last_eat_time.tv_sec) * 1000 +
			(curr_time.tv_usec - last_eat_time.tv_usec) / 1000);
}

int delay(long sleep_time)
{
	struct timeval start_time;

	gettimeofday(&start_time, NULL);
	while (delta_time(start_time) < sleep_time);
	return (0);
}
