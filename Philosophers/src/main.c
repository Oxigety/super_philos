/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapard <lchapard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:32:58 by lchapard          #+#    #+#             */
/*   Updated: 2024/02/22 10:32:59 by lchapard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	safe_handle(int ret, t_opcode code)
{
	if (ret == 0)
		return (0);
	else if (code == LOCK && ret == EINVAL)
		printf("Incorrect argument ! Couldn't lock mutex!");
	else if (code == UNLOCK && ret == EINVAL)
		printf("Incorrect argument ! Couldn't unlock mutex!");
	else if (code == INIT && ret == EINVAL)
		printf("Incorrect argument ! Couldn't init mutex!");
	return (1);
}

int	handle_mutex(pthread_mutex_t *mutex, t_opcode code)
{
	int	res;

	if (code == LOCK)
		res = safe_handle(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		res = safe_handle(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		res = safe_handle(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		res = safe_handle(pthread_mutex_destroy(mutex), code);
	else
	{
		printf("unknown opcode for mutex !");
		res = 1;
	}
	return (res);
}

int	wait_for_threads(t_threads *t)
{
	int	i;

	i = 0;
	if (pthread_join(t->threads_tab[0], NULL) != 0)
		return (free_all(t, t->nb));
	while (++i <= t->nb)
	{
		if (pthread_join(t->threads_tab[i], NULL) != 0)
		{
			printf("Error while joining threads !");
			return (free_all(t, t->nb));
		}
	}
	return (1);
}

int	create_philos(int argc, char **argv, int nb)
{
	t_threads	my_t;
	int			i;

	i = 1;
	if (init_struct(&my_t, nb, argv, argc) < 0)
		return (-1);
	while (i <= nb && nb != 1)
	{
		if (pthread_create(my_t.threads_tab + i, NULL, &routine,
				&my_t.tab[i - 1]) != 0)
		{
			printf("Error while creating a new thread !");
			return (free_all(&my_t, i));
		}
		i++;
	}
	my_t.simulation_start = write_time('m');
	m_set_bool(&my_t.m_ready, &my_t.t_ready, true);
	if (wait_for_threads(&my_t) < 0)
		return (-1);
	return (free_all(&my_t, my_t.nb));
}

int	main(int argc, char **argv)
{
	int	nb_philo;

	if (argc < 5 || argc > 6)
		return (1);
	nb_philo = ft_atoi(argv[1]);
	if (nb_philo < 1 || nb_philo > MAX_PHILOS)
		return (-1);
	if (nb_philo == 1)
		lone_philo(argc, argv, nb_philo);
	else
		create_philos(argc, argv, nb_philo);
	return (0);
}
