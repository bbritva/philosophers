#include "philo_main.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n > 0)
	{
		*str = '\0';
		str++;
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (result)
		ft_bzero(result, count * size);
	return (result);
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
	return ((int)r);
}
