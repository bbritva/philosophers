#ifndef PHILO_MAIN_H
# define PHILO_MAIN_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define IS_FULL 2
# define STARTED 1
# define TAKE_FORK "has taken fork"
# define PUT_FORK "has put fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FULL "is full"
# define DEAD "\x1B[36mis dead\x1B[0m"
# define ALL_FULL "\x1B[36m all philos is full\x1B[0m\n"

typedef struct s_data {
	int					philos_cnt;
	long				death_time;
	int					eat_time;
	int					sleep_time;
	int					limit_to_eat;
	int					full_cnt;
	int					started_count;
	struct timeval		start_time;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		odd_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		*forks;

}						t_data;

typedef struct s_philo {
	pthread_t			thread;
	struct timeval		last_eat_time;
	int					index;
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
void	*put_message(t_philo *philo, char *message);
int		delay(long sleep_time);
int		ft_atoi(char *str);
void	*ft_calloc(size_t count, size_t size);

#endif