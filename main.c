#define EXE_FILE_ORIGINAL_SIZE (size_t)178881

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "zip.h"

#include "fileutils.h"

int main(int argc, char **argv)
{
    FILE *this_exe = fopen(argv[0], "rb");
    if (this_exe == NULL)
    {
        puts("打开文件时出错：");
        puts(strerror(errno));
        exit(1);
    }

    fseek(this_exe, EXE_FILE_ORIGINAL_SIZE, SEEK_CUR);
    size_t zip_size = file_size(this_exe) - EXE_FILE_ORIGINAL_SIZE;

    if (zip_size == 0)
    {
        puts("*使用方法*\n\
        将zip文件内容添加到本文件末尾即可。\n\n\
        Windows:\n\
        cmd /c copy /b 本文件名 + zip文件名 输出文件名\n\n\
        类UNIX操作系统:\n\
        cat zip文件名 >> 本文件名\n\n\
        *注意：第二种方法会覆盖原始文件，请提前备份！\n\
        Windows CMD下运行时，请添加.exe扩展名，否则会报错`No such file or directory`\n\n\
        解压时，直接运行本文件会默认将文件提取到当前目录，也可通过命令行参数指定解压位置\n\n\
        请按任意键退出...");
        getchar();
        exit(1);
    }

    void *data = malloc(zip_size);
    fread(data, zip_size, 1, this_exe);

    char *dir_name;
    if (argc > 1)
        dir_name = argv[1];
    else
        dir_name = ".";

    zip_stream_extract(data, zip_size, dir_name, NULL, NULL);
    free(data);

    return 0;
}