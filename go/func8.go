package main

import "fmt"

func suma(a int) (int)  {
	if a == 0 {
		return 0
	}

	return a + suma(a-1)
}

func main() {
	var sum = suma(100)
	fmt.Println(sum)
}
