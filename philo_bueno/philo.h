/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:26:13 by jmatute-          #+#    #+#             */
/*   Updated: 2022/08/05 19:18:51 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h> 
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>

# define BBLU "\e[1;34m"
# define BGRN "\e[1;32m"
# define ROJO_T     "\x1b[31m"
# define YEL "\e[0;33m"
# define BYEL "\e[1;33m"
# define MAG "\e[0;35m"
# define EAT_X_TIMES 4
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define FORK_L "has taken left fork"
# define FORK_R "has taken right fork"
# define DIED "died"
# define LEFT_FORK 0
# define RIGHT_FORK 1

typedef struct s_philo_vars
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_eat;
	int				n_philos;
	long long		first_time;
	bool			dead_philo;
	bool			all_eaten;
	bool			one_died;
	pthread_mutex_t	print;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	check_dead;
	pthread_mutex_t	dead;
	pthread_mutex_t	*forks;
}				t_philo_vars;

typedef struct s_philo
{
	int				id;
	int				n_ates;
	t_philo_vars	*vars;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	int				time_to_die;
	pthread_t		thread;	
}				t_philo;

int			creates_philos(int argc, char **argv, t_philo_vars *vars, \
			t_philo **philos);
int			init_philos(t_philo_vars *vars, t_philo *philo);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *str);
int			check_died(t_philo *philo);
void		print_mesage(char *msg, t_philo *philo, int unlock	);
int			check_all_eaten(t_philo **philos);
void		cycle_routine(t_philo **philo, t_philo_vars *vars);
long long	get_time_now(void);
void		kill_threads(t_philo **philos, t_philo_vars *vars);
#endif