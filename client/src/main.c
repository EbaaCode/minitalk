/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:01:06 by ealshari          #+#    #+#             */
/*   Updated: 2025/02/16 20:39:39 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_client_context
{
	int		target_pid;
	char	*message;
	int		status;
}	t_client_context;

static t_client_context	g_ctx;

static void	error_exit(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

static void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_ctx.status = 1;
	else if (signum == SIGUSR2)
		error_exit("Server terminated the connection");
}

static int	validate_input(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		error_exit("Usage: ./client [server_pid] [message]");
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		error_exit("Invalid PID");
	if (!ft_strlen(argv[2]))
		error_exit("Message cannot be empty");
	return (pid);
}

static void	send_byte(unsigned char byte)
{
	int	bit_position;

	bit_position = 7;
	while (bit_position >= 0)
	{
		g_ctx.status = 0;
		if ((byte >> bit_position) & 1)
		{
			if (kill(g_ctx.target_pid, SIGUSR1) == -1)
				error_exit("Failed to send signal to server");
		}
		else
		{
			if (kill(g_ctx.target_pid, SIGUSR2) == -1)
				error_exit("Failed to send signal to server");
		}
		while (!g_ctx.status)
			;
		bit_position--;
	}
}

static void	transmit_message(void)
{
	int	i;

	i = 0;
	while (g_ctx.message[i])
	{
		send_byte((unsigned char)g_ctx.message[i]);
		i++;
	}
	send_byte('\0');
}

static int	setup_signal_handlers(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		error_exit("Failed to setup SIGUSR1 handler");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		error_exit("Failed to setup SIGUSR2 handler");
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	ft_memset(&g_ctx, 0, sizeof(t_client_context));
	if (setup_signal_handlers() != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	g_ctx.target_pid = validate_input(argc, argv);
	g_ctx.message = argv[2];
	transmit_message();
	ft_putendl_fd("Message sent successfully", 1);
	return (EXIT_SUCCESS);
}
