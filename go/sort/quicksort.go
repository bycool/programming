package main

import "fmt"

func swap(a, b int) (int, int) {
	return b, a
}

func quicksort(arr []int, b, e int) {
	var bb, ee int = b, e
	var tmp int = arr[b]

	if b >= e || b<0 || e>=len(arr) {
		return
	}

	for bb < ee{
		for arr[ee] >= tmp && bb < ee {
				ee--
		}	
		for arr[bb] <= tmp && bb < ee {
				bb++
		}

		arr[bb], arr[ee] = swap(arr[bb], arr[ee])
	}

	arr[b], arr[bb] = swap(arr[b], arr[bb])

	quicksort(arr, b, bb-1)

	if ee+1 >= len(arr){
		return
	}

	quicksort(arr, ee+1, e)
}

func main () {
	arr := []int{5,7,3,8,2,1,9,0,6,4}
	quicksort(arr, 0, 9)

	fmt.Println(arr)
}
