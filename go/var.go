package main

import "fmt"

func test()(a, b, c int){
	return 1, 2, 3
}

func main() {
	var a int
	a = 10
	fmt.Printf("a:%d\n", a);
	fmt.Printf("a:%T\n", a);

	b := 20
	fmt.Printf("b:%d\n", b);
	fmt.Printf("b:%T\n", b);

	c := b
	fmt.Printf("c:%d\n", c);
	fmt.Printf("c:%T\n", c);

	i, j := 10, 20
	fmt.Printf("i:%d, j:%d\n", i, j);

	k, _ := i, j
	fmt.Printf("k: %d\n", k)

	x, y, z := test();
	fmt.Println("x: ", x);
	fmt.Println("y: ", y);
	fmt.Println("z: ", z);

	y, z, _ = test()
	fmt.Println("x: ", x);
	fmt.Println("y: ", y);
	fmt.Println("z: ", z);
}
