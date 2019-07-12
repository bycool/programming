package main

import (
	"fmt"
	"os"
)

func main () {
	//os.Stdout.Close()
	fmt.Println("hello")
	os.Stdout.WriteString("hello\n")
}
