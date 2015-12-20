
#ifdef WACCGL_VERSION
#warning "Macro WACCGL_VERSION was already defined! This may be WACCGL versioning problem!"
#error "Cannot use two versions of WACCGL - check out your dependencies."
#endif

/**
	WACCGL
		Windows Advanced Console Componental Graphics Library
		Version 2.0 Alpha
**/
#define WACCGL_VERSION 2.0
using namespace std;




#ifndef WACCGL_DISABLE_COMPATIBILITY_MODULE
#undef WACCGL_DISABLE_COMPATIBILITY_MODULE
#endif

#define _WIN32_WINNT 0x500
#include <windows.h>

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <functional>
#include <tchar.h>
#include <algorithm>
#include "compatibility.h"

namespace waccgl {

	#define uint unsigned int
	#define getid(NAME) (MACRO_STR__(NAME))
	#define assignid(NAME) NAME.id = MACRO_STR__(NAME);
	#define STR_VALUE(arg)      #arg
	#define MACRO_STR__(name) STR_VALUE(name)
	#define objectid std::string
	#define nullid "<null>"

	static bool runapp = true;

	class context;
	class scene_object;


	class context;
	class scene_object;


	std::string intToStr(int n) {
	     std::string tmp, ret;
	     if(n < 0) {
	          ret = "-";
	          n = -n;
	     }
	     do {
	          tmp += n % 10 + 48;
	          n -= n % 10;
	     }
	     while(n /= 10);
	     for(int i = tmp.size()-1; i >= 0; i--)
	          ret += tmp[i];
	     return ret;
	}


	double strToDouble(std::string s) {
		return atof(s.c_str());
	}

	std::string doubleToStr(double dbl) {
		std::ostringstream strs;
		strs << dbl;
		return strs.str();
	}

	int strToInt(std::string s) {
	     int tmp = 0, i = 0;
	     bool m = false;
	     if(s[0] == '-') {
	          m = true;
	          i++;
	     }
	     for(; i < s.size(); i++)
	          tmp = 10 * tmp + s[i] - 48;
	     return m ? -tmp : tmp;
	}

	inline std::string stringify(char c) {
		std::string s = "0";
		s[0] = c;
		return s;
	}

	inline std::string stringify(int n) {
		return intToStr(n);
	}

	inline std::string stringify(double d) {
		return doubleToStr(d);
	}

	inline std::string stringify(float f) {
		return doubleToStr((double)f);
	}

	#include "mathematics.h"
	#include "textstyle.h"
	#include "keys.h"
	#include "action.h"
	#include "console.h"
	#include "graphics.h"
	#include "controls.h"

	#undef uint
	#undef STR_VALUE
	#undef MACRO_STR__

};
