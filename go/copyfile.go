package main

import (
	"fmt"
	"os"
//	"bufio"
	"io"
)


func main () {
	list := os.Args
	if len(list) != 3 {
		fmt.Println("usnage: xx. srcfile tgt file")
		return
	}

	srcpath := list[1]
	tgtpath := list[2]

	if srcpath == tgtpath {
		fmt.Println("same file")
		return
	}

	sf, errs := os.Open(srcpath)
	if errs != nil {
		fmt.Println("open srcpath error")
		return
	}

	tf, errt := os.Create(tgtpath)
	if errt != nil {
		fmt.Println("create tgtpath error")
		return
	}

	defer sf.Close()
	defer tf.Close()

	buf := make([]byte, 1024*4)
	for {
		n, errsr := sf.Read(buf)
		if errsr != nil {
			if errsr == io.EOF {
				break
			}
			fmt.Println("read srcpath error")
			break
		}
		tf.Write(buf[:n])
	}
}
