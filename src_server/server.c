/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:05:03 by josemigu          #+#    #+#             */
/*   Updated: 2025/07/09 12:06:40 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/** @brief Concatenates s1 and s2 and frees s1
 *  @param s1 - string
 *  @param s2 - string
*/
static char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*result;
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_result;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_result = len_s1 + len_s2;
	result = malloc((len_result + 1) * sizeof (*result));
	if (!result)
		return (NULL);
	ft_memmove(result, s1, len_s1);
	ft_memmove(result + len_s1, s2, len_s2);
	result[len_result] = '\0';
	free(s1);
	return (result);
}

static void	send_signal(pid_t pid, int sig)
{
	if (kill(pid, sig) == -1)
		exit(ft_printf("Server: Error sending signal.\n"));
}

static bool	check_client_pid(pid_t *client_pid, siginfo_t *info)
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
	send_signal(*client_pid, SIGUSR1);
	ft_printf("\n");
	ft_printf("Server: Acknowledge received message.\n");
	send_signal(*client_pid, SIGUSR2);
	*client_pid = 0;
}

static void	signal_handler_server(int sig, siginfo_t *info, void *ucontext)
{
	static int				i = 0;
	static char				c = 0;
	static pid_t			client_pid = 0;
	static char				*message;

	(void)ucontext;
	if (!check_client_pid(&client_pid, info))
		return ;
	if (!message)
		message = ft_strdup("");
	if (sig == SIGUSR2)
		c |= 1;
	if (++i == 8)
	{
		i = 0;
		if (c == END_TRANSMISSION)
			acknowledge_received_message(&client_pid, &message);
		else
		{
			message = ft_strjoin_free(message, &c);
			send_signal(client_pid, SIGUSR1);
		}
		c = 0;
	}
	else
	{
		c = c << 1;
		send_signal(client_pid, SIGUSR1);
	}
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
