#-------------------------------------------------------------------------------
# Name:        module1
# Purpose:     call class methods from C++ lib
#
# Author:      bkumpar
#
# Created:     22.09.2019
# Copyright:   (c) bkumpar 2019
# Licence:     <your licence>
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# ctypes type 	|	C type			    |	Python type
#-------------------------------------------------------------------------------
# c_bool		|	_Bool			    |	bool (1)
# c_char		|	char			    |	1-character string
# c_wchar		|	wchar_t			    |	1-character unicode string
# c_byte		|	char			    |	int/long
# c_ubyte		|	unsigned char		|	int/long
# c_short		|	short			    |	int/long
# c_ushort		|	unsigned short		|	int/long
# c_int			|	int			        |	int/long
# c_uint		|	unsigned int		|	int/long
# c_long		|	long			    |	int/long
# c_ulong		|	unsigned long	    |	int/long
# c_longlong	|	__int64             |
#			    |	long long		    |	int/long
# c_ulonglong	|	unsigned __int64    |
#		    	|	unsigned long long	|	int/long
# c_float 		|	float			    |	float
# c_double		|	double 			    |	float
# c_longdouble  |	long double		    |	float
# c_char_p		|	char * (NUL terminated)	    |	string or None
# c_wchar_p		|	wchar_t * (NUL term.)	    |	unicode or None
# c_void_p		|	void * 			    |	int/long or None
#------------------------------------------------------------------------------


from ctypes import cdll
lib = cdll.LoadLibrary('./PythonExtensions.dll')

class Extension1(object):

# something like forward declarations
    def message1(self):
        pass

    def message2(self):
        pass
    
    def message3(self):
        pass

    def product(self, d1, d2):
        pass

    def myPi(self):
        pass
    
    def myInt(self):
        pass

    def __init__(self):
        self.obj = lib.newExtension1()
        self.message1 = lib.message1
        self.message2 = lib.message2
        self.message3 = lib.message3
        self.product =  lib.product
        self.myPi = lib.myPi
        self.myInt = lib.myInt


if __name__ == '__main__':
    print('test:')
    
    print(2.0 * 3.0)
    ex = Extension1()
    dp = ex.myPi()
    print( dp)

    i = ex.myInt()
    print( repr( i))

 #   ex.message1()
 #   ex.message2()
 #   ex.message3()
 #result = ex.product(1, 2)
    
