#include "philo_main.h"


int	get_forks(t_philo *me, pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	put_message(me, TAKE_FORK);
	pthread_mutex_lock(second);
	pthread_mutex_lock(&(me->death_mutex));
	gettimeofday(&me->last_eat_time, NULL);
	put_message(me, TAKE_FORK);
	return (0);
}

int	put_forks(t_philo *me)
{
	pthread_mutex_unlock(&(me->death_mutex));
	pthread_mutex_unlock(me->right_fork);
	put_message(me, PUT_FORK);
	pthread_mutex_unlock(me->left_fork);
	put_message(me, PUT_FORK);
	return (0);
}

int	eat(t_philo *me, int *eat_count)
{
	get_forks(me, me->right_fork, me->left_fork);
	put_message(me, EAT);
	delay(me->params->eat_time);
	put_forks(me);
	(*eat_count)++;
	return (0);
}

void	*life_cycle(void *data)
{
	t_philo		*me;
	int			eat_count;

	if (!data)
		return (0);
	me = (t_philo *)data;
	while (me->flag & STARTED)
	{
		eat(me, &eat_count);
		if (me->params->limit_to_eat && eat_count >= me->params->limit_to_eat)
			break ;
		put_message(me, SLEEP);
		delay(me->params->sleep_time);
		put_message(me, THINK);
	}
	put_message(me, FULL);
	me->params->full_cnt++;
	if (me->params->full_cnt == me->params->philos_cnt)
		me->params->flag = 0;
	return (NULL);
}
