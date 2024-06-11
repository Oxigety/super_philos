/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapard <lchapard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:24:25 by lchapard          #+#    #+#             */
/*   Updated: 2024/04/06 16:24:26 by lchapard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long int	total;
	size_t		i;

	i = 0;
	sign = 1;
	total = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		total = total * 10 + (str[i] - 48);
		if (total < 0 && sign > 0)
			return (-1);
		if (total < 0 && sign < 0)
			return (0);
		i++;
	}
	return (total * sign);
}

void	*safe_malloc(t_threads *t, size_t size, char c)
{
	void	*ret;

	if (c == 'm')
	{
		free(t->threads_tab);
		free(t->tab);
		return (NULL);
	}
	ret = malloc(size);
	if (ret == NULL)
	{
		printf("Error ! Malloc failed ! %c \n", c);
		if (c == 'p')
			free(t->threads_tab);
		if (c == 'f')
		{
			free(t->threads_tab);
			free(t->tab);
		}
	}
	return (ret);
}

void	desync_phil(t_philo *ph)
{
	if (ph->table->nb % 2 == 0)
	{
		if (ph->ph_id % 2 == 0)
			usleep(3e4);
	}
	else
	{
		if (ph->ph_id % 2)
			mutex_think(ph);
	}
}

void	*philo_died(t_threads *t, int i)
{
	if (t->nb == m_get_int(&t->table_m, &t->cpt_full))
	{
		m_set_bool(&t->table_m, &t->simulation_ended, true);
		return (NULL);
	}
	if ((write_time('m') - m_get_long(&t->philo_m,
				&t->tab[i].last_meal)) > t->t_die)
	{
		handle_mutex(&t->print_m, LOCK);
		printf("%ld %d died\n", write_time('m') - t->simulation_start,
			t->tab[i].ph_id);
		handle_mutex(&t->print_m, UNLOCK);
		m_set_bool(&t->table_m, &t->simulation_ended, true);
		return (NULL);
	}
	return (t);
}
