/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:22:13 by mg                #+#    #+#             */
/*   Updated: 2025/04/16 14:32:57 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H

/*
-----------------------------------------------------------------------
	        afficher du texte en couleur :
	printf(GREEN "Ceci est un texte vert." RST);
	printf(BLUE "1er -> color, dernier -> reset" RST);

                         Example : 
        int valeur = 42;
        printf("La valeur est : " RED "%d" RST "\n", valeur);
-----------------------------------------------------------------------
*/

# define RST	    "\033[0m"		
# define RED	    "\033[1;31m"	
# define GREEN		"\033[1;32m"	
# define YELLOW		"\033[1;33m"	
# define BLUE		"\033[1;34m"	
# define MAGENTA	"\033[1;35m"	
# define CYAN		"\033[1;36m"	
# define WHITE		"\033[1;37m"	

/*
        write_debug ft
*/
#define DEBUG_MODE 0
/*
        OPcode pour mutex | chaque instructuion a un opcode qui la  represente
*/

typedef enum    e_opcode
{
        LOCK,
        UNLOCK,
        INIT,
        DESTROY,
        CREATE,
        JOIN,
        DETACH,
}               t_opcode;

/*
        code pour get_time | 0 = SECOND, 1 = MILLI ..
*/

typedef enum e_time_code
{
        SECOND,
        MILLISECOND,
        MICROSECOND,

}               t_time_code;

/*
        philo state
*/

typedef enum e_status
{
        EATING,
        SLEEPING,
        THINKING,
        TAKE_FIRST_WORK,
        TAKE_SECOND_FORK,
        DIED,
}               t_philo_status;

/*
-----------------------------------------------------------------------
                Bibliothe pour :    
            printf, malloc/free, memset,
            write/uslepp, gettimeofday,
            ft_thread, bool
-----------------------------------------------------------------------
*/

#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     
#include <sys/time.h>   
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>


/*
----------------------------------------------------------------------
    Déclaration anticipée des structures (forward declaration)
    Nécessaire quand deux structures se font référence mutuellement
----------------------------------------------------------------------
*/

typedef pthread_mutex_t t_mtx;
typedef struct s_table  t_table;

typedef struct  s_fork
{
        t_mtx  fork;
        int     id_fork;    
}               t_fork;



typedef struct  s_philo
{
        int             philo;
        int             id;
        long            meals_counter;
        bool            full;
        long            last_meal;
        t_fork          *first_fork; // left
        t_fork          *second_fork; // rigth
        pthread_t       thread_id;
        t_table         *table;      

        
}               t_philo;



struct  s_table
{
        long    philo_nbr;
        long    time_to_die;
        long    time_to_sleep;
        long    time_to_eat;
        long    limit_meals;
        long    start;
        bool    end;
        bool    all_thread;
        t_mtx   table_mtx;
        t_mtx   write_mtx;
        t_fork  *forks;
        t_philo *philos;
};


/*
-------------------------------------------
                prototypes
-------------------------------------------
*/


//      *** UTILS ***
void    exit_error(const char *error);
inline  bool is_digit(char c);
void    *safe_malloc(size_t bytes);
void    safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
void    safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
long    get_time(t_time_code time_code);


//      *** SYNCHRO ***
void    wait_thread(t_table *table);
void    better_usleep(long usec, t_table *table);



//      *** PARSING ***
void    parse_input(t_table *table, char **av);


//      *** INIT ***
void    data_init(t_table *table);


//      *** SETTER_GETTER ***
bool    sim_finish(t_table *table);
long    get_long(t_mtx *mutex, long *value);
void    set_long(t_mtx *mutex, long *dest, long value);
bool    get_bool(t_mtx *mutex, bool *value);
void    set_bool(t_mtx *mutex, bool *dest, bool value);

//       *** WRITE ***
void    write_status(t_philo_status status, t_philo *philo, bool debug);






#endif