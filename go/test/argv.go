package main

import (
	"fmt"
	"os"
)

func main() {
	for i,argvs := range os.Args {
		fmt.Println(i, argvs)
	}
}

