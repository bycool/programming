package main

import "fmt"

func main(){
	var f1 float32
	f1 = 3.14
	fmt.Println(f1)

	var f2 = 3.14
	fmt.Printf("f2: %g, %T\n", f2, f2)  //float64
}
