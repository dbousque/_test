

#include "mlx.h"
#include <unistd.h>

int	main()
{
	void *lol = mlx_init();
	mlx_new_window(lol, 400, 400, "hello");
	sleep(3);
	return (0);
}
