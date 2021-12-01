#pragma once
#include <iostream>
#include <sstream> 
#include "PythonModule.h"

namespace EmbededPython
{
Module::Module(std::string moduleName, std::string pathToModule)
{
	_putenv_s("PYTHONPATH", pathToModule.c_str());
	Py_Initialize();
	_moduleName = PyUnicode_DecodeFSDefault(moduleName.c_str());
	module = PyImport_Import(_moduleName);
    Py_DECREF(_moduleName);
}

Module::~Module()
{
	//Py_DECREF(module);
	Py_Finalize();
}

void Module::setPath(std::string path)
{
	if(!path.empty())
	{
		PyObject* sysPath = PySys_GetObject("path");
#ifdef PYTHON_3
		PyList_Append(sysPath, PyUnicode_FromString(path.c_str()));
#else
		PyList_Append(sysPath, PyString_FromString(path.c_str()));
#endif
	}
}
}