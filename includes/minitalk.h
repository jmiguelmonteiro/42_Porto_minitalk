/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:25:06 by josemigu          #+#    #+#             */
/*   Updated: 2025/07/09 12:56:14 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 200809L
# define END_TRANSMISSION '\0'

# include <libft.h>
# include <stdbool.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

bool	check_client_pid(pid_t *client_pid, siginfo_t *info);

#endif
