package test_astar

func test1() {
	c := NewAStarCalculator()
	c.SetPosBegin(NewPosXY(2, 2))
	c.SetPosEnd(NewPosXY(6, 2))
	c.SetBlock([]*Pos{
		NewPosXY(4, 0),
		NewPosXY(4, 1),
		NewPosXY(4, 2),
		NewPosXY(4, 3),
		NewPosXY(4, 4),
		NewPosXY(4, 5),
		NewPosXY(5, 5),
		NewPosXY(6, 5),
		NewPosXY(7, 5),
		//NewPosXY(8, 5),
	})
	c.SetPosBorder(NewPosXY(9, 7))
	//c.SetAroundEnable(true)
	c.Calculate()
	c.Graph()
}

func test2() {
	c := NewAStarCalculator()
	c.SetPosBegin(NewPosXY(2, 2))
	c.SetPosEnd(NewPosXY(6, 2))
	c.SetBlock([]*Pos{
		NewPosXY(0, 0),
		NewPosXY(1, 1),
		NewPosXY(2, 1),
		NewPosXY(3, 1),
		NewPosXY(4, 1),
		NewPosXY(5, 1),
		NewPosXY(5, 2),
		NewPosXY(5, 3),
		NewPosXY(4, 3),
		NewPosXY(3, 3),
		NewPosXY(2, 3),
		NewPosXY(1, 3),
		NewPosXY(1, 4),
		NewPosXY(1, 5),
		//NewPosXY(1, 6),
	})
	c.SetPosBorder(NewPosXY(9, 7))
	//c.SetAroundEnable(true)
	c.Calculate()
	c.Graph()
}

func Test() {
	test1()
	test2()
}
