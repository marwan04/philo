/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:05:02 by malrifai          #+#    #+#             */
/*   Updated: 2025/01/22 20:46:21 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = data->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL)
			|| pthread_mutex_init(&(data->philosophers[i].meal_mutex), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(data->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(data->meal_check), NULL))
		return (1);
	if (pthread_mutex_init(&(data->dieded_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(data->all_ate_mutex), NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = data->nb_philo;
	while (--i >= 0)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].x_ate = 0;
		data->philosophers[i].left_fork_id = i;
		data->philosophers[i].right_fork_id = (i + 1) % data->nb_philo;
		data->philosophers[i].t_last_meal = 0;
		data->philosophers[i].data = data;
	}
	return (0);
}

int	init_all(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_death = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->all_ate = 0;
	data->dieded = 0;
	if (data->nb_philo <= 0 || data->time_death <= 0 || data->time_eat <= 0
		|| data->time_sleep <= 0 || data->nb_philo > 250)
		return (1);
	if (argv[5])
	{
		data->nb_eat = ft_atoi(argv[5]);
		if (data->nb_eat <= 0)
			return (1);
	}
	else
		data->nb_eat = -1;
	if (init_mutex(data))
		return (2);
	init_philosophers(data);
	return (0);
}
