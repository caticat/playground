package test_net_client

import (
	"fmt"
	"net"
)

func Test() {
	conn, err := net.Dial("tcp", "127.0.0.1:2223")
	if err != nil {
		fmt.Println("链接服务器失败,err:", err)
		return
	}
	defer conn.Close()

	fmt.Println("开始发送数据")
	conn.Write([]byte("how are you"))
	buffer := make([]byte, 100)
	l, err := conn.Read(buffer)
	fmt.Println("收到服务器数据:", string(buffer[:l]), ",长度:", l, ",错误:", err)
	fmt.Println("函数调用完成")
}
