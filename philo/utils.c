/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 21:40:16 by jmatute-          #+#    #+#             */
/*   Updated: 2022/08/02 21:40:23 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

void	bucle_atoi(long *count, long *sign, const char *str, int *neg)
{
	while ((str[(*count)] == '-' || str[(*count)] == '+'))
	{
		if (str[(*count)] == '-')
			(*neg) = -1;
		(*sign) += 1;
		(*count) += 1;
	}
}

int	ft_atoi(const char *str)
{
	long	count;
	long	save;
	long	sign;
	int		neg;

	count = 0;
	save = 0;
	sign = 0;
	neg = 1;
	while ((str[count] >= 9 && str[count] <= 13) || str[count] == 32)
		count++;
	bucle_atoi(&count, &sign, str, &neg);
	while (ft_isdigit(str[count]) && sign <= 1 && save <= 21474836479)
		save = save * 10 + (str[count++] - 48);
	save = save * neg;
	if (save > 2147483647)
		return (-1);
	if (save < -2147483648)
		return (0);
	return ((int)save);
}

long long	get_time_now(void)
{
	struct timeval	time;
	long long		micro_s;

	gettimeofday(&time, NULL);
	micro_s = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (micro_s);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	count;

	count = 0;
	while ((s1[count] || s2[count]))
	{
		if (s1[count] != s2[count])
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
		count++;
	}
	return (0);
}
