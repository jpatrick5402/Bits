#include <stdio.h>
#include <stdlib.h>

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

    int byteCount = 0;
    unsigned char byte;
    while (fread(&byte, sizeof(byte), 1, fptr) == 1)
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
    fclose(fptr);
    return 0;
}