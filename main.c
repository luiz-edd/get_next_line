#include "get_next_line.h"
#include "stdio.h"
#include <fcntl.h>

int	main(void)
{
	int fd;
	int i;
	char *line;

	i = 0;
	fd = open("text.txt", O_RDONLY);
	while (i < 100)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line != NULL)
			free(line);

		i++;
	}
	close(fd);
}