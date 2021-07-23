#include "philo_main.h"

int	get_forks(t_philo *me)
{
	int sem_value;

	gettimeofday(&me->last_eat_time, NULL);
	sem_wait(me->params->forks);
	put_message(me, TAKE_FORK);
	sem_wait(me->params->forks);
	put_message(me, TAKE_FORK);
	sem_getvalue(me->params->forks, &sem_value);
	printf("sem_value = %d\n", sem_value);
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
//	pthread_mutex_lock(&me->params->death_mutex);
//	pthread_mutex_unlock(&me->params->death_mutex);
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

void	*philosopher(void *data)
{
	t_philo		*me;
	int			eat_count;
	pthread_t	my_killer;

	me = (t_philo *)data;
	prepare_philo(me, &eat_count);
	pthread_create(&my_killer, NULL, killer, me);
	while (me->flag & STARTED && !(me->flag & IS_FULL))
	{
		if (me->flag & STARTED)
			eat(me, &eat_count);
		if (me->params->limit_to_eat && eat_count >= me->params->limit_to_eat)
			break ;
		if (me->flag & STARTED)
			put_message(me, SLEEP);
		delay(me->params->sleep_time);
		if (me->flag & STARTED)
			put_message(me, THINK);
	}
	pthread_join(my_killer, NULL);
	put_message(me, FULL);
	me->flag = me->flag | IS_FULL;
	me->flag = me->flag & ~(STARTED);
	me->params->full_cnt++;
	return (NULL);
}
