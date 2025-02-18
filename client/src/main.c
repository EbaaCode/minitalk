/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:01:06 by ealshari          #+#    #+#             */
/*   Updated: 2025/02/17 15:41:46 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client_context	g_ctx;

static void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_ctx.status = 1;
	else if (signum == SIGUSR2)
		print_error_and_exit("Server terminated the connection");
}

static int	validate_input(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		print_error_and_exit("Usage: ./client [server_pid] [message]");
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		print_error_and_exit("Invalid PID");
	if (!ft_strlen(argv[2]))
		print_error_and_exit("Message cannot be empty");
	return (pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	ft_memset(&g_ctx, 0, sizeof(t_client_context));
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		print_error_and_exit("Failed to setup signal handlers");
	g_ctx.target_pid = validate_input(argc, argv);
	g_ctx.message = argv[2];
	transmit_message(&g_ctx);
	ft_putendl_fd("Message sent successfully", 1);
	return (EXIT_SUCCESS);
}
