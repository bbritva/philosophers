#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/libft.h"

# define SLEEP_TIME 10000
# define KOEF 1000
# define IS_ALIVE 1

typedef struct		    s_data {
	int				    philos_count;
	int				    death_time;
	int				    eat_time;
	int				    sleep_time;
	int				    limit_to_eat;
	int				    index;
	int	    			flag;
	struct timeval		start_time;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*forks;

}					t_data;

typedef struct			s_philo {
	pthread_t 			thread;
	struct timeval		last_eat_time;
	int 				eat_count;
	int				    index;
	t_data				*params;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;

}						t_philo;

int		start_philos(t_data *data);
int		parse_params(int argc, char *argv[], t_data *data);
void	*philos_lifecycle(void *data);
void	*philosopher(void *data);
long	delta_time(struct timeval last_eat_time);

#endif