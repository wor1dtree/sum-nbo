#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>

int sumNbo(int argc, char* argv[]){
    uint32_t total = 0;

    for (int i = 1; i != argc; i++) {

        FILE* fp = fopen(argv[i], "r");

        if (fp == NULL) {
            printf("\nfail fopen() {%s}", argv[i]);
            return -1;
        }

        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);
        if (size != 4) {
            printf("\nworng filesize {%s}", argv[i]);
            fclose(fp);
            return -1;
        }
        fseek(fp, 0, SEEK_SET);

        uint32_t num;
        fread(&num, sizeof(uint32_t), 1, fp);
        num = htonl(num);
        total += num;
        printf("%u(0x%08x) ", num, num);

        fclose(fp);

        if (i != argc - 1) {
            printf("+ ");
        }
        else {
            printf("= %u(0x%08x)", total, total);
        }

    }

    return 0;
}



int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("usage : sum-nbo <file1> [<file2>...]");

        return -1;
    }

    sumNbo(argc, argv);

    return 0;
}
