/*
	datadriver.h

	Datadiver library

    Copyright (C) Bret Curtis 2014

    This file is part of Datadiver.

    Datadiver is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    Datadiver is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DATADIVER_LIB_H
#define DATADIVER_LIB_H

/* set our symbol export visiblity */
#if defined _WIN32 || defined __CYGWIN__
  /* ========== NOTE TO WINDOWS DEVELOPERS:
   * If you are compiling for Windows and will link to the static library
   * (libWildMidi.a with MinGW, or wildmidi_static.lib with MSVC, etc),
   * you must define DATADIVER_STATIC in your project. Otherwise dllimport
   * will be assumed. */
# if defined(DATADIVER_BUILD) && defined(DLL_EXPORT)		/* building library as a dll for windows */
#  define DD_SYMBOL __declspec(dllexport)
# elif defined(DATADIVER_BUILD) || defined(DATADIVER_STATIC)	/* building or using static lib for windows */
#  define DD_SYMBOL
# else									/* using library dll for windows */
#  define DD_SYMBOL __declspec(dllimport)
# endif
#elif defined(DATADIVER_BUILD)
# if defined(SYM_VISIBILITY)	/* __GNUC__ >= 4, or older gcc with backported feature */
#  define DD_SYMBOL __attribute__ ((visibility ("default")))
/*
# elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590)
#  define DD_SYMBOL __attribute__ ((visibility ("default")))
*/
# elif defined(SYM_LDSCOPE)	/* __SUNPRO_C >= 0x550 */
#  define DD_SYMBOL __global
# else
#  define DD_SYMBOL
# endif
#else
#  define DD_SYMBOL
#endif

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

struct dd_context;
typedef dd_context* dd_handle;

/*!
 * Retrieves the version of the library.
 *
 * \return long (our version information in long format)
 */
DD_SYMBOL long DataDiver_GetVersion (void);

/*!
 * Creates the "handle" or context that we use through the life of the file or buffer we are
 * working with.
 *
 * \return dd_handle (a pointer to the location in memory we are working on.)
 */
DD_SYMBOL dd_handle * DataDiver_Setup (void);

/*!
 * Shuts down the "handle" or context and releases the allocated memory.
 *
 * \param context (a pointer to our context handle)
 * \return int (a boolean)
 */
DD_SYMBOL int DataDiver_Shutdown (dd_handle *context);

DD_SYMBOL dd_handle * DataDiver_Open (const char *midifile);

DD_SYMBOL dd_handle * DataDiver_OpenBuffer (uint8_t *buffer, uint32_t size);

DD_SYMBOL int DataDiver_SetOption (dd_handle *context, uint16_t options, uint16_t setting);

DD_SYMBOL int DataDiver_GetOption (dd_handle *context, uint16_t options);

#if defined(__cplusplus)
}
#endif

#endif /* DATADIVER_LIB_H */

