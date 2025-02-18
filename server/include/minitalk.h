/* ************************************************************************** */
/*                                                    Standard header block    */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_server_context
{
	int		current_bit;
	char	current_char;
	int		buffer_index;
	int		buffer_size;
	char	*message_buffer;
	int		client_pid;
}	t_server_context;

// Signal handling
void	handler(int sig, siginfo_t *info, void *ucontext);

// Buffer management
void	cleanup_context(void);
int		handle_buffer_expansion(void);
void	process_complete_message(void);

// Utilities
void	print_error_and_exit(char *msg);
int		send_signal(pid_t pid, int signum);

#endif
