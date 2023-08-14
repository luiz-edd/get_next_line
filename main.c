#include "get_next_line.h"
#include "stdio.h"
#include <fcntl.h>

int	main(void)
{
	int fd;
	int i;

	i = 0;
	fd = open("text.txt", O_RDONLY);
	while (i < 8)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
}