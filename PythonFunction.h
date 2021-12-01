#pragma once
#include "StdAfx.h"
#include <Python.h>
#include <string>

#include "PythonModule.h"

namespace EmbededPython
{
class FunctionBase 
{
public:
	FunctionBase(Module* pythonModule, std::string functionName, int argc)
	{
		if(pythonModule->module)
		{
			pFunc = PyObject_GetAttrString(pythonModule->module, functionName.c_str());
			pArgs = PyTuple_New(argc);
		}
		else
		{
			pFunc = Py_None;
			pArgs = Py_None;
		}
	}

	~FunctionBase()
	{
	 Py_XDECREF(pFunc);
	}

	void addArg(int arg)
	{
		PyObject* pValue = Py_BuildValue("i", arg);
		PyTuple_SetItem(pArgs, argCount++, pValue);
		//Py_XDECREF(pValue);
	}

	void addArg(double arg)
	{
		PyObject* pValue = Py_BuildValue("d", arg);
		PyTuple_SetItem(pArgs, argCount++, pValue);
		//Py_DECREF(pValue);
	}

	void addArg(std::string arg)
	{
		PyObject* pValue = Py_BuildValue("s", arg.c_str());
		PyTuple_SetItem(pArgs,  argCount++, pValue);
		//Py_DECREF(pValue);
	}

	bool convert(int &outputValue, PyObject* inputValue)
	{
		outputValue = PyLong_AsLong(inputValue);
		return true;
	}

	bool convert(long &outputValue, PyObject* inputValue)
	{
		outputValue = PyLong_AsLong(inputValue);
		return true;
	}

	bool convert(double &outputValue, PyObject* inputValue)
	{
		outputValue = PyFloat_AsDouble(inputValue);
		return true;
	}

	bool convert(std::string &outputValue, PyObject* inputValue)
	{
		PyObject* bytes = PyUnicode_AsUTF8String(inputValue);
		outputValue = PyBytes_AsString(bytes); 
		if (PyErr_Occurred()) 
		{
			Py_DECREF(bytes); 
			return false; 
		}
		
		Py_DECREF(bytes); 
		return true;
	}

	PyObject* executeFunction()
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

private:
	PyObject *pName;
	PyObject *pModule;
	PyObject *pFunc;
protected:
	PyObject* pArgs;
	int argCount;
};

template<typename R, typename P1, typename P2, typename P3>
class Function3p : public FunctionBase
{
public:
	Function3p(Module* pythonModule, std::string functionName ) 
		: FunctionBase(pythonModule, functionName, 3)	{};
	
	R execute( P1 param1, P2 param2, P3 param3) 
	{ 
		argCount = 0;
		addArg(param1);
		addArg(param2);
		addArg(param3);
		R retval;
		PyObject* value = executeFunction();
		convert(retval, value);
		Py_DECREF(value); 
		return retval;
	};
};

template<typename P1, typename P2, typename P3>
class VoidFunction3p : public FunctionBase
{
public:
	VoidFunction3p(Module* pythonModule, std::string functionName ) 
		: FunctionBase(pythonModule, functionName, 3)	{};
	
	void execute( P1 param1, P2 param2, P3 param3) 
	{ 
		argCount = 0;
		addArg(param1);
		addArg(param2);
		addArg(param3);
		PyObject* value = executeFunction();
		Py_DECREF(value); 
		return;
	};
};

template<typename R, typename P1, typename P2>
class Function2p : public FunctionBase
{
public:
	Function2p(Module* pythonModule, std::string functionName ) 
		: FunctionBase(pythonModule, functionName, 2){};

	R execute( P1 param1, P2 param2) 
	{ 
		argCount = 0;
		addArg(param1);
		addArg(param2);
		R retval;
		PyObject* value = executeFunction();
		convert(retval, value);
		Py_DECREF(value); 
		return retval;
	};
};

template<typename R, typename P1, typename P2>
class VoidFunction2p : public FunctionBase
{
public:
	VoidFunction2p(Module* pythonModule, std::string functionName ) 
		: FunctionBase(pythonModule, functionName, 2){};

	void execute( P1 param1, P2 param2) 
	{ 
		argCount = 0;
		addArg(param1);
		addArg(param2);
		R retval;
		PyObject* value = executeFunction();
		convert(retval, value);
		Py_DECREF(value); 
		return;
	};
};


template<typename R, typename P1>
class Function1p : public FunctionBase
{
public:
	Function1p(Module* pythonModule, std::string functionName) 
		: FunctionBase(pythonModule, functionName, 1)	{};

	R execute( P1 param1) 
	{ 
		argCount = 0;
		addArg(param1);
		R retval;
		PyObject* value = executeFunction();
		convert(retval, value);
		Py_DECREF(value); 
		return retval;
	};
};

template<typename P1>
class VoidFunction1p : public FunctionBase
{
public:
	VoidFunction1p(Module* pythonModule, std::string functionName) 
		: FunctionBase(pythonModule, functionName, 1)	{};

	void execute( P1 param1) 
	{ 
		argCount = 0;
		addArg(param1);
		PyObject* value = executeFunction();
		//Py_DECREF(value); 
		return;
	};
};

template<typename R>
class Function : public FunctionBase
{
public:
	Function(Module* pythonModule, std::string functionName) 
		: FunctionBase(pythonModule, functionName, 0)	{};

	R execute() 
	{ 
		R retval;
		PyObject* value = executeFunction();
		convert(retval, value);
		Py_DECREF(value); 
		return retval;
	};
};

class VoidFunction : public FunctionBase
{
public:
	VoidFunction(Module* pythonModule, std::string functionName) 
		: FunctionBase(pythonModule, functionName, 0)	{};

	void execute() 
	{ 
		PyObject* value = executeFunction();
		Py_DECREF(value); 
		return;
	};
};

}

