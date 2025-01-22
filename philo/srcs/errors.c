/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:16:56 by malrifai          #+#    #+#             */
/*   Updated: 2025/01/22 20:58:42 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	write_error(char *str)
{
	int	len;

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

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	validate_print(t_data *data, int id, char *string)
{
	pthread_mutex_lock(&(data->writing));
	pthread_mutex_lock(&(data->dieded_mutex));
	if (!data->dieded || ft_strcmp(string, "died") == 0)
	{
		if (ft_strcmp(string, "died") == 0)
			data->dieded = 1;
		pthread_mutex_unlock(&(data->dieded_mutex));
		printf("%lli %i %s\n", timestamp() - data->first_timestamp, id + 1,
			string);
	}
	else
		pthread_mutex_unlock(&(data->dieded_mutex));
	pthread_mutex_unlock(&(data->writing));
}
