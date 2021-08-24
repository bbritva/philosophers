#include "philo_main.h"

int	prepare_philo(t_philo *me, int *eat_count)
{
	*eat_count = 0;
	if (me->index % 2)
	{
		pthread_mutex_lock(&me->params->odd_mutex);
		pthread_mutex_unlock(&(me->params->odd_mutex));
	}
	delay(me->index);
	gettimeofday(&me->last_eat_time, NULL);
	me->flag = me->flag | STARTED;
	me->params->started_count++;
	if (me->params->started_count >= me->params->philos_cnt / 2 + \
		(me->params->philos_cnt % 2))
		pthread_mutex_unlock(&(me->params->odd_mutex));
	return (0);
}

void	*death(t_philo *philo)
{
	long	delta;

	philo->params->flag = 0;
	pthread_mutex_lock(&philo->params->death_mutex);
	pthread_mutex_lock(&philo->params->print_mutex);
	delta = delta_time(philo->params->start_time);
	printf("%-8ld: Philo #%2d %s\n", delta, philo->index + 1, DEAD);
	return (0);
}

void	*philosopher(void *data)
{
	t_philo		*me;
	int			eat_count;
	pthread_t	life;
	long		delta;

	me = (t_philo *)data;
	prepare_philo(me, &eat_count);
	pthread_create(&life, NULL, life_cycle, data);
	pthread_detach(life);
	while (1)
	{
		pthread_mutex_lock(&(me->death_mutex));
		delta = delta_time(me->last_eat_time);
		if (me->flag & STARTED && delta > me->params->death_time)
			break ;
		pthread_mutex_unlock(&(me->death_mutex));
	}
	if (me->params->full_cnt)
		return (NULL);
	return (death(me));
}
