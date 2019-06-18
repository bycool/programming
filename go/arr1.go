package main

import "fmt"

func display(args [5]int) {
	for _, data := range args {
		fmt.Printf("%d,", data)
	}
	fmt.Printf("\b \n")
}

func main() {
	var arr [5]int = [5]int{5,3,4,2,1 }
	display(arr)
}
