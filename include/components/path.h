#pragma once

struct path {
	//@String
	char string[260];

	bool append(const char * element);
};

#ifdef ROSE_PATH_IMPL
bool path::append(const char * element) {
	//implement me later
	return true;
}
#endif