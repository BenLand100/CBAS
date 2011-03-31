/**
 *  Copyright 2007 by Benjamin J. Land (a.k.a. BenLand100)
 *
 *  This file is part of the CBAS C-Based Autoing System
 *
 *  CBAS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  CBAS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CBAS. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 *This file should go in the CBAS/Includes directory, it contains the linker 
 *information and the exported function defs. You are not limited in naming 
 *convention, or number of Include files, however, care should be taken to 
 *avoid problems. In adition to this file, your compiled library file should go
 *in the CBAS/Lib directory for linking.
 */


/**
 *Ensure that this file is only included once, speeds compiling time.
 */
#ifndef EXAMPLEPLUGIN_H
#define	EXAMPLEPLUGIN_H

/**
 *Notify CBAS to link in your library if this header is included. Only used by
 *CBAS, this will not work elsewhere. If you use other libraries (including 
 *libcbas) you should not have to include their link directives because their 
 *headers should already include them. Just ensure that your compiler links 
 *against the required libraries.
 */
#warning links ExamplePlugin

/**
 *EXPORT is defined as an export or inport depending on whether the library is 
 *being compiled (BUILD_DLL is defined) or being used (BUILD_DLL is not defined)
 */
#ifdef BUILD_DLL
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __declspec(dllimport)
#endif

/**
 *Either define your methods here, or in another include file, just be sure that
 *the include files contain the #warning links [library] directive so that the
 *correct library is linked by CBAS.
 */
EXPORT double divide(double a, double b);
EXPORT int factorial(int a);
EXPORT void message(char* title, char* message);


#endif

