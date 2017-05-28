

# include <semaphore.h>
# include <sys/shm.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

int		main(void)
{
	int		shmid;
	void	*data;

	shmid = shmget(4242, 32, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);

	shmdt(data);

	shmid = shmget(4242, 32, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);

	shmdt(data);

	shmid = shmget(4242, 32, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);

	shmdt(data);

	shmid = shmget(4242, 32, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);

	shmdt(data);

	shmid = shmget(4242, 32, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);

	shmdt(data);

	shmid = shmget(4242, 32, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);

	shmdt(data);

	shmid = shmget(4242, 32, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);

	shmdt(data);

	shmid = shmget(4242, 32, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);

	shmdt(data);

	shmid = shmget(4242, 32, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	if (((char*)data)[0] != 1) {
		printf("ERROR\n");
		return (0);
	}
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);

	shmdt(data);

	shmid = shmget(4242, 32, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);

	shmdt(data);

	shmid = shmget(4242, 32, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);

	shmdt(data);

	shmid = shmget(4242, 32, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);

	shmdt(data);

	shmid = shmget(4242, 64, IPC_CREAT | 0666);
	printf("\nshmid : %d\n", shmid);
	data = shmat(shmid, NULL, 0);
	((char*)data)[0] = 1;
	((char*)data)[1] = 2;
	printf("data : %p\n", data);
	return (0);
}