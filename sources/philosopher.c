#include "philo_main.h"

int	get_forks(t_philo *me, pthread_mutex_t *first, pthread_mutex_t *second)
{
	while (1)
	{
		pthread_mutex_lock(first);
		if (!pthread_mutex_trylock(second))
			break ;
		else
			pthread_mutex_unlock(first);
	}
	put_message(me, TAKE_FORK);
	return (0);
}

int	put_forks(t_philo *me)
{
	pthread_mutex_unlock(me->right_fork);
	pthread_mutex_unlock(me->left_fork);
	put_message(me, PUT_FORK);
	return (0);
}

int	eat(t_philo *me, int *eat_count)
{
	pthread_mutex_lock(&me->params->death_mutex);
	pthread_mutex_unlock(&me->params->death_mutex);
	if (me->index % 2)
	{
		get_forks(me, me->left_fork, me->right_fork);
	}
	else
	{
		get_forks(me, me->right_fork, me->left_fork);
	}
	put_message(me, EAT);
	gettimeofday(&me->last_eat_time, NULL);
	delay(me->params->eat_time);
	put_forks(me);
	(*eat_count)++;
	return (0);
}

int	prepare_philo(t_philo *me, int *eat_count)
{
	*eat_count = 0;
	if (me->index == me->params->philos_cnt - 1)
		pthread_mutex_unlock(&me->params->odd_mutex);
	if (me->index % 2)
	{
		pthread_mutex_lock(&me->params->odd_mutex);
		pthread_mutex_unlock(&me->params->odd_mutex);
	}
	gettimeofday(&me->last_eat_time, NULL);
	me->flag = me->flag | STARTED;
	return (0);
}

void	*philosopher(void *data)
{
	t_philo	*me;
	int		eat_count;

	me = (t_philo *)data;
	prepare_philo(me, &eat_count);
	while (1)
	{
		eat(me, &eat_count);
		if (me->params->limit_to_eat && eat_count >= me->params->limit_to_eat)
			break ;
		put_message(me, SLEEP);
		delay(me->params->sleep_time);
		put_message(me, THINK);
	}
	put_message(me, FULL);
	me->flag = me->flag | IS_FULL;
	me->flag = me->flag & ~(STARTED);
	me->params->full_cnt++;
	return (NULL);
}
