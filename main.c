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
        puts("���ļ�ʱ����");
        puts(strerror(errno));
        exit(1);
    }

    fseek(this_exe, EXE_FILE_ORIGINAL_SIZE, SEEK_CUR);
    size_t zip_size = file_size(this_exe) - EXE_FILE_ORIGINAL_SIZE;

    if (zip_size == 0)
    {
        puts("*ʹ�÷���*\n\
        ��zip�ļ�������ӵ����ļ�ĩβ���ɡ�\n\n\
        Windows:\n\
        cmd /c copy /b ���ļ��� + zip�ļ��� ����ļ���\n\n\
        ��UNIX����ϵͳ:\n\
        cat zip�ļ��� >> ���ļ���\n\n\
        *ע�⣺�ڶ��ַ����Ḳ��ԭʼ�ļ�������ǰ���ݣ�\n\
        Windows CMD������ʱ�������.exe��չ��������ᱨ��`No such file or directory`\n\n\
        ��ѹʱ��ֱ�����б��ļ���Ĭ�Ͻ��ļ���ȡ����ǰĿ¼��Ҳ��ͨ�������в���ָ����ѹλ��\n\n\
        �밴������˳�...");
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