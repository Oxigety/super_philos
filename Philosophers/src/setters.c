/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapard <lchapard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:14:50 by lchapard          #+#    #+#             */
/*   Updated: 2024/04/06 16:14:54 by lchapard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	m_set_bool(pthread_mutex_t *mutex, bool *val, bool new)
{
	handle_mutex(mutex, LOCK);
	*(val) = new;
	handle_mutex(mutex, UNLOCK);
}

void	m_add_int(pthread_mutex_t *mutex, int *val, int add)
{
	handle_mutex(mutex, LOCK);
	*(val) += add;
	handle_mutex(mutex, UNLOCK);
}

void	m_set_long(pthread_mutex_t *mutex, long *val, long new)
{
	handle_mutex(mutex, LOCK);
	*(val) = new;
	handle_mutex(mutex, UNLOCK);
}

void	m_set_int(pthread_mutex_t *mutex, int *val, int new)
{
	handle_mutex(mutex, LOCK);
	*(val) = new;
	handle_mutex(mutex, UNLOCK);
}
