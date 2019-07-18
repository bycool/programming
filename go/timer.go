package main

import (
	"fmt"
	"time"
)

func main () {
	fmt.Println("now: ", time.Now())
	timer := time.NewTimer(2*time.Second)  //定时向time的管道内写入数据(当前时间)
	t := <-timer.C  // 此处会阻塞，timer.C是channel
	fmt.Println("t: ", t)
}

