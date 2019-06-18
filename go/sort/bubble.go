package main

import  "fmt"

func display(arr [5]int) {
	for _,data := range arr {
		fmt.Printf("%d\n",data)
	}
}


func main() {
	var arr [5]int = [5]int{3,4,2,5,1}
	var tmp int = 0

	for i:=0; i<5; i++ {
		for j:=0; j<4; j++ {
			if arr[j] > arr[j+1] {
				tmp = arr[j]
				arr[j] = arr[j+1]
				arr[j+1] = tmp
			}
		}
	}


	display(arr)
}
