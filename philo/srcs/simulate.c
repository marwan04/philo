/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:30:13 by malrifai          #+#    #+#             */
/*   Updated: 2025/01/25 23:21:51 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eats(t_philosopher *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->left_fork_id < philo->right_fork_id)
	{
		pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
		pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
	}
	else
	{
		pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
		pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
	}
	validate_print(data, philo->id, "has taken a fork");
	validate_print(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->meal_mutex));
	validate_print(data, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(philo->meal_mutex));
	smart_sleep(data->time_eat, data);
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->x_ate++;
	pthread_mutex_unlock(&(philo->meal_mutex));
	pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
}

void	*p_thread(void *void_philosopher)
{
	t_philosopher	*philo;
	t_data			*data;

	philo = (t_philosopher *)void_philosopher;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	while (1)
	{
		if (check_dead(philo) == 1)
			break ;
		if (check_eat(philo) == 1)
			break ;
		if (check_philo(philo) == 1)
			break ;
		philo_eats(philo);
		validate_print(data, philo->id, "is sleeping");
		smart_sleep(data->time_sleep, data);
		validate_print(data, philo->id, "is thinking");
	}
	return (NULL);
}

void	exit_launcher(t_data *data, t_philosopher *philos)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutex_destroy(&(philos[i].meal_mutex));
	}
	pthread_mutex_destroy(&(data->writing));
	pthread_mutex_destroy(&(data->dieded_mutex));
	pthread_mutex_destroy(&(data->all_ate_mutex));
}

void	death_checker(t_data *data, t_philosopher *philos)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&(philos[i].meal_mutex));
			if (time_diff(philos[i].t_last_meal,
					timestamp()) > data->time_death)
			{
				pthread_mutex_unlock(&(philos[i].meal_mutex));
				validate_print(data, i, "died");
				return ;
			}
			pthread_mutex_unlock(&(philos[i].meal_mutex));
		}
		check_meal(philos);
		if (check_eat(philos) == 1)
			break ;
		usleep(1000);
	}
}

int	simulater(t_data *data)
{
	int				i;
	t_philosopher	*phi;

	phi = data->philosophers;
	data->first_timestamp = timestamp();
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		pthread_mutex_lock(&(phi[i].meal_mutex));
		phi[i].t_last_meal = timestamp();
		pthread_mutex_unlock(&(phi[i].meal_mutex));
		i++;
	}
	death_checker(data, data->philosophers);
	exit_launcher(data, phi);
	return (0);
}
