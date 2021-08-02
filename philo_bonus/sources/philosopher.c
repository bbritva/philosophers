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
	philo->flag = (char) (philo->flag | ~(IS_FULL));
	printf("%-8ld:%s", delta_time(philo->params->start_time), ALL_FULL);
	return (0);
}

int	get_forks(t_philo *me)
{
	sem_wait(me->params->forks);
	put_message(me, TAKE_FORK);
	sem_wait(me->params->forks);
	gettimeofday(&me->last_eat_time, NULL);
	put_message(me, TAKE_FORK);
	return (0);
}

int	put_forks(t_philo *me)
{
	put_message(me, PUT_FORK);
	sem_post(me->params->forks);
	put_message(me, PUT_FORK);
	sem_post(me->params->forks);
	return (0);
}

int	eat(t_philo *me, int *eat_count)
{
	get_forks(me);
	put_message(me, EAT);
	delay(me->params->eat_time);
	put_forks(me);
	(*eat_count)++;
	return (0);
}

int	prepare_philo(t_philo *me, int *eat_count)
{
	usleep(100 * (me->index));
	*eat_count = 0;
	gettimeofday(&me->last_eat_time, NULL);
	me->flag = (char) (me->flag | STARTED);
	return (0);
}

void	*live_cycle(void *data)
{
	t_philo		*me;
	int			eat_count;

	if (data)
	{
		me = (t_philo *) data;
		prepare_philo(me, &eat_count);
		while (me->flag & STARTED && !(me->flag & IS_FULL))
		{
			if (me->flag & STARTED)
				eat(me, &eat_count);
			if (me->params->limit_to_eat &&
				eat_count >= me->params->limit_to_eat)
				break;
			if (me->flag & STARTED)
				put_message(me, SLEEP);
			delay(me->params->sleep_time);
			if (me->flag & STARTED)
				put_message(me, THINK);
		}
		put_message(me, FULL);
		me->flag = (char)(me->flag | IS_FULL);
		me->flag = (char)(me->flag & ~(STARTED));
		me->params->full_cnt++;
	}
	return (NULL);
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
	pthread_create(&live, NULL, live_cycle, data);
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
