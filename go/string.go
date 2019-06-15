package main

import "fmt"

func main() {
	var str1 string = "123456"
	fmt.Println(str1)

	var str2 = "123456"
	fmt.Println(str2)

	str3 := "123456"
	fmt.Println(str3)

	fmt.Println(len(str1), len(str2), len(str3))
	fmt.Printf("str1.len: %d, str2.len: %d, str3.len: %d\n", len(str1), len(str2), len(str3))
}
