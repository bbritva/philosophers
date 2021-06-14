// #include "philo_one.h"
#include "../includes/philo_one.h"

int main(int argc, char *argv[])
{
	t_data *data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (data)
	{
		if (parse_params(argc, argv))
			do_philos(data);
		else
			printf("params error\n");

		free(data);
	}
	return (0);
}