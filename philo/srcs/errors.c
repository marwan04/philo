/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:16:56 by malrifai          #+#    #+#             */
/*   Updated: 2025/01/21 22:07:02 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	write_error(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

int	error_manager(int error)
{
	if (error == 1)
		return (write_error("At least one wrong argument"));
	if (error == 2)
		return (write_error("Fatal error when intializing mutex"));
	return (1);
}

void validate_print(t_data *data, int id, char *string)
{
	pthread_mutex_lock(&(data->dieded_mutex));
	if(!data->dieded)
	{
		pthread_mutex_unlock(&(data->dieded_mutex));
		action_print(data, id, string);
	}
	else
		pthread_mutex_unlock(&(data->dieded_mutex));
}