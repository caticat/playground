package test_select

import (
	"fmt"
	"time"
)

var cha = make(chan int, 10)

//var wg = &sync.WaitGroup{}

func Test() {
	go p()
	go c()
	time.Sleep(10 * time.Second)
}

func p() {
	ticker := time.NewTicker(1 * time.Second)
	for {
		select {
		case <-ticker.C:
			cha <- 1
			fmt.Println("写数据,len:", len(cha))
		}
	}
}

func c() {
	ticker := time.NewTicker(1 * time.Second)
	for {
		select {
		case <-cha:
			fmt.Println("读取到数据了,len:", len(cha))
		case <-ticker.C:
			fmt.Println("tick")
			//default:
			//	fmt.Println("default")
		}
	}
}
