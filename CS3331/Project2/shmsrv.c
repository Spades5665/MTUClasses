#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <wait.h>

int main(int argc, char *argv[])
{
   key_t              ShmKEY;
   int                ShmID, i;
   int                **points;
   int                pixels;
   int                arraysize;
   unsigned long long rowstart;
   int                j;
   int                cpid;
   int                estatus;

   //-- Points array dimension.
   pixels=5;

   //-- Setting up a shared memory segment
   ShmKEY = ftok("./", 'x');
   arraysize=sizeof(int *)*pixels + sizeof(int)*pixels*pixels;
   ShmID = shmget(ShmKEY, arraysize,
                  IPC_CREAT | 0666);

   //-- We'll access the shared memory through this variable.
   points = (int **) shmat(ShmID, NULL, 0);
   printf("Shared start: %p sizeof(int *) %d  sizeof(int) %d\n",points,sizeof(int *),sizeof(int));

   //-- Child will fill in the array.  We'll wait for the child.
   //   Then we know it is safe to read the values written by the child.
   //
   cpid=fork();
   if (cpid==0){
       execlp("./shmcli","shmcli",(char *)0);
       exit(1);
   }
   wait(&estatus);

   //-- Shared memory block contains row pointers and rows of integers.
   //-- Row pointers at lowest address.                                     
   //          Pointers occupy pixels*sizeof(int *)                         
   //-- Row values next.                                                    
   //          Each row occupies pixels*sizeof(int) bytes                   
   //-- So row 0 values start at address points+pixels*sizeof(int *)
   //      row X values at (points+pixels*sizeof(int *)+ X*pixels(sizeof (int))
   //
   for (i=0;i<pixels;i++){
       rowstart=(unsigned long long)points+pixels*sizeof(int *)+i*pixels*sizeof(int);
       points[i]=(int *)rowstart;
       printf("[%d]Row %d at address %p. Stored at %p\n",getpid(),i,points[i],&points[i]);
     }

   //
   //-- Read values written by the child
   //
   for (i=0;i<pixels;i++)
     for (j=0;j<pixels;j++)
       printf("[%d]pixels[%d][%d]=%d at address <%p>\n",getpid(),i,j,points[i][j],&points[i][j]);

   
   shmdt((void *) points);
   shmctl(ShmID, IPC_RMID, NULL);
   exit(0);
}

