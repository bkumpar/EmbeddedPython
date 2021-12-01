#pragma once
#include "StdAfx.h"
#include <Python.h>
#include <string>

#include "PythonClass.h"

namespace EmbededPython
{

class ClassMethodBase 
{
public:
	ClassMethodBase(PyObject* pythonClassInstance,  std::string methodName, int argc)
	{
		if(pythonClassInstance)
		{
			pFunc = PyObject_GetAttrString(pythonClassInstance, methodName.c_str());
            pArgs = PyTuple_New(argc);
		}
		else
		{
			pFunc = Py_None;
			pArgs = Py_None;
		}
	}

	~ClassMethodBase()
	{
	 Py_XDECREF(pFunc);
	}

private:
	PyObject *pName;
	PyObject *pModule;
	PyObject *pFunc;
protected:
	PyObject* pArgs;
	int argCount;
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

};


template<typename R, typename P1, typename P2, typename P3>
class ClassMethod3p : public ClassMethodBase
{
public:
	ClassMethod3p(PyObject* pythonClassInstance, std::string methodName ) 
		: ClassMethodBase(pythonClassInstance, methodName, 3)	{};
	
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
		return (R)retval;
	};
};

template<typename P1, typename P2, typename P3>
class VoidClassMethod3p : public ClassMethodBase
{
public:
	VoidClassMethod3p(PyObject* pythonClassInstance, std::string methodName ) 
		: ClassMethodBase(pythonClassInstance, methodName, 3)	{};
	
	void execute( P1 param1, P2 param2, P3 param3) 
	{ 
		argCount = 0;
        addArg(param1);
		addArg(param2);
		addArg(param3);
		R retval;
		PyObject* value = executeFunction();
		convert(retval, value);
		Py_DECREF(value); 
	};
};

template<typename R, typename P1, typename P2>
class ClassMethod2p : public ClassMethodBase
{
public:
	ClassMethod2p(PyObject* pythonClassInstance, std::string methodName ) 
		: ClassMethodBase(pythonClassInstance, methodName, 2){};

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

template<typename P1, typename P2>
class VoidClassMethod2p : public ClassMethodBase
{
public:
	VoidClassMethod2p(PyObject* pythonClassInstance, std::string methodName ) 
		: ClassMethodBase(pythonClassInstance, methodName, 2){};

	void execute( P1 param1, P2 param2) 
	{ 
		argCount = 0;
        addArg(param1);
		addArg(param2);
		R retval;
		PyObject* value = executeFunction();
		convert(retval, value);
		Py_DECREF(value); 
	};
};

template<typename R, typename P1>
class ClassMethod1p : public ClassMethodBase
{
public:
	ClassMethod1p(PyObject* pythonClassInstance, std::string methodName) 
		: ClassMethodBase(pythonClassInstance, methodName, 1)	{};

	R execute( P1 param1) 
	{ 
        argCount = 0;
        addArg(param1);
		PyObject* value = executeFunction();
	    R retval;
        convert(retval, value);
        Py_DECREF(value); 
	    return retval;
	};
};

template<typename P1>
class VoidClassMethod1p : public ClassMethodBase
{
public:
	VoidClassMethod1p(PyObject* pythonClassInstance, std::string methodName) 
		: ClassMethodBase(pythonClassInstance, methodName, 1)	{};

	void execute( P1 param1) 
	{ 
        argCount = 0;
        addArg(param1);
		PyObject* value = executeFunction();
        Py_DECREF(value); 
	};
};

template<typename R>
class ClassMethod : public ClassMethodBase
{
public:
	ClassMethod(PyObject* pythonClassInstance, std::string methodName) 
		: ClassMethodBase(pythonClassInstance, methodName, 0)	{};

	R execute() 
	{ 
		PyObject* value = executeFunction();
	    R retval;
        convert(retval, value);
        Py_DECREF(value); 
	    return (R)retval;
	};

};

class VoidClassMethod : public ClassMethodBase
{
public:
	VoidClassMethod(PyObject* pythonClassInstance, std::string methodName) 
		: ClassMethodBase(pythonClassInstance, methodName, 0)	{};

	void execute1() 
	{ 
		PyObject* value = executeFunction();

        Py_DECREF(value); 
	};

};
}