package main

import (
	"fmt"
	"io"
	"bufio"
	"os"
)

func WriteFile(path string) {
	f, err := os.Create(path)
	if err != nil {
		fmt.Println("create file error")
		return
	}

	defer f.Close()

	var buf string

	for i:=0; i<10; i++ {
		buf = fmt.Sprintf("i = %d\n", i)
		n, err := f.WriteString(buf)
		if err != nil {
			fmt.Println("write ", buf, "error")
		}
		fmt.Println("n:", n)
	}
}

func ReadFile(path string) {
	f, err := os.Open(path)
	if err != nil {
		fmt.Println("create ", path, "errpr")
		return
	}

	defer f.Close()

	buf := make([]byte, 2014*2)

	n, err1 := f.Read(buf)
	if err1 != nil {
		fmt.Println("read buf error")
		return
	}

	fmt.Println(string(buf[:n]))

}

func ReadFileLine(path string) {
    f, err := os.Open(path)
    if err != nil {
        fmt.Println("create ", path, "errpr")
        return
    }

    defer f.Close()

	r := bufio.NewReader(f)

	for {
		buf, err := r.ReadBytes('\n')
		if err != nil {
			if err == io.EOF {
				break
			}
		}
		fmt.Println(string(buf))
	}
}

func main() {
	var path string = "./1.txt"

	WriteFile(path)
//	ReadFile(path)
	ReadFileLine(path)
}
