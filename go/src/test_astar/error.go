package test_astar

import "fmt"

type GeneralError struct {
	errorInfo string
}

func NewGeneralError(errorInfo string, a ...interface{}) *GeneralError {
	return &GeneralError{
		errorInfo: fmt.Sprintf(errorInfo, a...),
	}
}

func (this *GeneralError) Error() string {
	return this.errorInfo
}
