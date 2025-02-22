#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

int main() {
    // Generate a unique key for the shared memory segment
    key_t key = ftok("shmfile", 65);
    
        int status;
    // Create a shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the address space of the process
    char *shared_memory = (char*) shmat(shmid, NULL, 0);
    if (shared_memory == (char*) -1) {
        printf("%d %s shmat", __LINE__,strerror(errno));
        exit(1);
    }

    // Write data to the shared memory segment
    strcpy(shared_memory, "Hello, World!");

    // Print the data written to the shared memory segment
//    printf("Data written to shared memory: %s\n", shared_memory);

    // Detach the shared memory segment from the address space of the process
    if (shmdt(shared_memory) == -1) {
        printf("%d %s shmdt", __LINE__,strerror(errno));
        exit(1);
    }

    // Create a child process to read data from the shared memory segment
    pid_t pid = fork();
    if (pid == -1) {
        printf("%d %s fork", __LINE__,strerror(errno));
        exit(1);
    } else if (pid == 0) {
        // Child process
	    fflush(stdout);
        fprintf(stdout,"\nData read from shared memory by child process2\n");

        // Attach the shared memory segment to the address space of the child process
        shared_memory = (char*) shmat(shmid, NULL, 0);
        if (shared_memory == (char*) -1) {
            printf("%s %d shmat",strerror(errno),__LINE__);
            exit(1);
        }

    //strcpy(shared_memory, "Hello, World2!");

        // Read and print the data from the shared memory segment
	
        fprintf(stdout, "Data read from shared memory by child process2: %s\n", shared_memory);
        if (shmdt(shared_memory) == -1) {
            printf("%s %d shmdt",strerror(errno),__LINE__);
            exit(1);
        }

        // Detach the shared memory segment from the address space of the child process
	fflush(stdout);
        exit(0);
    } else {
        // Parent process waits for the child process to finish
	        // Remove the shared memory segment
//        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
  //          perror("shmctl");
    //        exit(1);
      //  }
	shmdt(shared_memory);
	wait(&status);
	printf("status:%d\n",status);
	if(WIFSIGNALED(status)) {
		printf("Child died");
		if(WTERMSIG(status) == SIGSEGV) {
			printf("Child died with seg fault");
		}
	}
	printf("Wait complete \n");

    }

    return 0;
}

