#if 0
#include "PythonFunction.h"
#define PYTHON_3


PythonFunction::PythonFunction(PythonModule* pythonModule, std::string functionName, int argc)
{
	if(pythonModule->module)
	{
		pFunc = PyObject_GetAttrString(pythonModule->module, functionName.c_str());
		pArgs = PyTuple_New(argc);
		argCount = 0;
	}
	else
	{
		pFunc = Py_None;
	}

}

PythonFunction::~PythonFunction()
{
	 Py_XDECREF(pFunc);
}

void PythonFunction::addArg(int arg)
{
	PyObject* pValue = Py_BuildValue("i", arg);
	PyTuple_SetItem(pArgs, argCount++, pValue);
}

void PythonFunction::addArg(double arg)
{
	PyObject* pValue = Py_BuildValue("d", arg);
	PyTuple_SetItem(pArgs, argCount++, pValue);
}

void PythonFunction::addArg(std::string arg)
{
	PyObject* pValue = Py_BuildValue("s", arg.c_str());
	PyTuple_SetItem(pArgs,  argCount++, pValue);
}

PyObject* PythonFunction::execute()
{
	
	PyObject* pValue;
	if(pFunc)
	{
		pValue = PyObject_CallObject(pFunc, pArgs);
	}
	else
	{
		pValue = Py_None;
	}
	return pValue;
}


#endif