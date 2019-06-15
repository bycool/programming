package main

import "fmt"
import "time"

func main() {
	for i:=0; i<10; i++ {
		if i==3 {
//			break;
			continue
		}
		fmt.Println(i)
		time.Sleep(time.Second)
	}
	fmt.Println(time.Second)
}
