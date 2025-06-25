#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

int main(int argc, char *argv[])
{
   key_t              ShmKEY;
   int                ShmID;
   int                i,j;
   int                **points;
   int                pixels;
   int                arraysize;
   unsigned long long rowstart;
   
   pixels=5;
   ShmKEY = ftok("./", 'x');
   arraysize=sizeof(int *)*pixels + sizeof(int)*pixels*pixels;
   ShmID = shmget(ShmKEY, arraysize, 0666);  
   points = (int **) shmat(ShmID, NULL, 0);
   for (i=0;i<pixels;i++)
     {
       rowstart=(unsigned long long)points+pixels*sizeof(int *)+i*pixels*sizeof(int);
       points[i]=(int *)rowstart;
       printf("[%d]Row %d at address %p. Stored at %p\n",getpid(),i,points[i],&points[i]);
     }
   //-- Fill in the array
   for (i=0;i<pixels;i++)
     for (j=0;j<pixels;j++)
       points[i][j]=i*3+j;
     
   shmdt((void *) points);
   exit(0);
}

