#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my_string.h"

stream_t *string_init()
{
    stream_t *stream = (stream_t *)(malloc(sizeof(stream_t)));
    stream->limit = BUF_SIZE;
    stream->str = (char *)malloc((stream->limit)*sizeof(char));
    stream->size = 0;
    return stream;
}

stream_t        *string_create(char* str)
{
    stream_t *string;
    string = string_init();
    string_append(string, str);
    return string;
}

void string_append(stream_t *ptr, char* str)
{
    int size = 0;
    if (ptr == NULL)
        ptr = string_create(str);
    else
    {
        size = strlen(str);
        if (ptr->size + size >= ptr->limit)
        {
            ptr->limit += size + 1;
            ptr->str = (char *)realloc(ptr->str, ptr->limit);
            ptr->str[ptr->size + size] = '\0';
        }
        for (int i = 0; i < size; i++)
            ptr->str[ptr->size + i] = str[i];
        ptr->size += size;
        ptr->str[ptr->size] = '\0';
    }

}

void string_destroy(stream_t *str)
{
    free(str->str);
    free(str);
}

