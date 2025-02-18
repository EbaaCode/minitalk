/* ************************************************************************** */
/*                                                    Standard header block    */
/* ************************************************************************** */

#include "minitalk.h"

void	print_error_and_exit(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

int	send_signal(pid_t pid, int signum)
{
	if (kill(pid, signum) == -1)
	{
		ft_putendl_fd("Failed to send signal", 2);
		return (-1);
	}
	return (0);
}
