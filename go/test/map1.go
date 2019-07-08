package main

import "fmt"

func main () {
	var a map[int]string
	a = make(map[int]string)
	a[1] = "str1"
	a[2] = "str2"
	a[3] = "str3"
	a[4] = "str4"
	a[5] = "str5"
	a[6] = "str6"

	delete(a, 1)

	fmt.Println(a)

	
}
