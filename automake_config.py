#!/usr/bin/python
#   coding: UTF-8
#   author: XuZhiXi
#   create Time: 2012-09-17 00:16:25


#user global set
g_program_type = 2          # 1 表示一般程序, 2 表示动态库, 3 表示静态库
g_handle_subdir = True  # 是否递归对子目录进行编译链接
g_except_dir_list = ["ky_test"]  # 不进行编译链接处理的目录, 仅当g_handle_subdir设置为True时才有效
g_except_file_list = [] # 不进行编译链接处理的文件

g_bin_name = "libky.so" # 生成程序名或动态库名或静态库名
g_debug_bin_name = "libky.so" # 执行make debug时生成的程序名

g_compilers_opt = "-W -Wall -Wpointer-arith -pipe -D_REENTRANT -O3" # 编译选项
g_debug_compilers_opt = "-W -Wall -Wpointer-arith -pipe -D_REENTRANT"   # debug的编译选项

g_include_opt = ""  # 包含的头文件选项
g_libs_opt = "-lpthread -L/usr/lib/mysql -lmysqlclient" # 包含的动态库选项

g_ar_opt = "" # 编译静态库时, ar命令的选项

# install执行命令列表
g_install_commands = ["echo 'install command not set'"]

