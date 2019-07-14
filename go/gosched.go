package main

import (
	"fmt"
	"runtime"
	"time"
)

func main () {
	go func() {
		for i:=0;i<10;i++ {
			fmt.Println("go")
			time.Sleep(time.Second)
		}
	}()

	for i:=0;i<15;i++ {
		if i==0 {
			runtime.Gosched()
			fmt.Println("run gosched")
		}
		fmt.Println("main")
		time.Sleep(time.Second)
	}
}


