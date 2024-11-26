#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_SIZE 4
#define TOTAL_PACKETS 10
#define TIMEOUT 3

bool received_acks[TOTAL_PACKETS];

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
        // Send packets within the window
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_PACKETS) {
            if (!received_acks[next_seq_num]) {
                send_packet(next_seq_num);
            }
            next_seq_num++;
        }
        
        sleep(TIMEOUT); // Simulate waiting for ACKs
        
        // Check for acknowledgments and retransmit lost packets
        for (int i = base; i < next_seq_num; i++) {
            if (!received_acks[i] && receive_ack(i)) {
                printf("ACK received for packet %d\n", i);
                received_acks[i] = true;
            } else if (!received_acks[i]) {
                printf("Timeout: Resending packet %d\n", i);
                send_packet(i); // Resend only the lost packet
            }
        }
        
        // Slide window
        while (received_acks[base] && base < TOTAL_PACKETS) {
            base++;
        }
    }
    printf("All packets sent successfully with selective repeat!\n");
    return 0;
}
