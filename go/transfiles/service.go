package main

import (
	"fmt"
	"ioutil"
	"net"
	"os"
)
// op_code:
//                   
//  1 dir create     [1|op] [dirname]
//  2 file create    [1|op] [filename]
//  3 write          [1|op] [1|flienamelen][filename] [content]
//  4 chmod          [1|op] [1|filenamelen] [uint32]
//  5 chtimes
//  

type fc struct {
	type
}

func main () {
	
}
