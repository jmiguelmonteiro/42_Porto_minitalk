/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:05:03 by josemigu          #+#    #+#             */
/*   Updated: 2025/06/21 13:24:39 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	
}

int	main(void)
{
	pid_t	pid;
	struct sigaction sa;
	
	pid = getpid();
	ft_printf("%d\n", pid);
	ft_bzero(&sa, sizeof(sa));
	sa.__sigaction_u.__sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	while (true)
		pause();
	return (EXIT_SUCCESS);
}
