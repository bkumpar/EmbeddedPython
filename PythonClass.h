#pragma once

#include "StdAfx.h"
#include <Python.h>
#include <string>
#include "PythonModule.h"


namespace EmbededPython
{
class ClassBase 
{
public:
	ClassBase(Module* pythonModule, std::string className, int argc )
	{
		Py_Initialize();
		if(pythonModule->module)
		{
			_class = PyObject_GetAttrString(pythonModule->module, className.c_str());
			pCtorArgs = PyTuple_New(argc);
		}
		else
		{
			_class = Py_None;
		}
	}
		
	~ClassBase()
	{
		//Py_DECREF(module);
		Py_Finalize();
	}

	PyObject * newInstance()
	{
		PyObject* pValue;
		if(_class)
		{
			pValue = PyObject_CallObject(_class, pCtorArgs);
		}
		else
		{
			pValue = Py_None;
		}
		return pValue;	
	}

	void addArg(int arg)
	{
		PyObject* pValue = Py_BuildValue("i", arg);
		PyTuple_SetItem(pCtorArgs, argCount++, pValue);
		//Py_XDECREF(pValue);
	}

	void addArg(double arg)
	{
		PyObject* pValue = Py_BuildValue("d", arg);
		PyTuple_SetItem(pCtorArgs, argCount++, pValue);
		//Py_DECREF(pValue);
	}

	void addArg(std::string arg)
	{
		PyObject* pValue = Py_BuildValue("s", arg.c_str());
		PyTuple_SetItem(pCtorArgs,  argCount++, pValue);
		//Py_DECREF(pValue);
	}
	
	PyObject* _class;
	PyObject* pCtorArgs;
	int argCount;

};

template<typename P1>
class Class1p : public ClassBase
{
public:
	Class1p(Module* pythonModule, std::string className, P1 param1) 
		: ClassBase(pythonModule, className, 1)
	{
		argCount = 0;
		addArg(param1);
	}
};

}