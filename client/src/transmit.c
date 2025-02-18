/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:21:09 by ealshari          #+#    #+#             */
/*   Updated: 2025/02/18 16:35:59 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_byte(t_client_context *ctx, unsigned char byte)
{
	int	bit_position;

	bit_position = 7;
	while (bit_position >= 0)
	{
		ctx->ack_received = 0;
		if ((byte >> bit_position) & 1)
		{
			if (kill(ctx->target_pid, SIGUSR1) == -1)
				print_error_and_exit("Failed to send signal to server");
		}
		else
		{
			if (kill(ctx->target_pid, SIGUSR2) == -1)
				print_error_and_exit("Failed to send signal to server");
		}
		while (!ctx->ack_received);
		bit_position--;
	}
}

void	transmit_message(t_client_context *ctx)
{
	int	i;

	i = 0;
	while (ctx->message[i])
	{
		send_byte(ctx, (unsigned char)ctx->message[i]);
		i++;
	}
	send_byte(ctx, '\0');
}
