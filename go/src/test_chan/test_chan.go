package test_chan

import "fmt"

func Test() {
	c := make(chan bool, 10)
	fmt.Println(len(c))
	t(c)
	fmt.Println(len(c))
}

func t(c chan bool) {
	c <- true
	c <- true
	c <- true
}
