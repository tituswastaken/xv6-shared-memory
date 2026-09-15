#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct shared_data {
    int turn;
    char msg[256];
};

int main() {
    int shmid = shmget(1234, sizeof(struct shared_data), IPC_CREAT | 0666);
    struct shared_data *shm = shmat(shmid, NULL, 0);
    
    shm->turn = 1; 
    
    while (1) {
        while (shm->turn != 1); 
        
        printf("You: ");
        fgets(shm->msg, 256, stdin);
        shm->turn = 2;          
        
        while (shm->turn != 1);
        printf("P2: %s", shm->msg);
    }
}