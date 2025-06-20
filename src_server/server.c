/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:05:03 by josemigu          #+#    #+#             */
/*   Updated: 2025/06/20 18:59:20 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(void)
{
	pid_t	pid;
	struct sigaction sigact;
	
	pid = getpid();
	ft_printf("%d\n", pid);
	
	while (true)
	{
		
	}

	return (EXIT_SUCCESS);
}
