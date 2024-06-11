/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapard <lchapard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:14:59 by lchapard          #+#    #+#             */
/*   Updated: 2024/04/06 16:15:00 by lchapard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	sim_end(t_philo *ph)
{
	return (m_get_bool(&ph->table->table_m,
			&ph->table->simulation_ended));
}

time_t	write_time(char conv)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		return (-1);
	if (conv == 's')
		return (t.tv_sec + (t.tv_usec / 1e6));
	else if (conv == 'm')
		return ((t.tv_sec * 1e3) + (t.tv_usec / 1e3));
	else if (conv == 'u')
		return ((t.tv_sec * 1e6) + (t.tv_usec));
	return (-1);
}

bool	m_get_bool(pthread_mutex_t *mutex, bool *val)
{
	bool	ret;

	handle_mutex(mutex, LOCK);
	ret = *val;
	handle_mutex(mutex, UNLOCK);
	return (ret);
}

long	m_get_long(pthread_mutex_t *mutex, long *val)
{
	long	ret;

	handle_mutex(mutex, LOCK);
	ret = *val;
	handle_mutex(mutex, UNLOCK);
	return (ret);
}

int	m_get_int(pthread_mutex_t *mutex, int *val)
{
	int	ret;

	handle_mutex(mutex, LOCK);
	ret = *val;
	handle_mutex(mutex, UNLOCK);
	return (ret);
}
