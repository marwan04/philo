/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:45:31 by malrifai          #+#    #+#             */
/*   Updated: 2025/01/21 22:09:46 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void smart_sleep(long long time, t_data *data)
{
    long long start_time = timestamp();
    while (1)
    {
        pthread_mutex_lock(&(data->dieded_mutex));
        if (data->dieded)
        {
            pthread_mutex_unlock(&(data->dieded_mutex));
            break;
        }
        pthread_mutex_unlock(&(data->dieded_mutex));
        if (time_diff(start_time, timestamp()) >= time)
            break;
        usleep(100);
    }
}


void action_print(t_data *data, int id, char *string)
{
    pthread_mutex_lock(&(data->writing));
    pthread_mutex_lock(&(data->dieded_mutex));
    if (!(data->dieded))
    {
        pthread_mutex_unlock(&(data->dieded_mutex));
        printf("%lli %i %s\n", timestamp() - data->first_timestamp, id + 1, string);
    }
    else
        pthread_mutex_unlock(&(data->dieded_mutex));
    pthread_mutex_unlock(&(data->writing));
}

