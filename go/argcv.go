package main

import "fmt"
import "os"

func main() {
	list := os.Args
	n := len(list)
	fmt.Println(n)

	for _, data := range os.Args {
		fmt.Println(data)
	}
}
