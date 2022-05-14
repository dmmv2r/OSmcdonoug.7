#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

   if(argc < 2) { //detects if only ./chain is inputted
      printf("Not enough arguments given\n");
      printf("Issue command './chain -h' for help\n");
      return -1;
   }

   int opt;
   int nprocs;
   int nchars;
   int sleeptime;
   int niters;
   int iflag; //i is a required argument, this is a flag for if it is given

   //default argument values
   nprocs = 4;
   nchars = 80;
   sleeptime = 3;
   niters = -1;
   iflag = 0;

   while((opt = getopt(argc, argv, "hp:c:s:i:")) != -1) {
      switch(opt) {
         case 'h':
            printf("Usage: './chain -h -p w -c x -s y -i z'\n");
            printf("w = number of processes (default 4)\n");
            printf("x = number of characters to read (default 80)\n");
            printf("y = time to sleep in each iteration (default 3s)\n");
            printf("z = number of iterations in loop (REQUIRED)\n");
            return -1;
         case 'p':
            nprocs = atoi(optarg);
            if(nprocs < 1) {
               printf("-p must be positive\n");
               return -1;
            }
            break;
         case 'c':
            nchars = atoi(optarg);
            if(nchars < 1) {
               printf("-c must be positive\n");
               return -1;
            }
            break;
         case 's':
            sleeptime = atoi(optarg);
            if(sleeptime < 0) {
               printf("-s must be at least 0\n");
               return -1;
            }
            break;
         case 'i':
            niters = atoi(optarg);
            if(niters < 1) {
               printf("-i must be positive\n");
               return -1;
            }
            iflag = 1;
            break;
         default:
            printf("%s: Error: ", argv[0]);
            perror("Default getopt hit");
            printf("invalid argument entered into getopt\n");
            return -1;
      }
   }

   if(iflag == 0) { //checks to see if -i is given
      printf("-i is a required argument\n");
      return -1;
   }


   char mybuf[nchars]; //part 8 variables
   int l;

   //chain code modified slightly
   pid_t childpid = 0;
   int i;
   for(i = 1; i < nprocs; i++) {
      if((childpid = fork())) {
         break;
      }
   }
   
   int j;
   for(j = 0; j < niters; j++) {
      //sleep(sleeptime);
      wait(NULL);
      //fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)childpid);

      /*fprintf(stderr, "i:%d ", i);
      fprintf(stderr, "process ID: %ld ", (long)getpid());
      fprintf(stderr, "parent ID: %ld ", (long)getppid());
      fprintf(stderr, "child ID: %ld\n", (long)childpid);
      */

      //part 8 code
      printf("Input string\n");
      for(l = 0; l < nchars; l++) {
         mybuf[l] = getchar();
      }
      mybuf[nchars] = '\0';
      printf("%s\n", mybuf);
   }
   
   return 0;
}
