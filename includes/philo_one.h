#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "../libft/libft.h"



typedef struct		s_data {
	int				philos_count;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				limit_to_eat;
}					t_data;

int		do_philos(t_data *data);
int		parse_params(int argc, char *argv[], t_data *data);

#endif