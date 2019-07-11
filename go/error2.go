package main

import "fmt"
import "errors"

func mydiv(a, b int)(result int, err error) {
	err = nil

	if b == 0 {
		err = errors.New("fenzi buneng dengyu 0")
	} else {
		result = a/b
	}
	return
}

func main () {
	result, err := mydiv(6,0)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(result)
	}
}
