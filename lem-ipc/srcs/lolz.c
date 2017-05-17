

#include <semaphore.h>
#include <sys/shm.h>
#include <fcntl.h>
#define SHMSZ 27
#include <unistd.h>
#include <stdio.h>

int	main()
{
  int shmid;
  key_t key;
  char *shm;
  char *s;
  //char ch;
  sem_t *mutex;

  //name the shared memory segment
  key = 4242;

  //create & initialize semaphore
  mutex = sem_open("_sem_lemipc_board_", O_CREAT, 0644, 1);
  if(mutex == SEM_FAILED)
    {
      printf("unable to create or open semaphore\n");
      sem_unlink("_sem_lemipc_board_");
      return (0);
    }

  //create the shared memory segment with this key
  shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
  if(shmid<0)
    {
      printf("failure in shmget\n");
      return (0);
    }

  //attach this segment to virtual memory
  shm = shmat(shmid, NULL, 0);

  //start writing into memory
  s = shm;
  *s = '*';
  /*for(ch='A';ch<='Z';ch++)
    {
      sem_wait(mutex);
      *s++ = ch;
      sem_post(mutex);
    }

  //the below loop could be replaced by binary semaphore
  while(*shm != '*')
    {
      sleep(1);
    }
  sem_close(mutex);
  sem_unlink("_sem_lemipc_board_");
  shmctl(shmid, IPC_RMID, 0);*/

  return (0);
}