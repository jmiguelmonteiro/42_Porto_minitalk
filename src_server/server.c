/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:05:03 by josemigu          #+#    #+#             */
/*   Updated: 2025/06/27 18:39:10 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static bool check_client_pid(pid_t *client_pid, siginfo_t *info)
{
	if (*client_pid == 0)
		*client_pid = info->si_pid;
	else
		if (*client_pid != info->si_pid)
			return (false);
	return (true);
}

static void	acknowledge_received_message(pid_t *client_pid, char **message)
{
	write(1, *message, ft_strlen(*message));
	free(*message);
	*message = NULL;
	ft_printf("\n");
	ft_printf("Server: Acknowledge received message.\n");
	if (kill(*client_pid, SIGUSR2) == -1)
	{
		exit (ft_printf("Server: Error sending signal.\n"));
	}
	*client_pid = 0;
}

static void	signal_handler_server(int sig, siginfo_t *info, void *ucontext)
{
	static int				i = 0;
	static char				c = 0;
	static pid_t			client_pid = 0;
	static char				*message;
	char					*temp;

	(void)ucontext;
	if (!check_client_pid(&client_pid, info))
		return ;
	if (!message)
		message = ft_strdup("");
	if (sig == SIGUSR2)
		c |= 1;
	i++;
	kill(client_pid, SIGUSR1);
	if (i == 8)
	{
		i = 0;
		if (c == END_TRANSMISSION)
			acknowledge_received_message(&client_pid, &message);
		else
		{
			temp = message;
			message = ft_strjoin(message, &c);
			free(temp);
		}
		c = 0;
	}
	else
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
	if ((sigaction(SIGUSR1, &sa, NULL) == -1)
		|| (sigaction(SIGUSR2, &sa, NULL) == -1))
	{
		ft_printf("Server: Error changing signals action.\n");
		return (EXIT_FAILURE);
	}
	ft_printf("Server: PID %d, waiting for messages.\n", pid);
	while (true)
		pause();
	return (EXIT_SUCCESS);
}
