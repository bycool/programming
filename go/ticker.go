package main

import (
	"fmt"
	"time"
)

func main () {
	ticker := time.NewTicker(1*time.Second)

	i := 0
	for {
		i++
		<-ticker.C
		fmt.Println(i)

		if i == 6 {
			break
		}
	}
}
