// #include "philo_one.h"
#include "../includes/philo_main.h"

int get_forks(t_philo *me)
{
	pthread_mutex_lock(me->right_fork);
	pthread_mutex_lock(me->left_fork);
	printf("Philo #%d: GET forks\n", me->index);
    return (0);
}

int put_forks(t_philo *me)
{
	pthread_mutex_unlock(me->right_fork);
	pthread_mutex_unlock(me->left_fork);
	printf("Philo #%d: PUT forks\n", me->index);
    return (0);
}

void	*philos_lifecycle(void *data)
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
        usleep(me->params->eat_time * KOEF);
		gettimeofday(&me->last_eat_time, NULL);
		put_forks(me);
		eat_count++;
        usleep(me->params->sleep_time * KOEF);
    }
	me->params->flag = me->params->flag & ~(IS_ALIVE);
	return (NULL);
}