package main

import (
	"fmt"
	"net"
)

func main () {
	listener, err := net.Listen("tcp", "127.0.0.1:8000")
	if err != nil {
		fmt.Println("listen err")
		return
	}

	defer listener.Close()

	conn, err := listener.Accept()
	if err != nil {
		fmt.Println("Accept err")
		return
	}

	defer conn.Close()
	
	buf := make([]byte, 1024)
	n, err1 := conn.Read(buf)
	if err1 != nil {
		fmt.Println("err1: ", err1)
		return
	}
	fmt.Println("buf : ", string(buf[:n]))
}
