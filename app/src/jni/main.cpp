#include <stdio.h>
#include <cstdlib>
#include "sdt_list.h"

#define MEM_BLOCK 1024
struct OneMB {
    int bytes[256*1024]; // 4*256*1024 Bytes = 1MB
};
struct sdt_list *mem_list = 0;

int main()
{
    int size, i;
    for (i = 0 ; i < MEM_BLOCK; ++i) {
        struct OneMB *oneMB = (struct OneMB *)malloc(sizeof(struct OneMB));
        if (!oneMB)
            break;
        size = sdt_list_add(mem_list, oneMB);
        if (size < 1)
            break;
    }

    return 0;
}