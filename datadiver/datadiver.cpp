/*
	datadriver.hpp

	Datadiver library

    Copyright (C) Bret Curtis 2014

    This file is part of Datadiver.cpp

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

#include "datadiver.h"

typedef struct DD_context {
	const char *input_path;
	const char *output_path;
	uint32_t *file_location;
	uint32_t *file_type;
	uint32_t files_found;
} DD_context;


/*
 * Creates the "handle" or context that we use through the life of the file or buffer we are
 * working with.
 *
 * :returns: dd_handle* -- (Just the pointer to the location in memory we are working on.)
 */
DD_SYMBOL dd_handle * DataDiver_Setup (void){

	return dd_handle;
}
