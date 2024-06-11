/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapard <lchapard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:22:56 by lchapard          #+#    #+#             */
/*   Updated: 2024/04/06 16:22:56 by lchapard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	mutex_think(t_philo *ph)
{
	long	t_sleep;
	long	t_eat;
	long	t_think;

	handle_mutex(&ph->table->print_m, LOCK);
	if (!sim_end(ph))
	{
		printf("%ld %d is thinking\n", write_time('m')
			- ph->table->simulation_start, ph->ph_id);
		handle_mutex(&ph->table->print_m, UNLOCK);
		if (ph->table->nb % 2 == 0)
			return ;
		t_eat = ph->table->t_eat;
		t_sleep = ph->table->t_sleep;
		t_think = t_eat * 2 - t_sleep;
		if (t_think <= 0)
			return ;
		usleep(t_think * 0.42 * 1000);
		return ;
	}
	handle_mutex(&ph->table->print_m, UNLOCK);
}

void	mutex_sleep(t_philo *ph)
{
	handle_mutex(&ph->table->print_m, LOCK);
	if (!sim_end(ph))
	{
		printf("%ld %d is sleeping\n", write_time('m')
			- ph->table->simulation_start, ph->ph_id);
		handle_mutex(&ph->table->print_m, UNLOCK);
		return ;
	}
	handle_mutex(&ph->table->print_m, UNLOCK);
}

void	mutex_eat(t_philo *ph)
{
	handle_mutex(&ph->table->print_m, LOCK);
	if (!sim_end(ph))
	{
		printf("%ld %d is eating\n", write_time('m')
			- ph->table->simulation_start, ph->ph_id);
		handle_mutex(&ph->table->print_m, UNLOCK);
		m_set_long(&ph->table->philo_m, &ph->last_meal, write_time('m'));
		usleep(ph->table->t_eat * 1000);
		m_add_int(&ph->table->philo_m, &ph->ate, 1);
		if (ph->ate == m_get_int(&ph->table->table_m, &ph->table->max_meals))
		{
			m_set_bool(&ph->table->philo_m, &ph->full, true);
			m_add_int(&ph->table->table_m, &ph->table->cpt_full, 1);
		}
		return ;
	}
	handle_mutex(&ph->table->print_m, UNLOCK);
}

int	left_fork(t_philo *ph)
{
	handle_mutex(&ph->left->fork, LOCK);
	if (!sim_end(ph))
	{
		handle_mutex(&ph->table->print_m, LOCK);
		if (!sim_end(ph))
		{
			printf("%ld %d has taken a fork\n", write_time('m')
				- ph->table->simulation_start, ph->ph_id);
		}
		handle_mutex(&ph->table->print_m, UNLOCK);
	}
	return (1);
}

int	right_fork(t_philo *ph)
{
	handle_mutex(&ph->fork, LOCK);
	if (!sim_end(ph))
	{
		handle_mutex(&ph->table->print_m, LOCK);
		if (!sim_end(ph))
		{
			printf("%ld %d has taken a fork\n", write_time('m')
				- ph->table->simulation_start, ph->ph_id);
		}
		handle_mutex(&ph->table->print_m, UNLOCK);
	}
	return (1);
}
