/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 05:07:31 by jmatute-          #+#    #+#             */
/*   Updated: 2022/08/08 19:12:40 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mesage(char *msg, t_philo *philo)
{
	long long	now;
	long long	first_time;

	pthread_mutex_lock(&philo->vars->print);
	now = get_time_now();
	first_time = philo->vars->first_time;
	if (!philo->vars->dead_philo)
		printf(MAG"[%llims] philo %i ", now - first_time, philo->id);
	if (ft_strcmp(msg, FORK_L) == 0 || ft_strcmp(msg, FORK_R) == 0)
		printf(BYEL"%s\n", msg);
	else if (ft_strcmp(msg, SLEEPING) == 0)
		printf(BBLU"%s\n", msg);
	else if (ft_strcmp(msg, THINKING) == 0)
		printf(YEL"%s\n", msg);
	else if (ft_strcmp(msg, EATING) == 0)
		printf(BGRN"%s\n", msg);
	else if (ft_strcmp(msg, DIED) == 0)
		printf(ROJO_T"%s\n", msg);
	pthread_mutex_unlock(&philo->vars->print);
}

static int	error_args(char **argv)
{
	int	it;

	it = 1;
	while (argv[it])
	{
		if (ft_atoi(argv[it]) <= 0 || (it == 1 && ft_atoi(argv[it]) > 200))
			return (1);
		it++;
	}
	return (0);
}

int	creates_philos(int argc, char **argv, t_philo_vars *vars, t_philo **philos)
{
	if (argc < 5 || argc > 6 || error_args(argv))
		return (1);
	vars->n_philos = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	vars->first_time = 0;
	vars->dead_philo = false;
	vars->all_eaten = false;
	vars->one_died = false;
	if (argv[5])
		vars->n_times_eat = ft_atoi(argv[5]);
	else
		vars->n_times_eat = -1;
	(*philos) = malloc(sizeof(t_philo) * vars->n_philos);
	if (!(*philos))
		return (write(2, "Error intializing threads", 26), 1);
	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->n_philos);
	if (!(*philos))
		return (write(2, "Error intializing threads", 26), 1);
	return (0);
}

int	init_mutex(t_philo_vars *vars)
{
	if (pthread_mutex_init(&vars->print, NULL))
		return (write(2, "Error mutex initialization", 27), 1);
	if (pthread_mutex_init(&vars->dead, NULL))
		return (write(2, "Error mutex initialization", 27), 1);
	if (pthread_mutex_init(&vars->last_meal, NULL))
		return (write(2, "Error mutex initialization", 27), 1);
	return (0);
}

int	init_philos(t_philo_vars *vars, t_philo *philo)
{
	int	i;

	if (init_mutex(vars))
		return (1);
	i = 0;
	while (i < vars->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].n_ates = 0;
		philo[i].vars = vars;
		philo[i].left_fork = i;
		philo[i].term = false;
		philo[i].time_to_die = vars->time_to_die;
		if (i < vars->n_philos)
			philo[i].right_fork = i + 1;
		else
			philo[i].right_fork = 0;
		philo[i].last_meal = 0;
		if (pthread_mutex_init(&vars->forks[i], NULL))
			return (write(2, "Error mutex initialization", 27), 1);
		i++;
	}
	return (0);
}
