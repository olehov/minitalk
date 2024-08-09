/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:32:50 by ogrativ           #+#    #+#             */
/*   Updated: 2024/08/09 12:44:34 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "ft_libft/headers/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_server_state
{
	int		bit_pos;
	char	current_char;
	pid_t	client_pid;
}	t_server_state;

void	reset_state(void);
void	send_response(void);
void	handle_signal(int signal, siginfo_t *info, void *ptr);

#endif