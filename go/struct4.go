package main

import "fmt"

type node struct {
	id int
	name string
	age int
}

func main() {
	s1 := node{1,"jia", 18}	
	s2 := node{1,"jia", 18}	
	s3 := node{2,"jia", 18}
	s4 := node{3,"j", 19}
	fmt.Println("s1==s2", s1==s2)
	fmt.Println("s1==s3", s1==s3)

	fmt.Println("s4: ", s4)
	s4 = s3
	fmt.Println("s4: ", s4)
}
