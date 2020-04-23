package test_interface

import "fmt"

func Test() {
	var a1 a
	t1(a1)
	fmt.Println("p:", a1.data)
	b1 := &b{}
	t1(b1)
	fmt.Println("p:", b1.data)
}

type i interface {
	SetData(data string)
}

type a struct {
	data string
}

func (this a) SetData(data string) {
	this.data = data
}

type b struct {
	data string
}

func (this *b) SetData(data string) {
	this.data = data
}

func t1(p i) {
	p.SetData("t1")
}

func t2(p i) {
	p.SetData("t2")
}
