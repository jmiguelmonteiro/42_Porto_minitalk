/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:04:39 by josemigu          #+#    #+#             */
/*   Updated: 2025/07/04 12:33:53 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_bit(pid_t server_pid, int bit)
{
	if (bit)
	{
		if (kill(server_pid, SIGUSR2) == -1)
			exit(ft_printf("Client: Error sending signal.\n"));
	}
	else
	{
		if (kill(server_pid, SIGUSR1) == -1)
			exit(ft_printf("Client: Error sending signal.\n"));
	}
	pause();
}

static void	send_char(pid_t server_pid, unsigned char c)
{
	int	i;

	i = 8;
	while (i--)
		send_bit(server_pid, (c >> i) & 1);
}

static void	send_string(pid_t server_pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		send_char(server_pid, str[i++]);
	send_char(server_pid, '\0');
	pause();
}

static void	signal_handler_client(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGUSR2)
		ft_printf("Client: Server acknowledge the received the message!!!\n");
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_printf("Client: Usage: ./client server_pid string_to_send\n");
		return (EXIT_FAILURE);
	}
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = signal_handler_client;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if ((sigaction(SIGUSR1, &sa, NULL) == -1)
		|| (sigaction(SIGUSR2, &sa, NULL) == -1))
	{
		ft_printf("Client: Error changing signals action.\n");
		return (EXIT_FAILURE);
	}
	ft_printf("Client: Sending message.\n");
	send_string(ft_atoi(argv[1]), argv[2]);
	return (EXIT_SUCCESS);
}
