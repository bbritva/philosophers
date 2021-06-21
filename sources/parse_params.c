// #include "philo_one.h"
#include "../includes/philo_one.h"

int		is_int(char *line)
{
	int		i;

	i = 0;
	if (!line)
		return(0);
	while ((line[i] < 14 && line[i] > 8) || line[i] == 32)
		i++;
	while (line[i] == '+' || line[i] == '-')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	return (!line[i]);
	
}

int		check_params(char* argv[])
{
	int		i;
	if (!argv)
		return(0);
	i = 1;
	while (argv[i])
	{
		if (!is_int(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int		parse_params(int argc, char *argv[], t_data *data)
{
	if (argc < 5 || argc > 6 || !check_params(argv))
		return(0);
	data->philos_count = ft_atoi(argv[1]);
	if (data->philos_count < 2)
		return (0);
	data->death_time = ft_atoi(argv[2]);
	if (data->death_time < 2)
		return (0);
	data->eat_time = ft_atoi(argv[3]);
	if (data->eat_time < 2)
		return (0);
	data->sleep_time = ft_atoi(argv[4]);
	if (data->sleep_time < 2)
		return (0);
	if (argv[5])
	{
		data->limit_to_eat = ft_atoi(argv[5]);
		if (data->limit_to_eat < 2)
			return (0);
	}
	else
		data->limit_to_eat = 0;
	return (1);
}