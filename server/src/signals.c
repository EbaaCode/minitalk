/* ************************************************************************** */
/*                                                    Standard header block    */
/* ************************************************************************** */

#include "minitalk.h"

extern t_server_context	g_ctx;

static void	handle_client_switch(siginfo_t *info)
{
	if (g_ctx.client_pid && g_ctx.client_pid != info->si_pid)
	{
		if (send_signal(g_ctx.client_pid, SIGUSR2) == -1)
			ft_putendl_fd("Failed to notify previous client", 2);
		cleanup_context();
	}
	if (g_ctx.client_pid == 0)
		g_ctx.client_pid = info->si_pid;
}

static void	process_bit(int sig, siginfo_t *info)
{
	if (sig == SIGUSR1)
		g_ctx.current_char |= 1;
	g_ctx.current_bit++;
	if (g_ctx.current_bit == 8)
	{
		g_ctx.message_buffer[g_ctx.buffer_index++] = g_ctx.current_char;
		if (g_ctx.current_char == '\0')
		{
			process_complete_message();
			return ;
		}
		if (g_ctx.buffer_index == g_ctx.buffer_size
			&& handle_buffer_expansion() == -1)
		{
			if (send_signal(info->si_pid, SIGUSR2) == -1)
				ft_putendl_fd("Failed to notify client of error", 2);
			print_error_and_exit("Buffer expansion failed");
		}
		g_ctx.current_bit = 0;
		g_ctx.current_char = 0;
	}
	else
		g_ctx.current_char <<= 1;
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	handle_client_switch(info);
	if (!g_ctx.message_buffer)
	{
		g_ctx.message_buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
		if (!g_ctx.message_buffer)
		{
			if (send_signal(info->si_pid, SIGUSR2) == -1)
				ft_putendl_fd("Failed to notify client of error", 2);
			print_error_and_exit("Memory allocation failed");
		}
	}
	process_bit(sig, info);
	if (send_signal(info->si_pid, SIGUSR1) == -1)
		cleanup_context();
}
