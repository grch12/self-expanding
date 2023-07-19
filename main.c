#define EXE_FILE_ORIGINAL_SIZE (size_t)360337

#include <stdio.h>
#include <stdlib.h>

#include "zip.h"

#include "fileutils.h"

int main(int argc, char **argv)
{
    FILE *this_exe = fopen(argv[0], "rb");
    if (this_exe == NULL)
    {
        puts("Error when opening file.");
        puts(strerror(errno));
        exit(1);
    }

    fseek(this_exe, EXE_FILE_ORIGINAL_SIZE, SEEK_CUR);
    size_t zip_size = file_size(this_exe) - EXE_FILE_ORIGINAL_SIZE;
    void *data = malloc(zip_size);
    fread(data, zip_size, 1, this_exe);

    char tmp_filename[L_tmpnam];
    tmpnam(tmp_filename);
    FILE *tmp_zip = fopen(tmp_filename, "wb+");
    fwrite(data, zip_size, 1, tmp_zip);
    fclose(tmp_zip);

    char *dir_name;
    if (argc > 1)
        dir_name = argv[1];
    else
        dir_name = ".";
    
    zip_extract(tmp_filename, dir_name, NULL, NULL);


    return 0;
}