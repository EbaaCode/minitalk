/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:01:31 by ealshari          #+#    #+#             */
/*   Updated: 2025/02/18 16:08:00 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef ACK_TIMEOUT
# define ACK_TIMEOUT 50000
# endif

# if ACK_TIMEOUT < 1
# undef ACK_TIMEOUT
# define ACK_TIMEOUT 50000
# endif

# if BUFFER_SIZE < 1
# undef BUFFER_SIZE
# define BUFFER_SIZE 1024
# endif

void		print_error_and_exit(char *msg);

//- Client
typedef struct s_client_context
{
	int		target_pid;
	char	*message;
	int		ack_received;
}			t_client_context;

void		transmit_message(t_client_context *ctx);

//- Server
typedef struct s_server_context
{
	int		current_bit;
	char	current_char;
	int		buffer_index;
	int		buffer_size;
	char	*message_buffer;
	pid_t	client_pid;
}			t_server_context;

void		cleanup_context(t_server_context *ctx);
void		handle_buffer_expansion(t_server_context *ctx);
void		process_complete_message(t_server_context *ctx);

#endif
