#include "philo_main.h"

int get_forks(t_philo *me)
{
	if (me->index % 2)
	{
		pthread_mutex_lock(me->right_fork);
		put_message(me, TAKE_RIGHT);
		pthread_mutex_lock(me->left_fork);
		put_message(me, TAKE_LEFT);
	}
	else
	{
		pthread_mutex_lock(me->left_fork);
		put_message(me, TAKE_LEFT);
		pthread_mutex_lock(me->right_fork);
		put_message(me, TAKE_RIGHT);
	}
	return (0);
}

int put_forks(t_philo *me)
{
	pthread_mutex_unlock(me->right_fork);
	put_message(me, PUT_RIGHT);
	pthread_mutex_unlock(me->left_fork);
	put_message(me, PUT_LEFT);
	return (0);
}

void	*philosopher(void *data)
{
	t_philo 		*me;
	int     		eat_count;

	eat_count = 0;
	me = (t_philo *)data;
	gettimeofday(&me->last_eat_time, NULL);
	printf("Philo #%d: i'm alive\n", me->index);
	while (!me->eat_count || eat_count < me->eat_count)
	{
		get_forks(me);
		put_message(me, EAT);
		delay(me->params->eat_time);
		put_forks(me);
		gettimeofday(&me->last_eat_time, NULL);
		put_message(me, SLEEP);
		eat_count++;
		delay(me->params->sleep_time);
		put_message(me, THINK);
	}
	me->params->flag = me->params->flag & ~(IS_ALIVE);
	return (NULL);
}
