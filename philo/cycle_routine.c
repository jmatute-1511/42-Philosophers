/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 04:57:17 by jmatute-          #+#    #+#             */
/*   Updated: 2022/08/08 19:12:56 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(long long time)
{
	long long	now;

	now = get_time_now();
	while (1)
	{
		if (get_time_now() - now >= time)
			break ;
		usleep(50);
	}
}

int	check_one_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->dead);
	if (philo->vars->one_died)
	{
		philo->term = true;
		pthread_mutex_unlock(&philo->vars->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->vars->dead);
	return (0);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->forks[philo->left_fork]);
	if (!check_one_died(philo))
		print_mesage(FORK_L, philo);
	if (philo->vars->n_philos == 1)
	{
		sleeping(philo->vars->time_to_die);
		print_mesage(DIED, philo);
		return (1);
	}
	pthread_mutex_lock(&philo->vars->forks[philo->right_fork]);
	if (!check_one_died(philo))
		print_mesage(FORK_R, philo);
	pthread_mutex_lock(&philo->vars->last_meal);
	philo->n_ates += 1;
	philo->last_meal = get_time_now();
	if (!check_one_died(philo))
		print_mesage(EATING, philo);
	pthread_mutex_unlock(&philo->vars->last_meal);
	sleeping(philo->vars->time_to_eat);
	pthread_mutex_unlock(&philo->vars->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->vars->forks[philo->right_fork]);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_one_died(philo))
			break ;
		if (eating(philo))
			break ;
		if (philo->n_ates == philo->vars->n_times_eat)
			break ;
		if (!check_one_died(philo))
		{	
			print_mesage(SLEEPING, philo);
			sleeping(philo->vars->time_to_sleep);
			if (!check_one_died(philo))
				print_mesage(THINKING, philo);
		}
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
		if (philo[it].id % 2 == 0)
		{
			usleep(50);
			philo[it].last_meal = get_time_now();
			if (pthread_create(&philo[it].thread, NULL, \
			&philo_routine, &philo[it]))
				return ;
		}
		else
		{
			philo[it].last_meal = get_time_now();
			if (pthread_create(&philo[it].thread, NULL, \
			&philo_routine, &philo[it]))
				return ;
		}
		it++;
	}
}
