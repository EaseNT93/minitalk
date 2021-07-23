#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	ft_get_char(int signal)
{
	static int	len = 0;
	static int	i = 0;
	char		c;

	if (signal == SIGUSR1)
		i = i + (1 << len++);
	if (signal == SIGUSR2)
		i = i + (0 << len++);
	if (len == 8)
	{
		c = (char)i;
		write(1, &c, 1);
		if (c == '\0')
			write(1, "\n", 1);
		len = 0;
		i = 0;
	}
}

void	ft_putnbr(int n)
{
	char	c;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
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
	{
		pause();
	}
}
