// 使用第四象限

package test_astar

import (
	"bytes"
	"fmt"
)

type AStarCalculator struct {
	posBegin  *Pos   // 起始点
	posEnd    *Pos   // 终点
	sliBlock  []*Pos // 阻挡点
	posBorder *Pos   // 边界右下角坐标

	posCur   *AStarNode   // 当前寻路计算点
	sliOpen  []*AStarNode // 待处理的点
	sliClose []*AStarNode // 无需处理的点
	result   *AStarNode   // 最终路径
}

func NewAStarCalculator() *AStarCalculator {
	return &AStarCalculator{}
}

func (this *AStarCalculator) SetPosBegin(pos *Pos)  { this.posBegin = pos }
func (this *AStarCalculator) SetPosEnd(pos *Pos)    { this.posEnd = pos }
func (this *AStarCalculator) SetPosBorder(pos *Pos) { this.posBorder = pos }
func (this *AStarCalculator) SetBlock(sliBlock []*Pos) {
	for _, block := range sliBlock {
		this.sliBlock = append(this.sliBlock, block)
	}
}

func (this *AStarCalculator) Calculate() bool {
	// 检测边界
	if err := this.checkBorder(); err != nil {
		fmt.Println("检测边界出错:", err)
		return false
	}

	//
	this.posCur = NewNewAStarNodeByPos(this.posBegin)
	if this.isDone(this.posCur.Pos()) {
		this.result = this.posCur
		return true
	}
	this.sliOpen = append(this.sliOpen, this.posCur)
	this.posCur = this.getMinFNode()

	for ; this.posCur != nil; this.posCur = this.getMinFNode() {
		isDone, e := this.step()
		if e != nil {
			fmt.Println("出错了:", e)
			return false
		}
		if isDone {
			this.result = this.posCur
			return true
		}
	}

	return false // 寻路失败
}

func (this *AStarCalculator) Graph() {
	if this.result == nil {
		fmt.Println("没有找到路线")
		return
	}

	sliPos := []*Pos{this.result.Pos()}
	n := this.result.pFront
	for ; n != nil; n = n.pFront {
		sliPos = append(sliPos, n.Pos())
	}

	l := len(sliPos)
	l2 := l / 2
	for i := 0; i < l2; i++ {
		sliPos[i], sliPos[l-i-1] = sliPos[l-i-1], sliPos[i]
	}

	xMax := this.posBorder.X()
	yMax := this.posBorder.Y()
	fmt.Println("xMax:", xMax, "yMax:", yMax)

	buf := &bytes.Buffer{}
	cur := NewPos()
	for y := uint32(0); y <= yMax; y++ {
		for x := uint32(0); x <= xMax; x++ {
			cur.SetX(x)
			cur.SetY(y)
			if *this.posBegin == *cur {
				buf.WriteString("A")
			} else if *this.posEnd == *cur {
				buf.WriteString("B")
			} else if this.isPosInSlice(cur, sliPos) {
				buf.WriteString("*")
			} else if this.isPosInSlice(cur, this.sliBlock) {
				buf.WriteString("+")
			} else if (x == 0) || (x == xMax) {
				if (y == 0) || (y == yMax) {
					buf.WriteString("+")
				} else {
					buf.WriteString("|")
				}
			} else if (y == 0) || (y == yMax) {
				if (x == 0) || (x == xMax) {
					buf.WriteString("+")
				} else {
					buf.WriteString("_")
				}
			} else {
				buf.WriteString(" ")
			}
		}
		buf.WriteString("\n")
	}

	// 打印
	fmt.Println(buf.String())
}

func (this *AStarCalculator) checkBorder() error {
	xMax := uint32(0)
	yMax := uint32(0)
	sliPos := make([]*Pos, 0, len(this.sliBlock))
	sliPos = append(sliPos, this.sliBlock...)
	sliPos = append(sliPos, this.posBegin)
	sliPos = append(sliPos, this.posEnd)
	for _, pos := range sliPos {
		if xMax < pos.X() {
			xMax = pos.X()
		}
		if yMax < pos.Y() {
			yMax = pos.Y()
		}
	}

	if this.posBorder == nil {
		this.posBorder = NewPosXY(xMax+2, yMax+2)
	} else {
		if this.posBorder.X() <= xMax {
			return NewGeneralError("边界错误:x方向边界值:%v,实际最大值:%v", xMax, this.posBorder.X())
		}
		if this.posBorder.Y() <= yMax {
			return NewGeneralError("边界错误:y方向边界值:%v,实际最大值:%v", yMax, this.posBorder.Y())
		}
	}

	return nil
}

