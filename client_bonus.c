#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	ft_send_char(char c, int pid)
{
	int	i;
	int	kill_ret;

	i = 128;
	while (i)
	{
		if (c & i)
			kill_ret = kill(pid, SIGUSR1);
		else
			kill_ret = kill(pid, SIGUSR2);
		if (kill_ret == -1)
		{
			write(1, "Signal error\n", 13);
			exit(1);
		}
		usleep(75);
		i /= 2;
	}
}

void	ft_send_pid(int client_pid, int pid)
{
	int	i;

	while (client_pid)
	{
		i = 8;
		while (i)
		{
			if ((client_pid % 10) & i)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(75);
			i /= 2;
		}
		client_pid /= 10;
	}
	while (client_pid-- != -4)
	{
		kill(pid, SIGUSR1);
		usleep(75);
	}
}

void	ft_get_answer(int signal)
{
	if (signal == SIGUSR1)
	{
		write(1, "Message has been delivered\n", 27);
		write(1, "Response has been received from the server\n", 43);
		exit(0);
	}
}

int	ft_atoi(char *str)
{
	int	nbr;

	nbr = 0;
	while (*str >= '0' && *str <= '9')
		nbr = (nbr * 10) + (*str++ - '0');
	return (nbr);
}

int	main(int argc, char **argv)
{
	int	client_pid;
	int	pid;
	int	i;

	if (argc != 3)
	{
		write(1, "Try: ./client \"PID\" \"Message\"\n", 30);
		exit(1);
	}
	else
	{
		client_pid = getpid();
		signal(SIGUSR1, ft_get_answer);
		pid = ft_atoi(argv[1]);
		i = 0;
		while (argv[2][i])
			ft_send_char(argv[2][i++], pid);
		ft_send_char(argv[2][i], pid);
		ft_send_pid(client_pid, pid);
	}
	while (1)
		pause();
}
