package main

import (
	"fmt"
	"time"
)

func main () {
	timer := time.NewTimer(2*time.Second)

	go func () {
		<-timer.C //主线程设置两秒timer，但紧接着把timer stop了，那么2秒后timer.C不会被写入数据，这里就一直阻塞。
		fmt.Println("child.println")
	}()

	timer.Stop()
	
	for {
//		time.Sleep(5*time.Second)
//		break
	}
}
