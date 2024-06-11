/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapard <lchapard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:18:22 by lchapard          #+#    #+#             */
/*   Updated: 2024/04/06 16:18:23 by lchapard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	odd_philos(t_philo *ph)
{
	while (!sim_end(ph) && left_fork(ph) && right_fork(ph))
	{
		mutex_eat(ph);
		handle_mutex(&ph->left->fork, UNLOCK);
		handle_mutex(&ph->fork, UNLOCK);
		mutex_sleep(ph);
		usleep(ph->table->t_sleep * 1000);
		mutex_think(ph);
	}
}

void	even_philos(t_philo *ph)
{
	while (!sim_end(ph) && right_fork(ph) && left_fork(ph))
	{
		mutex_eat(ph);
		handle_mutex(&ph->fork, UNLOCK);
		handle_mutex(&ph->left->fork, UNLOCK);
		mutex_sleep(ph);
		usleep(ph->table->t_sleep * 1000);
		mutex_think(ph);
	}
}

void	*routine(void *phil)
{
	t_philo	*ph;
	long	start;

	ph = (t_philo *) phil;
	while (!m_get_bool(&ph->table->m_ready, &ph->table->t_ready))
	{
		usleep(500);
	}
	start = m_get_long(&ph->table->table_m, &ph->table->simulation_start);
	m_set_long(&ph->table->philo_m, &ph->last_meal, start);
	m_add_int(&ph->table->table_m, &ph->table->t_started, 1);
	desync_phil(ph);
	if (ph->ph_id % 2 == 0)
		even_philos(ph);
	else
		odd_philos(ph);
	return (NULL);
}

void	*watcher(void *phil)
{
	t_threads	*t;
	int			i;

	t = (t_threads *) phil;
	if (write_time('m') == -1)
	{
		printf("Error ! gettimeofday crashed!");
		m_set_bool(&t->table_m, &t->simulation_ended, true);
		return (NULL);
	}
	while (m_get_int(&t->table_m, &t->t_started) != t->nb)
		usleep(500);
	while (1)
	{
		i = 0;
		while (i < t->nb)
		{
			if (philo_died(t, i) == NULL)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
