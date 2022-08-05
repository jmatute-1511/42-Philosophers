/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 04:57:17 by jmatute-          #+#    #+#             */
/*   Updated: 2022/08/05 19:33:52 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mesage(char *msg, t_philo *philo, int unlock)
{
	long long	now;
	long long	first_time;

	pthread_mutex_lock(&philo->vars->print);
	if (unlock < 0)
		return ;
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
	if (unlock == 1)
		pthread_mutex_unlock(&philo->vars->print);
}

void	sleeping(t_philo *philo, long long time)
{
	long long	now;

	now = get_time_now();
	while (1)
	{
		pthread_mutex_lock(&philo->vars->dead);
		if (philo->vars->one_died)
			break ;
		pthread_mutex_unlock(&philo->vars->dead);
		if (get_time_now() - now >= time)
			break ;
		usleep(50);
	}
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->forks[philo->left_fork]);
	print_mesage(FORK_L, philo, 1);
	if (philo->vars->n_philos == 1)
		return (1);
	pthread_mutex_lock(&philo->vars->forks[philo->right_fork]);
	print_mesage(FORK_R, philo, 1);
	pthread_mutex_lock(&philo->vars->last_meal);
	philo->n_ates += 1;
	print_mesage(EATING, philo, 1);
	philo->last_meal = get_time_now();
	pthread_mutex_unlock(&philo->vars->last_meal);
	sleeping(philo, philo->vars->time_to_eat);
	pthread_mutex_unlock(&philo->vars->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->vars->forks[philo->right_fork]);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->vars->dead);
		if (philo->vars->one_died || philo->vars->all_eaten)
			break ;
		pthread_mutex_unlock(&philo->vars->dead);
		if (eating(philo))
			break ;
		if (!philo->vars->all_eaten)
		{
			print_mesage(SLEEPING, philo, 1);
			sleeping(philo, philo->vars->time_to_sleep);
			if (!philo->vars->all_eaten)
				print_mesage(THINKING, philo, 1);
		}
		if (philo->n_ates == philo->vars->n_times_eat)
			break ;
	}
	return (NULL);
}

void	cycle_routine(t_philo **philos, t_philo_vars *vars)
{
	int		it;
	t_philo	*philo;

	it = 0;
	philo = *philos;
	vars->first_time = get_time_now();
	while (it < vars->n_philos)
	{
		philo[it].last_meal = get_time_now();
		if (pthread_create(&philo[it].thread, NULL, &philo_routine, &philo[it]))
			return ;
		it++;
	}
	kill_threads(philos, vars);
}
