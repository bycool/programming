#!/bin/sh


init_path=`pwd`


install(){
	sleep 1
	echo -e "\033[31m *****  install()  *****\033[0m"
	osinfo=`cat /etc/redhat-release | grep "Red"`
	os=$?
	rm ff.ko -f
	cp ./ff/$os/ff.$(uname -r).ko ./ff.ko
	insmod ff.ko
	mkdir -p /mnt/debugfs
	mount -t debugfs debugfs /mnt/debugfs

	cd $init_path/run/
	./fzsweb -s
#	echo -e "\033[31m ** install() **\033[0m"
}

uninstall(){
	sleep 1
	echo -e "\033[31m ***** uninstall() *****\033[0m"
	cd $init_path/run/
	./fzsweb -q
	cd $init_path
	rmmod ff.ko
	umount debugfs
	rmdir /mnt/debugfs
#	echo -e "\033[31m ** uninstall() **\033[0m"
}


main(){
	echo -e "\033[31m [start test] \033[0m"
	i=0
	while [ $i -le 2 ]
	do
		install
		uninstall
		echo -e "\033[31m                                                      [round $i done]\n\033[0m"
		let i++
	done
	echo -e "\033[31m [done round $i test] \033[0m"
}

main
