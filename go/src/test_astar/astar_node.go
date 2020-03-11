package test_astar

import "fmt"

type AStarNode struct {
	pFront *AStarNode
	pos    *Pos
	g      uint32 // 到起始点的距离
	h      uint32 // 到终点的距离
}

func NewAStarNode() *AStarNode {
	return &AStarNode{
		pos: NewPos(),
	}
}

func NewAStarNodeByPos(pos *Pos) *AStarNode {
	a := NewAStarNode()
	a.SetPos(pos)
	return a
}

func (this *AStarNode) Pos() *Pos { return this.pos }
func (this *AStarNode) SetPos(pos *Pos) {
	*this.pos = *pos
}

func (this *AStarNode) Show() string {
	return fmt.Sprintf("坐标:(%v,%v),g:%v,h:%v,f:%v", this.Pos().X(), this.Pos().Y(), this.g, this.h, this.f())
}

// 总距离
func (this *AStarNode) f() uint32 {
	return this.g + this.h
}
