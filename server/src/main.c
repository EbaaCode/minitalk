/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:00:43 by ealshari          #+#    #+#             */
/*   Updated: 2025/02/17 15:43:11 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_server_context	g_ctx;

static int	setup_signal_handlers(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGUSR1, &act, NULL) == -1
		|| sigaction(SIGUSR2, &act, NULL) == -1)
		print_error_and_exit("Failed to setup signal handlers");
	return (EXIT_SUCCESS);
}

int	main(void)
{
	if (BUFFER_SIZE <= 1)
		print_error_and_exit("Buffer size must be greater than 1");
	ft_memset(&g_ctx, 0, sizeof(t_server_context));
	ft_printf("Server PID: %d\n", getpid());
	if (setup_signal_handlers() != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
