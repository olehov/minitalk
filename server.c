/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:00:46 by ogrativ           #+#    #+#             */
/*   Updated: 2024/08/09 12:54:25 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft/headers/libft.h"
#include "server.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static t_server_state	g_state;

//reset state after get full message
void	reset_state(void)
{
	g_state.bit_pos = 0;
	g_state.current_char = 0;
	g_state.client_pid = 0;
}

//send Acknowledgment to client after printing message
void	send_response(void)
{
	ft_putchar_fd('\n', 1);
	if (kill(g_state.client_pid, SIGUSR2) == -1)
	{
		perror("Failed to send acknowledgment SIGUSR2");
	}
	reset_state();
}

/*
	g_state.current_char &= ~(1 << g_state.bit_pos); set bit to 0
	g_state.current_char |= (1 << g_state.bit_pos); set bit to 1
*/
void	handle_signal(int signal, siginfo_t *info, void *ptr)
{
	(void)ptr;
	if (g_state.client_pid == 0)
		g_state.client_pid = info->si_pid;
	if (signal == SIGUSR1)
		g_state.current_char &= ~(1 << g_state.bit_pos);
	else if (signal == SIGUSR2)
		g_state.current_char |= (1 << g_state.bit_pos);
	g_state.bit_pos++;
	if (g_state.bit_pos == 8)
	{
		ft_putchar_fd(g_state.current_char, 1);
		if (g_state.current_char == '\0')
			return (send_response());
		else
		{
			g_state.current_char = 0;
			g_state.bit_pos = 0;
		}
	}
	if (kill(g_state.client_pid, SIGUSR1) == -1)
	{
		perror("Failed to send acknowledgment");
		reset_state();
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	reset_state();
	while (1)
	{
		pause();
	}
	return (0);
}
