/* ************************************************************************** */
/*                                                    Standard header block    */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_client_context
{
	int		target_pid;
	char	*message;
	int		status;
}	t_client_context;

void	transmit_message(t_client_context *ctx);
void	print_error_and_exit(char *msg);

#endif
