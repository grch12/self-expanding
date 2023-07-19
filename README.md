# 自解压工具

## 使用方法
将zip文件内容添加到本文件末尾即可。

Windows:
```bat
cmd /c copy /b 本文件名 + zip文件名 输出文件名
```

类UNIX操作系统:
```sh
cat zip文件名 >> 本文件名
```

*注意：第二种方法会覆盖原始文件，请提前备份！
Windows CMD下运行时，请添加.exe扩展名，否则会报错`No such file or directory`！

解压时，直接运本文件会默认将文件提取到当前目录，也可通过命令行参数指定解压位置。

## 编译指南
1. 确保你的设备上安装了`make`工具。
2. 编辑`makefile`，将`CC`和`LINKER`分别改为你使用的编译器与链接器。
3. 执行`make everything`。
4. 查看生成的可执行文件的大小（字节数），编辑`main.c`，将其中的`EXE_FILE_ORIGINAL_SIZE`宏改为此值。
5. 再次执行`make everything`

*为了在Windows平台上不出现乱码，本项目使用GBK编码，若在其他平台上编译，请先转换编码*