#include "philo_main.h"

void	*death(t_philo *philo, pthread_t *live)
{
	long	delta;

	sem_wait(philo->params->print_sem);
	pthread_detach(*live);
	delta = delta_time(philo->params->start_time);
	philo->flag = 0;
	printf("%-8ld: Philo #%2d %s\n", delta, philo->index + 1, DEAD);
	return (0);
}

void	*full(t_philo *philo, pthread_t *live)
{
	sem_wait(philo->params->print_sem);
	pthread_detach(*live);
	philo->flag = (char)(philo->flag | ~(IS_FULL));
	printf("%-8ld:%s", delta_time(philo->params->start_time), ALL_FULL);
	return (0);
}

void	*philosopher(void *data)
{
	pthread_t	live;
	t_philo		*me;
	long		delta;
	long		death_time;

	if (!data)
		return (NULL);
	me = (t_philo *)data;
	death_time = me->params->death_time;
	pthread_create(&live, NULL, life_cycle, data);
	while (1)
	{
		delay(10);
		if (me->params->full_cnt == me->params->philos_cnt)
			return (full(me, &live));
		delta = delta_time(me->last_eat_time);
		if (me->flag & STARTED && \
			delta > death_time)
			return (death(me, &live));
	}
}
