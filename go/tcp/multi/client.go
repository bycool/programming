package main

import (
	"fmt"
	"net"
	"os"
)

func main () {
	conn, err := net.Dial("tcp", "127.0.0.1:9000")
	if err != nil {
		fmt.Println("net.Dial err: ", err)
		return
	}

	defer conn.Close()

	go func () {
		buf := make([]byte, 1204)
		for {
			n, err := conn.Read(buf)
			if err != nil {
				fmt.Println("conn.read err: ", err)
				return
			}
			fmt.Println("[from service]: ", string(buf[:n]))
		}
	}()

	str := make([]byte, 1024)
	for {
		n, err := os.Stdin.Read(str)
		if err != nil {
			fmt.Println("os.Stdin.read err: ", err)
			return
		}

		conn.Write(str[:n])
	}
}
