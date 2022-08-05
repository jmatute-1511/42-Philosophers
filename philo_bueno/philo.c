/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:57:40 by jmatute-          #+#    #+#             */
/*   Updated: 2022/08/05 19:35:54 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_eaten(t_philo **philos)
{
	int			it;
	int			n_philos;
	int			n_eats;
	t_philo		*philo;

	it = 0;
	philo = (*philos);
	n_philos = (*philos)->vars->n_philos;
	n_eats = (*philos)->vars->n_times_eat;
	pthread_mutex_lock(&philo->vars->last_meal);
	while (n_eats > 0 && it < n_philos && philo[it].n_ates >= n_eats)
		it++;
	pthread_mutex_unlock(&philo->vars->last_meal);
	if (it == n_philos)
	{
		pthread_mutex_lock(&philo->vars->dead);
		(*philos)->vars->all_eaten = true;
		pthread_mutex_unlock(&philo->vars->dead);
		return (1);
	}
	return (0);
}

int	check_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->last_meal);
	if (get_time_now() - philo->last_meal >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->vars->dead);
		philo->vars->one_died = true;
		pthread_mutex_unlock(&philo->vars->dead);
		print_mesage(DIED, philo, 0);
		return (1);
	}
	pthread_mutex_unlock(&philo->vars->last_meal);
	return (0);
}

void	kill_threads(t_philo **philos, t_philo_vars *vars)
{
	int		it;
	int		n_philos;
	t_philo	*philo;

	it = 0;
	philo = (*philos);
	n_philos = vars->n_philos;
	while (!vars->one_died && !vars->all_eaten && vars->n_philos > 1)
	{
		if (check_died(philo))
			break ;
		if (check_all_eaten(philos))
			break ;
		usleep(50);
	}
	if (vars->one_died)
	{
		while (it < n_philos)
		{
			pthread_detach(philo[it].thread);
			it++;
		}
	}
}

int	joinner(t_philo *philo, t_philo_vars *vars)
{
	int	it;

	it = 0;
	while (it < vars->n_philos && vars->n_philos > 0)
	{
		if (pthread_join(philo[it].thread, NULL))
			return (1);
		pthread_mutex_destroy(&vars->forks[it]);
		it++;
	}
	pthread_mutex_destroy(&vars->print);
	free(vars->forks);
	free(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_vars	vars;
	t_philo			*philos;
	int				it;

	it = 0;
	if (creates_philos(argc, argv, &vars, &philos))
		return (1);
	if (init_philos(&vars, philos))
		return (1);
	cycle_routine(&philos, &vars);
	joinner(philos, &vars);
	return (0);
}
