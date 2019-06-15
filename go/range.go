package main

import "fmt"

func main() {
	var str1 = "123"

	for i:=0; i<len(str1); i++ {
		fmt.Printf("str1[%d]:%c\n", i, str1[i])
	}

	for i, data := range str1 {
		fmt.Printf("str1[%d]:%c\n", i, data)
	}

	for i := range str1 {
		fmt.Printf("str1[%d]:%c\n", i, str1[i])
	}
}
