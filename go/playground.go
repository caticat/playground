package main

import "fmt"

// 根据数据数量，单条数据长度（字节），消耗时间（微秒）来计算每秒处理多少MB的数据
func analyzeStress(dataNum, dataLen, useTime float64, prefix string) {
	allDataSize := dataNum * dataLen / (1024 * 1024) // 单位：M
	useTime /= 1000000 // 单位：秒
	pDS := allDataSize / useTime
	fmt.Printf("[%s]处理速度:%v(MB/S),%v(次/S)\n", prefix, pDS, dataNum / useTime)
}

// 单条数据长度（字节），每秒处理请求数来计算每秒处理多少MB的数据
func calcStress(dataLen, requestPerSecond float64, prefix string) {
	pDS := requestPerSecond * dataLen / (1024*1024)
	fmt.Printf("[%s]处理速度:%v(MB/S),%v(次/S)\n", prefix, pDS, requestPerSecond)
}

func main() {
	fmt.Println("\n本地测试debug")
	analyzeStress(10000, 1024*64, 1830879, "SET")
	analyzeStress(10000, 1024*64, 1447705,"GET")

	fmt.Println("\n本地测试release")
	analyzeStress(10000, 1024*64, 1789179,"SET")
	analyzeStress(10000, 1024*64, 1401223,"GET")

	fmt.Println("\n本地测试debug,多线程")
	analyzeStress(100000, 1024*64, 4697897,"SET")
	analyzeStress(100000, 1024*64, 6093962,"GET")

	fmt.Println("\nbenchmark测试,多线程")
	calcStress(1024*64, 9090.91,"SET")
	calcStress(1024*64, 9425.07,"GET")

	fmt.Println("\nbenchmark测试,单线程")
	calcStress(1024*64, 29585.80,"SET")
	calcStress(1024*64, 36101.08,"GET")

	fmt.Println("\n压测服测试release,单线程")
	analyzeStress(10000, 1024*64, 1477901,"SET")
	analyzeStress(10000, 1024*64, 877703,"GET")

	fmt.Println("\n压测服测试release,多线程")
	analyzeStress(100000, 1024*64, 3664834,"SET")
	analyzeStress(100000, 1024*64, 3349457,"GET")

	fmt.Println("\n压测服benchmark测试,单线程")
	calcStress(1024*64, 13793.10,"SET")
	calcStress(1024*64, 13661.20,"GET")

	fmt.Println("\n压测服benchmark测试,多线程")
	calcStress(1024*64, 30147.72,"SET")
	calcStress(1024*64, 31347.96,"GET")

	fmt.Println("\n压测服mysql测试release,单线程")
	analyzeStress(10000, 1024*64, 17437459,"INSERT")
	analyzeStress(10000, 1024*64, 7663155,"SELECT")
}
