/*
	datadriver.cpp

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

typedef struct _dd_context {
	const char *input_path;
	const char *output_path;
	uint32_t *file_location;
	uint32_t *file_type;
	uint32_t files_found;
} _dd_context;


DD_SYMBOL dd_context DataDiver_CreateContext (void) {
	dd_context context = new _dd_context;

	return (context);
}
