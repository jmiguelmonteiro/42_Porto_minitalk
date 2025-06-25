/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:04:39 by josemigu          #+#    #+#             */
/*   Updated: 2025/06/25 16:10:50 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void send_char(pid_t server_pid, unsigned char c)
{
	int	i;

	printf("client, send_char, c: %c\n", c);
	i = 8;
	while (i--)
	{
//		printf("client, send_char, i, bool: %d %d\n", i, (c >> i) & 1);
		if ((c >> i) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		pause();
	}
}

static void send_string(pid_t server_pid, char *str)
{
	while (*str)
	{
		send_char(server_pid, str[0]);
		str++;
	}
	send_char(server_pid, '\0');
}

void signal_handler_client(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	
	if (argc != 3)
	{
		ft_printf("Usage: ./client server_pid string_to_send\n");
		return (EXIT_FAILURE);
	}
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = signal_handler_client;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_string(ft_atoi(argv[1]), argv[2]);
	return(EXIT_SUCCESS);
}
