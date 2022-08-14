#pragma once

#ifdef _WIN32

	
	#ifdef KWEE_ENGINE
		#define KWEEAPI __declspec(dllexport)
	#else
		#define KWEEAPI __declspec(dllimport)
	#endif

#else

	#error Unknown os!

#endif