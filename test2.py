#-------------------------------------------------------------------------------
# Name:        module1
# Purpose:
#
# Author:      bkumpar
#
# Created:     03.09.2019
# Copyright:   (c) bkumpar 2019
# Licence:     <your licence>
#-------------------------------------------------------------------------------
import sys

def helloWorld ( ):
	print("Hello world2!\n")
	print(sys.path)
	return 3

def printPath ( ):
	print("PYTHONPATH2:")
	for i in sys.path:
		print(i)
	return len(sys.path)

def multiply ( a, b ):
	print("multiply2\n")
	return a*b


def printOut(count, str):
	for i in range(0, count):
		print(str)
	return count

class testClass:

    def __init__(self, param):
        self.param = param
        
    def setParam(self, param):
        self.param = param

    def getParam(self, param):
        return self.param
        
    def square(self, number):
        sq = number * number
        return sq
        


if __name__ == '__main__':
	helloWorld()
	multiply(3.14, 2.0)
	printOut(10, "text")