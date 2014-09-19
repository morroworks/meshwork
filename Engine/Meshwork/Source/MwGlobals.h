#pragma warning(disable:4231)
#pragma once

#if defined (MWDLLCOMPILE)
#	define MWDLLCLASS __declspec(dllexport)
#	define MWDLLTEMPLATEMEMBER
#else
#	define MWDLLCLASS __declspec(dllimport)
#	define MWDLLTEMPLATEMEMBER extern
#endif
