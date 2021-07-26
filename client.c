#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	ft_send_char(int c, int pid)
{
	int	i;
	int	kill_ret;

	i = 0;
	while (i < 8)
	{
		if (c % 2 == 1)
			kill_ret = kill(pid, SIGUSR1);
		else
			kill_ret = kill(pid, SIGUSR2);
		if (kill_ret == -1)
		{
			write(1, "Signal error\n", 13);
			exit(1);
		}
		usleep(75);
		c /= 2;
		i++;
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
	int	pid;
	int	i;

	if (argc != 3)
	{
		write(1, "Try: ./client \"PID\" \"Message\"\n", 30);
		exit(1);
	}
	else
	{
		pid = ft_atoi(argv[1]);
		i = 0;
		while (argv[2][i])
			ft_send_char(argv[2][i++], pid);
		ft_send_char(argv[2][i], pid);
	}
	return (0);
}
