package main

import "fmt"

func main() {
	var p *int = new(int)
	*p = 555

	fmt.Printf("%v\n", *p)
}
