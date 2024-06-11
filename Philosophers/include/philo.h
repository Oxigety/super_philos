/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapard <lchapard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:33:05 by lchapard          #+#    #+#             */
/*   Updated: 2024/02/22 10:33:06 by lchapard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <errno.h>

# define MAX_PHILOS 200

typedef enum s_opcode
{
	INIT,
	DETACH,
	LOCK,
	UNLOCK,
	DESTROY,
}			t_opcode;

struct						s_threads;

struct	s_philo
{
	int					ph_id;
	int					ate;
	pthread_mutex_t		fork;
	time_t				last_meal;
	bool				full;
	struct s_philo		*left;
	struct s_philo		*right;
	struct s_threads	*table;
};
typedef struct s_philo		t_philo;

struct s_threads
{
	t_philo			*tab;
	pthread_mutex_t	*fork_tab;
	pthread_t		*threads_tab;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_meals;
	int				nb;
	int				cpt_full;
	int				t_started;
	pthread_mutex_t	print_m;
	pthread_mutex_t	table_m;
	pthread_mutex_t	philo_m;
	pthread_mutex_t	m_ready;
	time_t			simulation_start;
	bool			simulation_ended;
	bool			t_ready;
};
typedef struct s_threads	t_threads;

int				handle_mutex(pthread_mutex_t *mutex, t_opcode code);
void			m_set_bool(pthread_mutex_t *mutex, bool *val, bool new);
void			m_add_int(pthread_mutex_t *mutex, int *val, int add);
void			m_set_long(pthread_mutex_t *mutex, long *val, long new);
void			m_set_int(pthread_mutex_t *mutex, int *val, int new);
void			odd_philos(t_philo *ph);
void			even_philos(t_philo *ph);
void			*routine(void *phil);
void			*watcher(void *phil);
int				sim_end(t_philo *ph);
time_t			write_time(char conv);
bool			m_get_bool(pthread_mutex_t *mutex, bool *val);
long			m_get_long(pthread_mutex_t *mutex, long *val);
int				m_get_int(pthread_mutex_t *mutex, int *val);
void			set_neighbours(t_threads *t, int nb, int i);
int				init_mutexes(t_threads *t, pthread_mutex_t *forks);
pthread_mutex_t	*set_tab_philos(t_threads *t, int i);
int				init_struct(t_threads *t, int nb_philo, char **argv, int argc);
int				ft_atoi(const char *str);
void			*safe_malloc(t_threads *t, size_t size, char c);
int				free_all(t_threads *t, int max);
void			desync_phil(t_philo *ph);
void			*philo_died(t_threads *t, int i);
void			mutex_think(t_philo *ph);
void			mutex_sleep(t_philo *ph);
void			mutex_eat(t_philo *ph);
int				left_fork(t_philo *ph);
int				right_fork(t_philo *ph);
void			*league_player(void *phil);
int				lone_philo(int argc, char **argv, int nb);

#endif