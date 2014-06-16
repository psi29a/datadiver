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
#include <string>
#include <cstddef>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

typedef struct _dd_input {
	_dd_input(void) {
		is_file = false;
		file_path = "";
		pointer = NULL;
	}
	bool is_file;
	boost::filesystem::path file_path;
	uint8_t *pointer;
} _dd_input;

typedef struct _dd_files {
	_dd_files(void) {
		location = 0;
		type = 0;
	}
	uint32_t location;
	uint32_t type;
} _dd_files;

typedef struct _dd_output {
	_dd_output(void) {
		path = "";
	}
	boost::filesystem::path path;
} _dd_output;

typedef struct _dd_context {
	_dd_context(void) :
			input(), output() {
	}
	_dd_input input;
	_dd_output output;
	std::vector<_dd_files> files;

} _dd_context;

DD_SYMBOL DataDiver DataDiver_CreateContext(void) {
	DataDiver handle = new _dd_context();
	return (handle);
}

DD_SYMBOL int DataDiver_DestroyContext(DataDiver handle) {
	delete handle;
	return (0);
}

DD_SYMBOL int DataDiver_OpenFile(DataDiver handle, const char *path) {
	handle->input.file_path = path;
	printf("Help %s\n", handle->input.file_path.c_str());
	boost::iostreams::mapped_file_source file;
	int numberOfBytes = 64*1024*1024;	// In MiB
	file.open(path, numberOfBytes);

	// Check if file was successfully opened
	if(file.is_open()) {
		handle->input.pointer = (uint8_t *)file.data();
		uint8_t temp = handle->input.pointer[0];
		printf("Help  %02x\n" % temp);
		return (0);
	} else {
		return (1);
	}
}
