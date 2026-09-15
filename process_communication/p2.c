#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct shared_data {
    int turn;
    char msg[256];
};

int main() {
    int shmid = shmget(1234, sizeof(struct shared_data), 0666);
    struct shared_data *shm = shmat(shmid, NULL, 0);
    
    while (1) {
        while (shm->turn != 2); 
        
        printf("P1: %s", shm->msg);
        
        printf("You: ");
        fgets(shm->msg, 256, stdin);
        shm->turn = 1;          
    }
}