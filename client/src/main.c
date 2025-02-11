/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:01:06 by ealshari          #+#    #+#             */
/*   Updated: 2025/02/11 16:54:52 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int g_status = 0;

void	handler(int signum)
{
	if (signum == SIGUSR1)
		g_status = 1;
	else if (signum == SIGUSR2)
		exit(1);
}

void	send_char(char bit, int pid)
{
	unsigned char	temp;
	int				i_bit;

	i_bit = 8;
	temp = (unsigned char)bit;
	while (i_bit--)
	{
		g_status = 0;
		temp = (bit >> i_bit);
		if (temp % 2 == 0)
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(!!(write(STDOUT_FILENO, "Error\n", 6)));
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(!!(write(STDOUT_FILENO, "Error\n", 6)));
		}
		while (!g_status)
			;
	}
}


void send_message(char *data, int pid)
{
	int i;
	i = 0;
	while (data[i])
	{
		send_char(data[i], pid);
		i++;
	}
	send_char('\0', pid);
}

#include <stdio.h>

int	main(int argc, char **argv)
{
	struct sigaction sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;

	sigemptyset(&sa.sa_mask);
	if(sigaction(SIGUSR1, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	if(sigaction(SIGUSR2, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	if(argc == 3)
	{
		int pid = atoi(argv[1]);
		send_message(argv[2], pid);
	}
	return (0);
}
