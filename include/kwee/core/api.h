#pragma once

#ifdef _WIN32
	#ifdef KWEE_BUILD
		#define KWEEAPI __declspec(dllexport)
	#else
		#define KWEEAPI __declspec(dllimport)
	#endif
#else
	#define KWEEAPI
#endif