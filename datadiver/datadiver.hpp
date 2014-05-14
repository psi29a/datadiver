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

/* for WildMidi_GetString */
#define DD_GS_VERSION		0x0001

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

struct _DD_Info {
	char *copyright;
	uint32_t current_sample;
	uint32_t approx_total_samples;
	uint16_t mixer_options;
	uint32_t total_midi_time;
};

typedef void midi;

DD_SYMBOL const char * DataDiver_GetString (uint16_t info);
DD_SYMBOL long DataDiver_GetVersion (void);
DD_SYMBOL int DataDiver_Init (const char *config_file, uint16_t rate, uint16_t mixer_options);
DD_SYMBOL midi * DataDiver_Open (const char *midifile);
DD_SYMBOL midi * DataDiver_OpenBuffer (uint8_t *midibuffer, uint32_t size);
DD_SYMBOL int DataDiver_SetOption (midi *handle, uint16_t options, uint16_t setting);
DD_SYMBOL int DataDiver_GetOption (midi *handle, uint16_t options, uint16_t setting);
DD_SYMBOL int DataDiver_Shutdown (void);


#if defined(__cplusplus)
}
#endif

#endif /* DATADIVER_LIB_H */

