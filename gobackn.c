#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#define WINDOW_SIZE 4
#define TOTAL_PACKETS 10
#define TIMEOUT 3
void send_packet(int packet) {
    printf("Sending packet %d\n", packet);
}
bool receive_ack(int packet) {
    return rand() % 2; 
}
int main() {
    srand(time(0));
    int base = 0, next_seq_num = 0;
    
    while (base < TOTAL_PACKETS) {
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_PACKETS) {
            send_packet(next_seq_num);
            next_seq_num++;
        }
        
        sleep(TIMEOUT);
        for (int i = base; i < next_seq_num; i++) {
            if (receive_ack(i)) {
                printf("ACK received for packet %d\n", i);
                base++;
            } else {
                printf("Timeout: Resending from packet %d\n", base);
                next_seq_num = base; 
                break;
            }
        }
    }
    printf("All packets sent successfully!\n");
    return 0;
}
