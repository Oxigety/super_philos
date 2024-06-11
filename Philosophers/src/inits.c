/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapard <lchapard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:15:28 by lchapard          #+#    #+#             */
/*   Updated: 2024/04/06 16:15:29 by lchapard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	free_all(t_threads *t, int max)
{
	int	i;

	i = -1;
	handle_mutex(&(t->print_m), DESTROY);
	handle_mutex(&(t->table_m), DESTROY);
	handle_mutex(&(t->philo_m), DESTROY);
	handle_mutex(&(t->m_ready), DESTROY);
	while (++i < max)
		handle_mutex(&(t->tab[i].fork), DESTROY);
	free(t->threads_tab);
	free(t->tab);
	free(t->fork_tab);
	return (-1);
}

void	set_neighbours(t_threads *t, int nb, int i)
{
	t->tab[i].table = t;
	t->tab[i].ph_id = i + 1;
	if (nb == 1)
		return ;
	if (i >= 1 && i <= nb - 2)
	{
		t->tab[i].left = &(t->tab[i - 1]);
		t->tab[i].right = &(t->tab[i + 1]);
	}
	t->tab[0].right = &(t->tab[1]);
	t->tab[0].left = &(t->tab[nb - 1]);
	t->tab[nb - 1].right = &(t->tab[0]);
	t->tab[nb - 1].left = &(t->tab[nb - 2]);
}

int	init_mutexes(t_threads *t, pthread_mutex_t *forks)
{
	int	err;
	int	i;

	i = 0;
	err = handle_mutex(&t->print_m, INIT);
	err += handle_mutex(&t->table_m, INIT);
	err += handle_mutex(&t->philo_m, INIT);
	err += handle_mutex(&t->m_ready, INIT);
	while (i < t->nb)
	{
		err += handle_mutex(&(forks[i]), INIT);
		i++;
	}
	if (err != 0)
		return (-1);
	return (1);
}

pthread_mutex_t	*set_tab_philos(t_threads *t, int i)
{
	pthread_mutex_t	*forks;

	t->tab = safe_malloc(t, sizeof(t_philo) * t->nb, 'p');
	if (t->tab == NULL)
		return (NULL);
	forks = safe_malloc(t, sizeof(pthread_mutex_t) * t->nb, 'f');
	if (forks == NULL)
		return (NULL);
	t->cpt_full = 0;
	if (init_mutexes(t, forks) < 0)
	{
		safe_malloc(t, 0, 'm');
		free(forks);
		return (NULL);
	}
	while (++i < t->nb)
	{
		t->tab[i].fork = forks[i];
		t->tab[i].last_meal = __LONG_MAX__;
		t->tab[i].ate = 0;
		t->tab[i].full = false;
		set_neighbours(t, t->nb, i);
	}
	return (forks);
}

int	init_struct(t_threads *t, int nb_philo, char **argv, int argc)
{
	t->t_die = ft_atoi(argv[2]);
	t->t_eat = ft_atoi(argv[3]);
	t->t_sleep = ft_atoi(argv[4]);
	t->max_meals = -1;
	if (argc == 6)
		t->max_meals = ft_atoi(argv[5]);
	if (t->t_eat < 1 || t->t_sleep < 1 || t->t_die < 1
		|| (argc == 6 && t->max_meals < 0))
		return (-1);
	t->simulation_ended = false;
	t->t_ready = false;
	t->t_started = 0;
	t->threads_tab = NULL;
	t->fork_tab = NULL;
	t->tab = NULL;
	t->nb = nb_philo;
	t->threads_tab = safe_malloc(t, (sizeof(pthread_t) * (t->nb + 1)), 't');
	if (t->threads_tab == NULL)
		return (-1);
	t->fork_tab = set_tab_philos(t, -1);
	if (t->fork_tab == NULL)
		return (-1);
	if (pthread_create(t->threads_tab, NULL, &watcher, t) != 0)
		return (free_all(t, t->nb));
	return (0);
}
