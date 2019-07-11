package main

import "fmt"

import "errors"

func main() {
	err1 := fmt.Errorf("%s", "1")
	fmt.Println("err1 = ", err1)

	err2 := errors.New("err2")
	fmt.Println("err2 = ", err2)
}
