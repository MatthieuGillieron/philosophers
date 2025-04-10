/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:22:13 by mg                #+#    #+#             */
/*   Updated: 2025/04/10 15:51:25 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H

/*
-----------------------------------------------------------------------
	        afficher du texte en couleur :
		printf(R "Ceci est un texte rouge." RST);
		printf(B "1er param choix couleur, dernier pour reset" RST);
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














#endif