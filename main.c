#include "get_next_line.h"
#include "stdio.h"
#include <fcntl.h>

int	main(void)
{
	int fd;
	int i;
	char *aux;
	i = 0;
	fd = open("text.txt", O_RDONLY);
	while (i < 25)
	{
		aux = get_next_line(fd);
		printf("%s", aux);
		if (aux != NULL)
		{
			free(aux);
		}

		i++;
	}
	close(fd);
}