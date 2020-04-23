package test_walk

/*
In the directory containing test.go run

go build
To get rid of the cmd window, instead run

go build -ldflags="-H windowsgui"
*/

import (
	"fmt"
	"github.com/lxn/walk"
	. "github.com/lxn/walk/declarative"
	"strings"
)

type MyMainWindow struct {
	*walk.MainWindow
}

func Test() {
	fmt.Println("进入")

	//test1()
	//test2()
	test3()

	fmt.Println("退出")
}

func test1() {
	mw := &MyMainWindow{}

	var inTE, outTE *walk.TextEdit

	MainWindow{
		AssignTo: &mw.MainWindow,
		Title:    "Test",
		MinSize:  Size{600, 400},
		Layout:   Flow{},
		Children: []Widget{
			HSplitter{
				Children: []Widget{
					TextEdit{AssignTo: &inTE},
					TextEdit{AssignTo: &outTE, ReadOnly: true},
				},
			},
			PushButton{
				Text: "SCREAM",
				OnClicked: func() {
					pb, _ := walk.NewPushButton(mw.MainWindow)
					pb.SetText(inTE.Text())
					pb.Clicked().Attach(func() {
						mw.MainWindow.Children().Remove(pb)
					})
					outTE.SetText(strings.ToUpper(inTE.Text()))
				},
			},
		},
	}.Create()
	mw.Run()
}

func test2() {
	mw := &MyMainWindow{}

	var inTE, outTE *walk.TextEdit

	MainWindow{
		AssignTo: &mw.MainWindow,
		Title:    "Test",
		MinSize:  Size{600, 400},
		Layout:   VBox{},
		Children: []Widget{
			HSplitter{
				Children: []Widget{
					TextEdit{AssignTo: &inTE},
					TextEdit{AssignTo: &outTE, ReadOnly: true},
				},
			},
			PushButton{
				Text: "SCREAM",
				OnClicked: func() {
					pb, _ := walk.NewPushButton(mw.MainWindow)
					pb.SetText(inTE.Text())
					pb.Clicked().Attach(func() {
						mw.MainWindow.Children().Remove(pb)
					})
					outTE.SetText(strings.ToUpper(inTE.Text()))
				},
			},
		},
	}.Create()
	mw.Run()
}

func test3() {
	mw := &MyMainWindow{}

	var inTE, outTE *walk.TextEdit

	MainWindow{
		AssignTo: &mw.MainWindow,
		Title:    "Test",
		MinSize:  Size{600, 400},
		Layout:   VBox{},
		Children: []Widget{
			HSplitter{
				Children: []Widget{
					TextEdit{AssignTo: &inTE},
					TextEdit{AssignTo: &outTE, ReadOnly: true},
				},
			},
			PushButton{
				Text: "SCREAM",
				OnClicked: func() {
					pb, _ := walk.NewPushButton(mw.MainWindow)
					pb.SetText(inTE.Text())
					pb.Clicked().Attach(func() {
						mw.MainWindow.Children().Remove(pb)
					})
					outTE.SetText(strings.ToUpper(inTE.Text()))
				},
			},
		},
	}.Create()
	go mw.Run()
}
