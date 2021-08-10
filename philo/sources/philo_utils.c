#include "philo_main.h"

void	*put_message(t_philo *philo, char *message)
{
	long	delta;

	if (!philo)
		return (0);
	delta = delta_time(philo->params->start_time);
	pthread_mutex_lock(&philo->params->print_mutex);
	printf("%-8ld: Philo #%2d %s\n", delta, philo->index + 1, message);
	pthread_mutex_unlock(&philo->params->print_mutex);
	return (0);
}

long	delta_time(struct timeval last_eat_time)
{
	struct timeval	curr_time;
	long			curr;
	long			last;
	long			delta;

	gettimeofday(&curr_time, 0);
	curr = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	last = last_eat_time.tv_sec * 1000 + last_eat_time.tv_usec / 1000;
	delta = curr - last;
	return (delta);
}

int	delay(long sleep_time)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	while (delta_time(start_time) <= sleep_time)
		usleep(500);
	return (0);
}
