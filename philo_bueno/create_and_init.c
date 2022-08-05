/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 05:07:31 by jmatute-          #+#    #+#             */
/*   Updated: 2022/08/05 19:33:36 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (pthread_mutex_init(&vars->check_dead, NULL))
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
		philo[i].time_to_die = vars->time_to_die;
		if (i < vars->n_philos - 1)
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
