#include "philo_main.h"

void	*put_message(t_philo *philo, char *message)
{
	long	delta;

	if (!philo)
		return (0);
//	pthread_mutex_lock(&philo->params->death_mutex);
//	pthread_mutex_unlock(&philo->params->death_mutex);
	delta = delta_time(philo->params->start_time);
	printf("%-8ld: Philo #%2d %s\n", delta, philo->index + 1, message);
	return (0);
}

long	delta_time(struct timeval last_eat_time)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, 0);
	return ((curr_time.tv_sec - last_eat_time.tv_sec) * 1000 + \
		(curr_time.tv_usec - last_eat_time.tv_usec) / 1000);
}

int	delay(long sleep_time)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	while (delta_time(start_time) < sleep_time)
		usleep(10);
	return (0);
}

static int	ft_is_num(char c)
{
	return ((c >= '0') && (c <= '9'));
}

int	ft_atoi(char *str)
{
	int			sign;
	long long	r;

	sign = 1;
	r = 0;
	while (((*str >= 9) && (*str <= 13)) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (ft_is_num(*str) && (r >= -2147483648) && (r < 2147483648))
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	r = r * sign;
	if (r < -2147483648)
		r = 0;
	if (r > 2147483647)
		r = -1;
	return (r);
}
