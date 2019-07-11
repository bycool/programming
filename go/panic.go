package main

import "fmt"

func testa() {
	fmt.Println("aaaaaaaaaaaaaa")
}
func testb(x int) {
	fmt.Println("bbbbbbbbbbbbbb")
	var a [10]int
	a[x] = 1 //越界会默认调用panic
}
func testc() {
	fmt.Println("cccccccccccccc")
	panic("this is a panic test")  //此处会直接让程序崩溃，之后的调用就不会执行了。
	fmt.Println("ccccccccccccc")
}

func main () {
	testa()
	testb(11)
//	testc()
}
