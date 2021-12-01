#pragma once
#include "StdAfx.h"
#include <Python.h>
#include <string>

#include "PythonModule.h"

namespace EmbededPython
{
	template<typename T>
	class Variable
	{
	public:
		Variable(Module* pythonModule, std::string variableName)
		{
			this->pythonModule = pythonModule;
			this->variableName = variableName;
		};
		~Variable() {};

		bool convert(int &outputValue, PyObject* inputValue)
		{
			outputValue = PyLong_AsLong(inputValue);
			return true;
		};

		bool convert(long &outputValue, PyObject* inputValue)
		{
			outputValue = PyLong_AsLong(inputValue);
			return true;
		};

		bool convert(double &outputValue, PyObject* inputValue)
		{
			outputValue = PyFloat_AsDouble(inputValue);
			return true;
		};

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
		};

		T value()
		{
			PyObject* value = PyObject_GetAttrString(pythonModule->module, variableName.c_str());
			T retval;
			convert(retval, value);
			Py_DECREF(value);
			return retval;
		};

	private:
		Module* pythonModule;
		std::string variableName;
	};
}