func (this *AStarCalculator) getMinFNode() *AStarNode {
	if len(this.sliOpen) == 0 {
		return nil
	}

	// 找到最小值
	var r *AStarNode = nil
	for _, n := range this.sliOpen {
		if r == nil {
			r = n
			continue
		}
		if n.f() >= r.f() {
			continue
		}
		r = n
	}

	if r == nil {
		return nil
	}

	// 将最小值从open中移除
	sliTmp := make([]*AStarNode, 0, len(this.sliOpen)-1)
	for i, n := range this.sliOpen {
		if r != n {
			continue
		}
		sliTmp = append(this.sliOpen[:i])
		if (i + 1) < len(this.sliOpen) {
			sliTmp = append(sliTmp, this.sliOpen[i+1:]...)
		}
		this.sliOpen = sliTmp
	}

	// 将最小值放入close中
	this.sliClose = append(this.sliClose, r)

	return r
}

func (this *AStarCalculator) step() (bool, error) {
	xCur := this.posCur.Pos().X()
	yCur := this.posCur.Pos().Y()
	var e error

	// 四个点
	sliAround := make([]*Pos, 0, 4)
	if xCur > 0 {
		sliAround = append(sliAround, NewPosXY(xCur-1, yCur))
	}
	if yCur > 0 {
		sliAround = append(sliAround, NewPosXY(xCur, yCur-1))
	}
	sliAround = append(sliAround, NewPosXY(xCur, yCur+1))
	sliAround = append(sliAround, NewPosXY(xCur+1, yCur))

	// 遍历处理
	for _, pos := range sliAround {
		node := NewAStarNode()
		node.pFront = this.posCur
		node.g = this.posCur.g + 1
		p := node.Pos()
		*p = *pos

		if !this.isInBorder(p) {
			continue
		}

		if this.isInBlock(p) {
			continue
		}

		if this.isInClose(p) {
			continue
		}
		node.h, e = this.calcH(p)
		if e != nil {
			return false, e
		}
		//fmt.Println("测试点:%v", node.Show())
		if openNode := this.getOpenNode(p); openNode != nil {
			if openNode.f() > node.f() {
				openNode.pFront = this.posCur
				openNode.g = node.g
				fmt.Println("更新点:", node.Show())
			} else {
				//fmt.Println("重复点:", node.Show())
			}
		} else {
			this.sliOpen = append(this.sliOpen, node)
			fmt.Println("新增点:", node.Show())
		}
		if this.isDone(p) {
			this.posCur = node
			return true, nil
		}
	}

	return false, nil
}

func (this *AStarCalculator) isInClose(pos *Pos) bool {
	for _, c := range this.sliClose {
		if *c.Pos() == *pos {
			return true
		}
	}
	return false
}

func (this *AStarCalculator) isInBorder(pos *Pos) bool {
	if pos.X() >= this.posBorder.X() {
		return false
	}
	if pos.Y() >= this.posBorder.Y() {
		return false
	}
	return true
}

func (this *AStarCalculator) isInBlock(pos *Pos) bool {
	return this.isPosInSlice(pos, this.sliBlock)
}

func (this *AStarCalculator) isPosInSlice(pos *Pos, sliData []*Pos) bool {
	for _, data := range sliData {
		if *data == *pos {
			return true
		}
	}
	return false
}

func (this *AStarCalculator) isDone(p *Pos) bool {
	if this.posEnd == nil {
		return true
	}
	if p == nil {
		return false
	}

	return *this.posEnd == *p
}

func (this *AStarCalculator) calcH(pos *Pos) (uint32, error) {
	if pos == nil {
		return 0, NewGeneralError("(pos == nil)没有参数")
	}
	if this.posEnd == nil {
		fmt.Println("没有设置终点坐标")
		return 0, NewGeneralError("(this.posEnd == nil)没有设置终点坐标")
	}

	h := uint32(0)
	if pos.X() > this.posEnd.X() {
		h = pos.X() - this.posEnd.X()
	} else {
		h = this.posEnd.X() - pos.X()
	}
	if pos.Y() > this.posEnd.Y() {
		h += pos.Y() - this.posEnd.Y()
	} else {
		h += this.posEnd.Y() - pos.Y()
	}

	return h, nil
}

func (this *AStarCalculator) getOpenNode(pos *Pos) *AStarNode {
	for _, c := range this.sliOpen {
		if *c.Pos() == *pos {
			return c
		}
	}
	return nil
}
