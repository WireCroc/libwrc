#include "utils.h"

void todo(FILE *f, const char *text, int code)
{
    fprintf(f, text, 0);
    exit(code);
}

char *wc_format(const char *text, ...)
{
    static char buffers[MAX_TEXTFORMAT_BUFFERS][MAX_TEXT_BUFFER_LENGTH] = {0};
    static int index = 0;

    char *currentBuffer = buffers[index];
    memset(currentBuffer, 0, MAX_TEXT_BUFFER_LENGTH);

    va_list args;
    va_start(args, text);
    vsnprintf(currentBuffer, MAX_TEXT_BUFFER_LENGTH, text, args);
    va_end(args);

    index += 1;
    if (index >= MAX_TEXTFORMAT_BUFFERS)
        index = 0;

    return currentBuffer;
} // format text
