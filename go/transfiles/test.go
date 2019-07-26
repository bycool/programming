package main

import (
	"fmt"
	"io/ioutil"
)

func main () {
	fileinfos, err := ioutil.ReadDir("/home/ten/")
	if err != nil {
		fmt.Println("os.Readdir err")
		return
	}

	for _,file := range fileinfos {
		if file.Name()[0] != '.' {
			fmt.Println(file.Name())
		}
	}
}
