

#include "stdafx.h"
#include <Python.h>
#include <iostream>
#include "PythonModule.h"
#include "PythonFunction.h"
#include "PythonClass.h"
#include "PythonClassMethod.h"
#include "pythonExtensionClass.h"
#include "PythonVariable.h"

namespace EPy=EmbededPython;

int main(int argc, char *argv[])
{
	std::string pathToModule("C:\\Users\\bkumpar\\Documents\\Visual Studio 2015\\Projects\\EmbeddedPython");
	std::string moduleName("test");
	EPy::Module* testModule = new EPy::Module(moduleName, pathToModule);

#if 1
	EPy::Function<long>* printPath = new EPy::Function<long>(testModule, "printPath");
	long longVal = printPath->execute();
	std::cout << "result of printPath: " << longVal << std::endl;
	
	EPy::VoidFunction* helloWorld = new EPy::VoidFunction(testModule, "helloWorld");
	helloWorld->execute();
	std::cout << "void function helloWorld executed " << std::endl;
	
	EPy::Function2p<double, double, double>* multiply = new EPy::Function2p<double, double, double>(testModule, "multiply");
	double dblVal = multiply->execute(3.14, 2.0);
	std::cout << "result of 1st multiply: " << dblVal << std::endl;
	dblVal = multiply->execute(3.14, 0.5);
	std::cout << "result of 2nd multiply: " << dblVal << std::endl;

	EPy::Function2p<long, int, std::string>* printOut = new EPy::Function2p<long, int, std::string>(testModule, "printOut");
	long lngVal = printOut->execute(10,"tekst to print out");
	std::cout << "result of printOut: " << lngVal << std::endl;

	EPy::Class1p<int>* testClass = new EPy::Class1p<int>(testModule, "testClass", 99 );
	PyObject* testClassInstance = testClass->newInstance();
    EPy::ClassMethod<int>* pcm1  = new EPy::ClassMethod<int>(testClassInstance, "printParam");
    int returnValue = pcm1->execute();
    std::cout << "result of testClass.printParam: " << returnValue << std::endl;

    EPy::ClassMethod1p<double, double>* printSquare  = new EPy::ClassMethod1p<double,double>(testClassInstance, "square");
    double returnValueDbl = printSquare->execute(3.14);
    std::cout << "result of testClass.printSquare: " << returnValueDbl << std::endl;

    EPy::VoidClassMethod1p<double>* setParam  = new EPy::VoidClassMethod1p<double>(testClassInstance, "setParam");
    setParam->execute(42);
    std::cout << "testClass.setParam executed " << std::endl;

/*
    PythonExtensionClass* pec = new PythonExtensionClass();
	EPy::VoidFunction1p<long>* printSomething = new EPy::VoidFunction1p<long>(testModule, "printSomething");
	
	printSomething->execute((long)pec, (long)method);
*/
#endif

	EPy::Variable<int> * intVar = new EPy::Variable<int>(testModule,"testInt");
	std::cout << "testInt value is " << intVar->value() << std::endl;
	return 0;
}

