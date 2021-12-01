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

testList = [1,2,3,4,5,6]
testDict = {"A":1,"B":2,"C":3,"D":4}
testTuple = (10, 20, 30)
testInt = 42

def helloWorld ( ):
	print("Hello world!\n")


def printPath ( ):
	print("PYTHONPATH:")
	for i in sys.path:
		print(i)
	return len(sys.path)

def multiply ( a, b ):
	print("multiply\n")
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

    def printParam(self):
        print(self.param)
        return 1000

    def getParam(self):
        return self.param

    def square(self, number):
        sq = number * number
        return sq

class PythonExtensionClass:

	def __init__(self, classRef):
		self.obj = classRef 
		self.printSomething
		
def printSomething(classRef):
	pec = PythonExtensionClass(classRef)
	pec.printSomething(self)
			

	

if __name__ == '__main__':
    helloWorld()
    printPath()
    print(multiply(3.14, 2.0))
    res = printOut(10, "text")
    print(res)
    tc=testClass(99)
    tc.printParam()
    print (tc.printParam())
    sq = tc.square(1.2)
    print(sq)
