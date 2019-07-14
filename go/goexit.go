package main

import (
	"fmt"
	"runtime"
)

func test() {
	defer fmt.Println("ccccccccc")
	runtime.Goexit()  //退出线程， 线程销毁，不会有下次调用了。
	// return  //返回函数，在下次线程调用函数依然在这里返回。
	fmt.Println("ddddddddddd")
}

func main () {
	go func(){
		fmt.Println("aaaaaaaaaaa")
		test()
		fmt.Println("bbbbbbbbbbb")
	}()

	for {

	}
}
