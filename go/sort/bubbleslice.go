package main

import "fmt"

func display(arr []int){
	for _, va:= range arr {
		fmt.Printf("%d,", va)
	}
}

func bubblesort(arr []int){
	var tmp int = 0
	for i:=0; i<len(arr); i++ {
		for j:=1; j<len(arr); j++ {
			if arr[j] < arr[j-1] {
				tmp = arr[j]
				arr[j] = arr[j-1]
				arr[j-1] = tmp
			}
		}
	}
}

func main () {
//	arr := make([]int)
	arr := []int{}

	fmt.Println(arr)

	arr = append(arr, 4)
	arr = append(arr, 2)
	arr = append(arr, 5)
	arr = append(arr, 3)
	arr = append(arr, 1)
	fmt.Println(arr)

	bubblesort(arr)
	fmt.Println(arr)
}
