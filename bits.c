#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help() {
    printf("bits <FILEPATH> [-r,-v,-h]\n");
}

void print_raw(FILE * file_pointer) {
	char * bitString;
    unsigned char byte;
    while (fread(&byte, sizeof(byte), 1, file_pointer) == 1) {
        for (int i = 7; i >= 0; i--) {
			bitString = bitString + (byte >> i);
            printf("%d", (byte >> i) & 1); // Print bit
        }
        printf("\n");
    }
    fclose(file_pointer);
}

void print_verbose(FILE * file_pointer) {
    int byteCount = 0;
    unsigned char byte;
    while (fread(&byte, sizeof(byte), 1, file_pointer) == 1)
    {
        printf("Byte #: %-10d ", byteCount); // Index of Byte

        printf("0x%02x ", byte); // Print Hex

        for (int i = 7; i >= 0; i--)
        {
            printf("%d", (byte >> i) & 1); // Print bit
        }

        if (byte == '\n')
            printf(" \\n      ");
        else if (byte == '\t')
            printf(" \\t       ");
        else if (byte == '\r')
            printf(" \\r       ");
        else if (byte == ' ')
            printf(" [space] ");
        else
            printf(" %c       ", byte); // Print ASCII Value

        if ((byteCount + 1) % 5 == 0)
            printf("\n");

        byteCount = byteCount + 1;
    }
    printf("\n");
    fclose(file_pointer);
}

int main(int argc, char *argv[])
{
    FILE *fptr;
    if (!argv[1])
    {
        printf("Enter file path to read: ");
        char answer[1000];
        scanf("%s", answer);
        fptr = fopen(answer, "rb");
    }
    else
    {
        fptr = fopen(argv[1], "rb");
    }

    if (strcmp(argv[2], "-h") == 0) {
        print_help();
    } else if (strcmp(argv[2], "-r") == 0) {
        print_raw(fptr);
    } else if (strcmp(argv[2], "-v") == 0) {
        print_verbose(fptr);
    } else {
        printf("argument not recognized: %s\n", argv[2]);
    }

    return 0;
}
