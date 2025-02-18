/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:06:38 by ealshari          #+#    #+#             */
/*   Updated: 2025/02/18 15:47:02 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	cleanup_context(t_server_context *ctx)
{
	if (ctx->message_buffer)
	{
		free(ctx->message_buffer);
		ctx->message_buffer = NULL;
	}
	ctx->current_bit = 0;
	ctx->current_char = 0;
	ctx->buffer_size = BUFFER_SIZE;
	ctx->buffer_index = 0;
	ctx->client_pid = 0;
}

void	handle_buffer_expansion(t_server_context *ctx)
{
	char	*new_buffer;
	size_t	new_size;

	new_size = ctx->buffer_size + BUFFER_SIZE;
	new_buffer = ft_calloc(new_size, sizeof(char));
	if (!new_buffer)
	{
		if (kill(ctx->client_pid, SIGUSR2) == -1)
			ft_putendl_fd("Failed to notify client of error", STDERR_FILENO);
		print_error_and_exit("Buffer expansion failed");
	}
	ft_memcpy(new_buffer, ctx->message_buffer, ctx->buffer_size);
	free(ctx->message_buffer);
	ctx->message_buffer = new_buffer;
	ctx->buffer_size = new_size;
}

void	process_complete_message(t_server_context *ctx)
{
	ft_putstr_fd(ctx->message_buffer, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (kill(ctx->client_pid, SIGUSR1) == -1)
		ft_putstr_fd("Failed to send acknowledgment to client\n",
			STDERR_FILENO);
	else
		ft_putstr_fd("Message acknowledged\n", STDOUT_FILENO);
	cleanup_context(ctx);
}
