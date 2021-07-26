#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	ft_get_pid(int *i, int *f, int *len)
{
	static int	pid = 0;
	static int	r = 1;

	if (*i == 15)
	{
		kill(pid, SIGUSR1);
		r = 1;
		pid = 0;
		*f = 0;
	}
	else
	{
		pid += *i * r;
		r *= 10;
	}
	*i = 0;
	*len = 0;
}

void	ft_get_char(int signal)
{
	static int	i = 0;
	static int	f = 0;
	static int	len = 0;
	char		c;

	if (signal == SIGUSR1)
		i = (i << 1) + 1;
	if (signal == SIGUSR2)
		i = (i << 1);
	len++;
	if (len == 8 && !f)
	{
		c = (char)i;
		write(1, &c, 1);
		if (c == '\0')
		{
			write(1, "\n", 1);
			f = 1;
		}
		len = 0;
		i = 0;
	}
	if (len == 4 && f)
		ft_get_pid(&i, &f, &len);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n > 9)
	{
		ft_putnbr(n / 10);
		c = n % 10 + '0';
		write(1, &c, 1);
	}
	else
	{
		c = n % 10 + '0';
		write(1, &c, 1);
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	write(1, "PID: ", 5);
	ft_putnbr(pid);
	write(1, "\n", 1);
	signal(SIGUSR1, ft_get_char);
	signal(SIGUSR2, ft_get_char);
	while (1)
		pause();
}
