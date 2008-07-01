#ifndef DLL_H
#define	DLL_H

#ifdef BUILD_DLL
#warning links libcbas
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

#endif

