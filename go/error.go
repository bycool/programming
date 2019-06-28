package main

import "fmt"

func main() {
	err1 := fmt.Errorf("%s", "1")
	fmt.Println("err1 = ", err1)
}
