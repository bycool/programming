package main

import "fmt"

func main() {
	var a  int
	fmt.Scan(&a)
	fmt.Println(a)

	fmt.Scanf("%d", &a)
	fmt.Println(a)
	fmt.Printf("%d\n", a)

	var s string
	fmt.Scan(&s)
	fmt.Println(s)
}
