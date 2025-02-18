/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:00:43 by ealshari          #+#    #+#             */
/*   Updated: 2025/02/18 16:31:51 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_server_context	g_ctx;

static void	handle_client_management(siginfo_t *info)
{
	if (g_ctx.client_pid && g_ctx.client_pid != info->si_pid)
	{
		if (kill(g_ctx.client_pid, SIGUSR2) == -1)
			ft_putendl_fd("Failed to notify previous client", STDERR_FILENO);
		cleanup_context(&g_ctx);
	}
	if (g_ctx.client_pid == 0)
		g_ctx.client_pid = info->si_pid;
	if (!g_ctx.message_buffer)
	{
		g_ctx.message_buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
		if (!g_ctx.message_buffer)
		{
			if (kill(info->si_pid, SIGUSR2) == -1)
				ft_putendl_fd("Failed to notify client of error",
					STDERR_FILENO);
			print_error_and_exit("Memory allocation failed");
		}
	}
}

static void	handle_message_reception(int sig, siginfo_t *info)
{
	if (sig == SIGUSR1)
		g_ctx.current_char |= 1;
	g_ctx.current_bit++;
	if (g_ctx.current_bit == 8)
	{
		g_ctx.message_buffer[g_ctx.buffer_index++] = g_ctx.current_char;
		if (g_ctx.current_char == '\0')
		{
			process_complete_message(&g_ctx);
			return ;
		}
		if (g_ctx.buffer_index == g_ctx.buffer_size)
			handle_buffer_expansion(&g_ctx);
		g_ctx.current_bit = 0;
		g_ctx.current_char = 0;
	}
	else
		g_ctx.current_char <<= 1;
	if (kill(info->si_pid, SIGUSR1) == -1)
	{
		ft_putendl_fd("Failed to acknowledge bit reception", STDERR_FILENO);
		cleanup_context(&g_ctx);
	}
}

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	handle_client_management(info);
	handle_message_reception(sig, info);
}

static void	setup_signal_handlers(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		print_error_and_exit("Failed to setup SIGUSR1 handler");
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		print_error_and_exit("Failed to setup SIGUSR2 handler");
}

int	main(void)
{
	ft_memset(&g_ctx, 0, sizeof(t_server_context));
	ft_printf("Server PID: %d\n", getpid());
	setup_signal_handlers();
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
