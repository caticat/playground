// 使用第四象限
// 开闭结构都使用slice，可以优化为有序list+map的组合，但是优化后代码就不够清晰了，影响理解，就这样吧

// A*寻路简述
// 程序维护两个列表，分别为open和close表
// 从起始点开始，所有没有进行发散处理的节点放在open中
// 每次遍历都是从open中找到总估值最小的节点进行发散遍历
// 同时将这个最小估值节点放入close中表示后续不需要在对他进行处理了
// 找到周围的点，如果在close中，则过掉。
// 如果周围的点在open中，则判断是否要更新这个点的预估值
// 如果不在open中，则向open中插入这个点
// 重复在open中获取最小估值点并处理
// 直到抵达目标（寻路成功）
// 或者open表中没有点为止（寻路失败）

package test_astar

import (
	"bytes"
	"fmt"
)

type AStarCalculator struct {
	posBegin     *Pos   // 起始点
	posEnd       *Pos   // 终点
	sliBlock     []*Pos // 阻挡点
	posBorder    *Pos   // 边界右下角坐标
	aroundEnable bool   // 是否开启斜向寻路

	posCur   *AStarNode   // 当前寻路计算点
	sliOpen  []*AStarNode // 待处理的点
	sliClose []*AStarNode // 无需处理的点
	result   *AStarNode   // 最终路径
}

func NewAStarCalculator() *AStarCalculator {
	return &AStarCalculator{}
}

func (this *AStarCalculator) SetPosBegin(pos *Pos)        { this.posBegin = pos }
func (this *AStarCalculator) SetPosEnd(pos *Pos)          { this.posEnd = pos }
func (this *AStarCalculator) SetPosBorder(pos *Pos)       { this.posBorder = pos }
func (this *AStarCalculator) SetAroundEnable(enable bool) { this.aroundEnable = enable }
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

	// 重置
	this.result = nil

	// 将起始点加入到开列表
	this.sliOpen = append(this.sliOpen, NewAStarNodeByPos(this.posBegin))

	// 循环寻路
	for this.posCur = this.getMinFNode(); this.posCur != nil; this.posCur = this.getMinFNode() {
		if this.isDone(this.posCur.Pos()) {
			this.result = this.posCur
			return true
		}
		this.step()
	}

	return false // 寻路失败
}

func (this *AStarCalculator) Graph() {
	if this.result == nil {
		fmt.Println("没有找到路线")
		return
	}

	sliPos := []*Pos{this.result.Pos()}
	for n := this.result.pFront; n != nil; n = n.pFront {
		sliPos = append(sliPos, n.Pos())
	}

	l := len(sliPos)
	l2 := l / 2
	for i := 0; i < l2; i++ {
		sliPos[i], sliPos[l-i-1] = sliPos[l-i-1], sliPos[i]
	}

	xMax := this.posBorder.X() + 1
	yMax := this.posBorder.Y() + 1
	fmt.Println("xMax:", xMax, "yMax:", yMax)

	buf := &bytes.Buffer{}
	cur := NewPos()
	for y := uint32(0); y <= yMax; y++ {
		for x := uint32(0); x <= xMax; x++ {
			if x == 0 && y == 0 {
				buf.WriteString("+ ")
			} else if x == 0 {
				buf.WriteString(fmt.Sprintf("%v ", y-1))
			} else if y == 0 {
				buf.WriteString(fmt.Sprintf("%v ", x-1))
			} else if x == xMax {
				if y == yMax {
					buf.WriteString("+ ")
				} else {
					buf.WriteString("| ")
				}
			} else if y == yMax {
				if x == xMax {
					buf.WriteString("+ ")
				} else {
					buf.WriteString("_ ")
				}
			} else {
				cur.SetX(x - 1)
				cur.SetY(y - 1)
				if *this.posBegin == *cur {
					buf.WriteString("A ")
				} else if *this.posEnd == *cur {
					buf.WriteString("B ")
				} else if this.isPosInSlice(cur, sliPos) {
					buf.WriteString("@ ")
				} else if this.isPosInSlice(cur, this.sliBlock) {
					buf.WriteString("# ")
				} else {
					buf.WriteString("  ")
				}
			}
		}
		buf.WriteString("\n")
	}

	// 打印
	fmt.Println(buf.String())
}

func (this *AStarCalculator) checkBorder() error {
	// 获取到所有相关点的最大值
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

	// 边界检测
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
		if (r != nil) && (n.f() >= r.f()) {
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

func (this *AStarCalculator) step() {
	xCur := this.posCur.Pos().X()
	yCur := this.posCur.Pos().Y()
	var e error

	// 整理上下左右四个点
	sliAround := make([]*Pos, 0, 4)
	if xCur > 0 {
		sliAround = append(sliAround, NewPosXY(xCur-1, yCur))
	}
	if yCur > 0 {
		sliAround = append(sliAround, NewPosXY(xCur, yCur-1))
	}
	sliAround = append(sliAround, NewPosXY(xCur, yCur+1))
	sliAround = append(sliAround, NewPosXY(xCur+1, yCur))

	// 整理斜向四个点
	if this.aroundEnable {
		if (xCur > 0) && (yCur > 0) {
			sliAround = append(sliAround, NewPosXY(xCur-1, yCur-1))
		}
		if xCur > 0 {
			sliAround = append(sliAround, NewPosXY(xCur-1, yCur+1))
		}
		if yCur > 0 {
			sliAround = append(sliAround, NewPosXY(xCur+1, yCur-1))
		}
		sliAround = append(sliAround, NewPosXY(xCur+1, yCur+1))
	}

	// 遍历处理
	for _, p := range sliAround {
		node := NewAStarNodeByPos(p)
		node.pFront = this.posCur
		node.g = this.posCur.g + 1

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
			fmt.Println("计算H出错:", e)
			return
		}
		//fmt.Println("测试点:%v", node.Show())
		if openNode := this.getOpenNode(p); openNode != nil {
			if openNode.f() > node.f() {
				openNode.pFront = this.posCur
				openNode.g = node.g
				fmt.Println("更新点:", node.Show())
			} else {
				fmt.Println("重复点:", node.Show())
			}
		} else {
			this.sliOpen = append(this.sliOpen, node)
			fmt.Println("新增点:", node.Show())
		}
	}
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
	if this.posBorder == nil {
		return false
	}
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
	if pos == nil {
		return false
	}
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
