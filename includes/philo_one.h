#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>



typedef struct			s_line {
	char			*main_line;
	char			*curr_line;
	char			*tmp_line;
	int 			hist_pos;
	int 			hist_len;
	size_t			pos;
}						t_line;

int			history_len(char **history);

#endif