#/usr/bin/sh

# read -p : 在read命令行指定提示符.
#      -s : 隐藏输入。输入的password不被显示出来。

read -s -p "input root password:" password

echo $password
