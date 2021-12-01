#pragma once

#include "StdAfx.h"
#include <Python.h>
#include <string>

namespace EmbededPython
{
	class Module 
	{
	public:
		Module(std::string moduleName, std::string pathToModule );
		~Module();
		PyObject* module;
	private:
		void setPath(std::string path);
		PyObject* _moduleName;
	};

}