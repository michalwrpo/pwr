// boot.c

void delay(unsigned long count) {
    while (count--) {
        __asm__ volatile ("");
    }
}

void main() {
    char *video_memory = (char*) 0xB8000;
    char *message = "Hello, World!";
    
    for (int i = 0; i < 80*25; i++) {
        video_memory[2 * i] = ' ';
        video_memory[2 * i + 1] = 0x0;
    }

    for(int j = 0; j < 256; j++) {
        unsigned char color = j;
        for (int i = 0; message[i] != '\0'; i++) {
            video_memory[(j % 25) * 160 + i * 2] = message[i];
            video_memory[(j % 25) * 160 + i * 2 + 1] = color;
            delay(1000000);
        }
    }
    
    while(1);
}
