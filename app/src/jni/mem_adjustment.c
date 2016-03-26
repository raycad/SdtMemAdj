#include <jni.h>
#include "sdt_list.h"

struct OneMB {
    int bytes[256*1024]; // 4*256*1024 Bytes = 1MB
};
struct sdt_list *mem_list = 0;

jint Java_com_seedotech_sdtmemadj_MainActivity_nativeInitMemAdj(JNIEnv* env, jobject thiz)
{
    mem_list = sdt_list_create();
    return 1;
}

jint Java_com_seedotech_sdtmemadj_MainActivity_nativeIncreaseMem(JNIEnv* env, jobject thiz, jint mb_size)
{
    int size, i;
    for (i = 0 ; i < mb_size; ++i) {
        struct OneMB *oneMB = (struct OneMB *)malloc(sizeof(struct OneMB));
        size = sdt_list_add(mem_list, oneMB);
        if (size < 1)
            break;
    }
    return size;
}

jint Java_com_seedotech_sdtmemadj_MainActivity_nativeDecreaseMem(JNIEnv* env, jobject thiz, jint mb_size)
{
    int size, i;
    for (i = 0 ; i < mb_size; ++i) {
        size = sdt_list_destroy_first_node(mem_list);
        if (size < 1)
            break;
    }
    return size;
}

jint Java_com_seedotech_sdtmemadj_MainActivity_nativeDeInitMemAdj(JNIEnv* env, jobject thiz)
{
    sdt_list_destroy_list_data(mem_list);
    return 1;
}