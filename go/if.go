package main

import "fmt"

func main() {
	s := "123"

	if s == "123" {
		fmt.Println("s=123")
	}

	if a:=1; a==1 {
		fmt.Println("a==1")
	}

	var b int
	fmt.Scan(&b)
	fmt.Printf("b: %d\n", b)

	if b == 1 {
		fmt.Println("b=1")
	}else if b == 2 {
		fmt.Println("b=2")
	}
}
