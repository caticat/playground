package test_astar

func Test() {
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
