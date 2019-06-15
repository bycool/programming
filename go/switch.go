package main

import "fmt"

func main() {
/*
	var a byte 

	fmt.Scanf("%c", &a)
	fmt.Printf("a: %c\n", a)

	switch a {
		case 'a':
			fmt.Println("a=a")
		case 'b':
			fmt.Println("a=b")
		case 'c':
			fmt.Println("a=c")
		default:
			fmt.Println("default")
	}
*/
	var b byte

	fmt.Scanf("%c", &b)
	fmt.Printf("b: %c\n", b)

	switch b {
		case '1':
			fmt.Println("b=1")
			fallthrough
		case '2':
			fmt.Println("b=2")
			fallthrough
		case '3':
			fmt.Println("b=3")
			fallthrough
		default:
			fmt.Println("default")
	}
}
