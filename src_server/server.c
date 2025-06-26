/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:05:03 by josemigu          #+#    #+#             */
/*   Updated: 2025/06/25 16:07:53 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void signal_handler_server(int sig, siginfo_t *info, void *ucontext)
{
	static int				i = 0;
	static unsigned char	c = 0;
	static pid_t			client_pid = 0;

	printf("server, i, signal received: %d, %d\n", i, sig);

	(void)ucontext;
	if (client_pid == 0)
		client_pid = info->si_pid;
	else
		if (client_pid != info->si_pid)
			return ;
	if (sig == SIGUSR2)
		c |= 1;
	i++;
	kill(client_pid, SIGUSR1);
	if (i == 8)
	{
		i = 0;
		if (c == END_TRANSMISSION)
		{
			kill(client_pid, SIGUSR2);
			client_pid = 0;
		}
		else
			ft_putchar_fd(c, 1);
		c = 0;
	} else
		c = c << 1;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;
	
	pid = getpid();
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = signal_handler_server;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if ((sigaction(SIGUSR1, &sa, NULL) == -1) || (sigaction(SIGUSR2, &sa, NULL) == -1))
	{
		ft_printf("Error changing signals action.\n");
		return (EXIT_FAILURE);
	}
	ft_printf("Server PID: %d\n", pid);
	while (true)
		pause();
	return (EXIT_SUCCESS);
}
