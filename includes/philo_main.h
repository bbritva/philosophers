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
# define IS_FULL 2
# define IS_STARTED 1
# define TAKE_RIGHT "has taken a right fork"
# define TAKE_LEFT "has taken a left fork"
# define PUT_RIGHT "has put a right fork"
# define PUT_LEFT "has put a left fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FULL "is full"
# define PUT_LEFT "has put a left fork"
# define DEAD "\x1B[36mis dead-------------------------------------\x1B[0m"
# define ALL_FULL "\x1B[36m all philos is full-----------------------\x1B[0m\n"


typedef struct		    s_data {
	int				    philos_count;
	int				    death_time;
	int				    eat_time;
	int				    sleep_time;
	int				    limit_to_eat;
	int	    			full_count;
	struct timeval		start_time;
	pthread_mutex_t		mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		*forks;

}					t_data;

typedef struct			s_philo {
	pthread_t 			thread;
	struct timeval		last_eat_time;
	int 				eat_count;
	int				    index;
	char				flag;
	t_data				*params;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;

}						t_philo;

int		start_philos(t_data *data);
int		parse_params(int argc, char *argv[], t_data *data);
void	*killer(void *data);
void	*philosopher(void *data);
long	delta_time(struct timeval last_eat_time);
int		put_message(t_philo *philo, char *message);
int 	delay(long sleep_time);


#endif