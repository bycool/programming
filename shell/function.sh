#/usr/bin/sh

# 方法不被按顺序执行，只有被调用时才会执行。

printe(){
	echo printe;
}

if [ $1 = 1 ]; then
	printe
fi
