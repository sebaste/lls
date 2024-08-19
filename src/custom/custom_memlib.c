#include "custom_memlib.h"

void *custom_memset(void *buffer, int value, size_t length)
{
    unsigned char *byte_ptr = (unsigned char *)buffer;
    unsigned char byte_value = (unsigned char)value;

    while (length--)
    {
        *byte_ptr++ = byte_value;
    }

    return buffer;
}

void *custom_memcpy(void *destination, const void *source, size_t nm_bytes)
{
    unsigned char *dest_ptr = (unsigned char *)destination;
    const unsigned char *src_ptr = (const unsigned char *)source;

    while (nm_bytes--)
    {
        *dest_ptr++ = *src_ptr++;
    }

    return destination;
}
