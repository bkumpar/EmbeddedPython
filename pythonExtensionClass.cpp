#include "pythonExtensionClass.h"


PythonExtensionClass* newClass() 
{ 
	return new PythonExtensionClass(); 
}

void printSomething(PythonExtensionClass* self)
{ 
	self-> printSomething(); 
}
