/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:33:10 by malrifai          #+#    #+#             */
/*   Updated: 2025/01/20 20:34:33 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	if (argc != 5 && argc != 6)
		return (write_error("Wrong amount of arguments"));
	if ((ret = init_all(&data, argv)))
		return (error_manager(ret));
	if (simulater(&data))
		return (write_error("There was an error creating the threads"));
	return (0);
}