#include "philo_main.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (data)
	{
		if (parse_params(argc, argv, data))
			start_philos(data);
		else
			printf("params error\n");
		free(data);
	}
	return (0);
}
