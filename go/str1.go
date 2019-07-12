package main

import "fmt"
import "strings"

func main() {
	fmt.Println(strings.Contains("abcdefghijklmn", "ghi")) // Contains

	s := []string{"abc", "def", "ghi"} //join 仿佛第一个参数只能用slice，类型不限。
	fmt.Println(strings.Join(s,","))

	fmt.Println(strings.Index("abcdefghijklmn", "ghi"))  // Index  字符串子串搜索

	fmt.Println(strings.Repeat("abc", 5))  //第一个参数  要重复的字符串，第二个参数 次数

	fmt.Println(strings.Replace("abcabcdefg", "abc","fff", 3))   // src, old, new, times  times:src内times个old被替换为new

	fmt.Println(strings.Split("abc,def,ghig,klm,ede", ","))  //将src中 ，分割后保存到切片内，并返回

	fmt.Println(strings.Trim("abcdefga", "a")) //两头查找指定字符串，然后去掉

	fmt.Println(strings.Fields("ab cde fg  hig  hl  mn")) // 类似split，但针对空格分割，且把空格去掉。
}
