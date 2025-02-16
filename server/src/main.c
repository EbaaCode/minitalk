/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:00:43 by ealshari          #+#    #+#             */
/*   Updated: 2025/02/16 20:24:58 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <string.h>

#define BUFFER_SIZE 1

void handler(int sig, siginfo_t *info, void *ucontext)
{
	static int		i;
	static char		c;
	static int 		index;
	static int 		buffer;
	static char		*str;
	static int pid;
	char *buff;

	if(pid == 0)
		pid = info->si_pid;
	if(pid != info->si_pid)
	{
		kill(pid, SIGUSR2);
		free(str);
		str = NULL;
		i = 0;
		c = 0;
		buffer = 0;
		buff = 0;
		index = 0;
		pid = info->si_pid;
	}
	if(buffer == 0)
		buffer = BUFFER_SIZE;
	if(str == NULL)
		str = calloc(BUFFER_SIZE, sizeof(char));

	(void)ucontext;
	if (sig == SIGUSR1)
		c |= 1;
	i++;
	if (i == 8)
	{
		str[index++] = c;
		if(index == buffer)
		{
			buff = str;
			str = calloc(BUFFER_SIZE + buffer, sizeof(char));
			memcpy(str, buff, buffer);
			free(buff);
			buff = NULL;
			buffer += BUFFER_SIZE;
		}
		if (c == '\0')
		{
			write(STDOUT_FILENO, str, strlen(str));
			write(STDOUT_FILENO, "\n", 1);
			i = 0;
			c = 0;
			buffer = 0;
			buff = 0;
			index = 0;
			pid = 0;
			free(str);
			str = NULL;
			kill(info->si_pid, SIGUSR1);
			return ;
		}
		i = 0;
		c = 0;
	}
	else
		c <<= 1;
	kill(info->si_pid, SIGUSR1);
}

#include <stdio.h>

int	main(void)
{

	int pid = getpid();
	printf("the pid is: %d\n", pid);
	struct sigaction	act;
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	if(sigaction(SIGUSR1, &act, NULL) == -1)
		return (EXIT_FAILURE);
	if(sigaction(SIGUSR2, &act, NULL) == -1)
		return (EXIT_FAILURE);
	while (1)
		pause();
	return (0);
}


// THE EPIC SUPER DUPER LIST OF THINGS KMKINGMAN RECOMMENDS I HANDLE / TEST TO MAKE THE GREATEST EPIC MINITALK PROJECT TO EVER EXIST:
// - if the buffersize is 0 or 1 (use -D flag to change the buffer size)
// - if the system calls just faild  (for ex: kill) they should return -1
