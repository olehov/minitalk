/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:57:10 by ogrativ           #+#    #+#             */
/*   Updated: 2024/08/09 13:08:00 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft/headers/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static volatile int	g_ack_received = 0;

static void	handle_ack(int signal)
{
	if (signal == SIGUSR1)
	{
		g_ack_received = 1;
	}
	else if (signal == SIGUSR2)
	{
		ft_putstr_fd("Acknowledgment received message printed.\n", 1);
		exit(EXIT_SUCCESS);
	}
}

static void	send_bit(pid_t server_pid, int bit)
{
	if (bit)
	{
		if (kill(server_pid, SIGUSR2) == -1)
		{
			perror("Failed to send bit 1");
		}
	}
	else
	{
		if (kill(server_pid, SIGUSR1) == -1)
		{
			perror("Failed to send bit 0");
		}
	}
}

static void	send_char(pid_t server_pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		send_bit(server_pid, (c >> i) & 1);
		while (!g_ack_received)
		{
		}
		g_ack_received = 0;
		i++;
	}
}

static void	send_str(pid_t server_pid, char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (str == NULL)
	{
		return ;
	}
	ft_printf("Sending String \"%s\" to server\n", str);
	len = ft_strlen(str);
	while (i <= len)
	{
		send_char(server_pid, str[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	signal(SIGUSR1, handle_ack);
	signal(SIGUSR2, handle_ack);
	server_pid = (pid_t)ft_atoi(argv[1]);
	send_str(server_pid, argv[2]);
	exit (EXIT_SUCCESS);
}
