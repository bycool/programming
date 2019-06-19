package main

import  "fmt"

func display(arr [5]int) {
	for _,data := range arr {
		fmt.Printf("%d\n",data)
	}
}

func main() {
	var arr [5]int = [5]int{3,4,2,5,1}
	display(arr)
}
