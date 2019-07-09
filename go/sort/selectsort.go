package main

import "fmt"

func selectsort(arr []int) {
	var tmp int
	for i:=0; i<len(arr); i++ {
		min := i
		for j:=i; j<len(arr); j++ {
			if arr[j] < arr[min] {
				min = j
			}
		}
		if min != i {
			tmp = arr[min]
			arr[min] = arr[i]
			arr[i] = tmp
		}
	}
}

func main () {
	arr := []int{4,2,3,5,1}
	selectsort(arr)
	fmt.Println(arr)
}
