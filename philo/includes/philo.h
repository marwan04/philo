/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:56:37 by malrifai          #+#    #+#             */
/*   Updated: 2025/01/23 20:32:06 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_data;

typedef struct s_philosopher
{
	int				id;
	int				x_ate;
	int				left_fork_id;
	int				right_fork_id;
	long long		t_last_meal;
	struct s_data	*data;
	pthread_t		thread_id;
	pthread_mutex_t	meal_mutex;

}					t_philosopher;

typedef struct s_data
{
	int				nb_philo;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				dieded;
	int				all_ate;
	long long		first_timestamp;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	writing;
	pthread_mutex_t	dieded_mutex;
	pthread_mutex_t	all_ate_mutex;
	t_philosopher	philosophers[250];
}					t_data;

int					write_error(char *str);
int					error_manager(int error);
int					init_all(t_data *data, char **argv);
int					ft_atoi(const char *str);
int					check_dead(t_philosopher *philo);
int					check_eat(t_philosopher *philo);
int					check_philo(t_philosopher *philo);
int					ft_strcmp(char *s1, char *s2);
long long			timestamp(void);
long long			time_diff(long long past, long long pres);
void				smart_sleep(long long time, t_data *data);
void				validate_print(t_data *data, int id, char *string);
int					simulater(t_data *data);
void				exit_launcher(t_data *data, t_philosopher *philos);

#endif
