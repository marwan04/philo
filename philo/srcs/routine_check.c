/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:08:57 by malrifai          #+#    #+#             */
/*   Updated: 2025/01/25 23:19:39 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo(t_philosopher *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->data->nb_philo == 1)
	{
		validate_print(data, philo->id, "has taken a fork");
		usleep(data->time_death * 1000);
		return (1);
	}
	return (0);
}

int	check_dead(t_philosopher *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->dieded_mutex));
	if (data->dieded)
	{
		pthread_mutex_unlock(&(data->dieded_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(data->dieded_mutex));
	return (0);
}

int	check_eat(t_philosopher *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->all_ate_mutex));
	if (data->all_ate)
	{
		pthread_mutex_unlock(&(data->all_ate_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(data->all_ate_mutex));
	return (0);
}

void	check_meal(t_philosopher *philo)
{
	t_data	*data;
	int		i;
	int		all_ate;

	i = 0;
	data = philo->data;
	pthread_mutex_lock(&(data->all_ate_mutex));
	if (data->nb_eat != -1)
	{
		all_ate = 1;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&(philo[i].meal_mutex));
			if (philo[i].x_ate < data->nb_eat)
				all_ate = 0;
			pthread_mutex_unlock(&(philo[i].meal_mutex));
			i++;
		}
		if (all_ate)
			data->all_ate = 1;
	}
	pthread_mutex_unlock(&(data->all_ate_mutex));
}
