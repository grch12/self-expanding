#include "fileutils.h"

size_t file_size(FILE *file)
{
    fpos_t fpos;
    size_t n;
    fgetpos(file, &fpos);
    fseek(file, 0, SEEK_END);
    n = ftell(file);
    fsetpos(file, &fpos);
    return n;
}