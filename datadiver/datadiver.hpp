/*
	datadriver.hpp

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

typedef struct DD_context {
	const char *input_path;
	const char *output_path;
	uint32_t *file_location;
	uint32_t *file_type;
	uint32_t files_found;
} DD_context;


DD_SYMBOL long DataDiver_GetVersion (void);
DD_SYMBOL DD_context * DataDiver_Open (const char *midifile);
DD_SYMBOL DD_context * DataDiver_OpenBuffer (uint8_t *buffer, uint32_t size);
DD_SYMBOL int DataDiver_SetOption (DD_context *context, uint16_t options, uint16_t setting);
DD_SYMBOL int DataDiver_GetOption (DD_context *context, uint16_t options);
DD_SYMBOL int DataDiver_Shutdown (DD_context *context);


#if defined(__cplusplus)
}
#endif

#endif /* DATADIVER_LIB_H */

