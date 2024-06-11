/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapard <lchapard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:27:05 by lchapard          #+#    #+#             */
/*   Updated: 2024/04/06 16:27:06 by lchapard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*league_player(void *phil)
{
	t_philo	*ph;

	ph = (t_philo *) phil;
	while (!m_get_bool(&ph->table->m_ready, &ph->table->t_ready))
		usleep(500);
	m_add_int(&ph->table->table_m, &ph->table->t_started, 1);
	ph->last_meal = m_get_long(&ph->table->philo_m,
			&ph->table->simulation_start);
	handle_mutex(&ph->table->print_m, LOCK);
	printf("%ld %d has taken a fork\n", write_time('m')
		- ph->table->simulation_start, ph->ph_id);
	handle_mutex(&ph->table->print_m, UNLOCK);
	while (!sim_end(ph))
		usleep(500);
	return (NULL);
}

int	lone_philo(int argc, char **argv, int nb)
{
	t_threads	my_t;

	if (init_struct(&my_t, nb, argv, argc) < 0)
		return (-1);
	if (nb == 1)
	{
		if (pthread_create(my_t.threads_tab + 1, NULL,
				&league_player, &my_t.tab[0]) != 0)
		{
			printf("Error while creating a new thread !");
			return (free_all(&my_t, 1));
		}
	}
	my_t.simulation_start = write_time('m');
	m_set_bool(&my_t.m_ready, &my_t.t_ready, true);
	if (pthread_join(my_t.threads_tab[0], NULL) != 0)
		return (free_all(&my_t, 1));
	if (pthread_join(my_t.threads_tab[1], NULL) != 0)
	{
		printf("Error while joining threads !");
		return (free_all(&my_t, 1));
	}
	return (free_all(&my_t, 1));
}
