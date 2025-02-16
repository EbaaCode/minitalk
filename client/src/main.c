/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:01:06 by ealshari          #+#    #+#             */
/*   Updated: 2025/02/16 18:24:46 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct {
	int pid;
	int status;
	struct sigaction sa;
} t_client;

static void clean_exit(t_client *client, const char *error_msg)
{
	(void)client;  // In case we need cleanup later
	if (error_msg)
		write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	exit(EXIT_FAILURE);
}

static t_client *g_client;

static void handle_signals(int signum)
{
	if (signum == SIGUSR1)
		g_client->status = 1;
	else if (signum == SIGUSR2)
		exit(EXIT_SUCCESS);
}

static void initialize_client(t_client *client)
{
	g_client = client;
	client->status = 0;
	client->sa.sa_handler = handle_signals;
	client->sa.sa_flags = 0;
	sigemptyset(&client->sa.sa_mask);

	if (sigaction(SIGUSR1, &client->sa, NULL) == -1)
		clean_exit(client, "Failed to set SIGUSR1 handler\n");
	if (sigaction(SIGUSR2, &client->sa, NULL) == -1)
		clean_exit(client, "Failed to set SIGUSR2 handler\n");
}

static void validate_input(int argc, char **argv, t_client *client)
{
	if (argc != 3)
		clean_exit(client, "Usage: ./client [server_pid] [message]\n");

	client->pid = ft_atoi(argv[1]);
	if (client->pid <= 0)
		clean_exit(client, "Invalid PID\n");
}

static void send_bit(int bit, t_client *client)
{
	if (bit)
	{
		if (kill(client->pid, SIGUSR1) == -1)
			clean_exit(client, "Failed to send signal\n");
	}
	else
	{
		if (kill(client->pid, SIGUSR2) == -1)
			clean_exit(client, "Failed to send signal\n");
	}
	while (!client->status)
		;
	client->status = 0;
}

static void send_char(char c, t_client *client)
{
	int i;
	unsigned char temp;

	i = 8;
	temp = (unsigned char)c;
	while (i--)
		send_bit((temp >> i) & 1, client);
}

static void send_message(const char *msg, t_client *client)
{
	while (*msg)
	{
		send_char(*msg, client);
		msg++;
	}
	send_char('\0', client);
}

int main(int argc, char **argv)
{
	t_client client;

	initialize_client(&client);
	validate_input(argc, argv, &client);
	send_message(argv[2], &client);
	return (EXIT_SUCCESS);
}
