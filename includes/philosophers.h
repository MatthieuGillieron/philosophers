/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:22:13 by mg                #+#    #+#             */
/*   Updated: 2025/04/11 15:59:30 by mg               ###   ########.fr       */
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
-----------------------------------------------------------------------
                Bibliothe pour :    
            printf, malloc/free, memset,
            write/uslepp, gettimeofday, ft_thread
-----------------------------------------------------------------------

*/

#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     
#include <sys/time.h>   
#include <pthread.h>    

/*
----------------------------------------------------------------------
    Déclaration anticipée des structures (forward declaration)
    Nécessaire quand deux structures se font référence mutuellement
----------------------------------------------------------------------
*/

typedef pthread_mutex_t pt_mtx;
typedef struct s_table  t_table;

typedef struct  s_fork
{
        pt_mtx  fork;
        int     id_fork;    
}               t_fork;



typedef struct  s_philo
{
        int             philo;
        long            meals_counter;
        bool            full;
        long            last_meal;
        t_fork          *left_fork;
        t_fork          *rigth_fork;
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
        t_fork  *forks;
        t_philo *philos;
};








#endif