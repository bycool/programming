package main

import "fmt"

func insertsort(arr []int) {
	var tmp, i, j int
	for i=0; i<len(arr); i++ {
		tmp = arr[i]
		for j=i; j>0 && arr[j-1]>tmp; j-- {
			arr[j] = arr[j-1]
		}
		arr[j] = tmp
	}
}

func main () {
	arr := []int{3,4,2,5,1}
	insertsort(arr)
	fmt.Println(arr)
}
