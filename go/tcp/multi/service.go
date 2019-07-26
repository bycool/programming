package main

import (
	"fmt"
	"net"
)


func HandleConn(conn net.Conn) {
	addr := conn.RemoteAddr().String()
	fmt.Printf("[conn sucessful] ")

	defer conn.Close()

	buf := make([]byte, 1024)

	for {
		n, err := conn.Read(buf)
		if err != nil {
			fmt.Println("conn read err: ", err)
			return
		}
		fmt.Printf("[%s]: %s", addr, buf[:n])
	
		conn.Write([]byte("[from server]"))
	}
}

func main () {
	listener, err := net.Listen("tcp", "127.0.0.1:9000")
	if err != nil {
		fmt.Println("net listen err:", err)
		return
	}

	defer listener.Close()

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("listener accept err: ", err)
			continue
		}

		go HandleConn(conn)
	}
}
