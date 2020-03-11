package test_astar

type Pos struct {
	x uint32
	y uint32
}

func NewPos() *Pos {
	return &Pos{}
}

func NewPosXY(x, y uint32) *Pos {
	pos := NewPos()
	pos.x = x
	pos.y = y
	return pos
}

func (this *Pos) X() uint32     { return this.x }
func (this *Pos) SetX(x uint32) { this.x = x }
func (this *Pos) Y() uint32     { return this.y }
func (this *Pos) SetY(y uint32) { this.y = y }
