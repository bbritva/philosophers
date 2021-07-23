#include "philo_main.h"

void	*death(t_philo *philo)
{
	long	delta;

//	pthread_mutex_lock(&philo->params->death_mutex);
//	pthread_mutex_lock(&philo->params->mutex);
	delta = delta_time(philo->params->start_time);
	philo->flag = 0;
	printf("%-8ld: Philo #%2d %s\n", delta, philo->index + 1, DEAD);
	return (0);
}

void	*full(t_philo *philo)
{
//	pthread_mutex_lock(&philo->params->death_mutex);
//	pthread_mutex_lock(&philo->params->mutex);
	philo->flag = (char) (philo->flag | ~(IS_FULL));
	printf("%-8ld:%s", delta_time(philo->params->start_time), ALL_FULL);
	return (0);
}

void	*killer(void *data)
{
	t_philo		*my_philo;
	long		delta;
	long		death_time;

	if (!data)
		return (0);
	my_philo = (t_philo *)data;
	death_time = my_philo->params->death_time;
//	delay((int)death_time * 2 / 3);
	while (1)
	{
		delay(10);
		if (my_philo->params->full_cnt == my_philo->params->philos_cnt)
			return (full(my_philo));
		delta = delta_time(my_philo->last_eat_time);
		if (my_philo->flag & STARTED && \
			delta > death_time)
		return (death(my_philo));
	}
}
