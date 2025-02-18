/* ************************************************************************** */
/*                                                    Standard header block    */
/* ************************************************************************** */

#include "minitalk.h"

extern t_server_context	g_ctx;

void	cleanup_context(void)
{
	if (g_ctx.message_buffer)
	{
		free(g_ctx.message_buffer);
		g_ctx.message_buffer = NULL;
	}
	g_ctx.current_bit = 0;
	g_ctx.current_char = 0;
	g_ctx.buffer_size = BUFFER_SIZE;
	g_ctx.buffer_index = 0;
	g_ctx.client_pid = 0;
}

int	handle_buffer_expansion(void)
{
	char	*new_buffer;
	size_t	new_size;

	new_size = g_ctx.buffer_size + BUFFER_SIZE;
	new_buffer = ft_calloc(new_size, sizeof(char));
	if (!new_buffer)
		return (-1);
	ft_memcpy(new_buffer, g_ctx.message_buffer, g_ctx.buffer_size);
	free(g_ctx.message_buffer);
	g_ctx.message_buffer = new_buffer;
	g_ctx.buffer_size = new_size;
	return (0);
}

void	process_complete_message(void)
{
	ft_putstr_fd(g_ctx.message_buffer, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (send_signal(g_ctx.client_pid, SIGUSR1) == -1)
		cleanup_context();
	else
		cleanup_context();
}
