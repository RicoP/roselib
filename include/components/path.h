#pragma once

#include <serializer/serializer.h>

struct path {
	//@String
	char string[260];

	bool append(const char * element);
};

inline void        serialize(path &o, ISerializer &s) {
	rose::ecs::serialize(o.string, s);
}
void      deserialize(path &o, IDeserializer &s) {
	rose::ecs::deserialize(o.string, s);
}


#ifdef ROSE_PATH_IMPL
bool path::append(const char * element) {
	//implement me later
	return true;
}
#endif