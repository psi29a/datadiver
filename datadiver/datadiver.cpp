/**
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
#include <cstddef>
//#include <boost/filesystem.hpp>

typedef struct _dd_input {
	_dd_input(void) {
		is_file = 0;
		//boost::filesystem::path = file_path("/");
		memory_location = NULL;
	}
	uint8_t is_file;
	//boost::filesystem::path file_path;
	uint8_t *memory_location;
} _dd_input;

typedef struct _dd_data {
	_dd_data(void) {
		location = NULL;
		type = NULL;
		files_found = 0;
	}
	uint32_t *location;
	uint32_t *type;
	uint32_t files_found;
} _dd_data;

typedef struct _dd_output {
	_dd_output(void) {
		path = "";
	}
	const char *path;
} _dd_output;

typedef struct _dd_context {
	_dd_context(void) :
			input(), data(), output() {
	}
	_dd_input input;
	_dd_data data;
	_dd_output output;

} _dd_context;

DD_SYMBOL DataDiver DataDiver_CreateContext(void) {
	DataDiver handle = new _dd_context();
	return (handle);
}
