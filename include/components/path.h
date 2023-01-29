#pragma once

#include <serializer/serializer.h>

struct path {
	//@String
	char string[260] = "";

	bool append(const char * element);

	bool operator==(const path & rhs) { return strcmp(string, rhs.string) == 0; }
	bool operator!=(const path & rhs) { return strcmp(string, rhs.string) != 0; }
};

namespace rose::ecs {
inline void        serialize(path &o, ISerializer &s) {
	rose::ecs::serialize(o.string, s);
}
inline void      deserialize(path &o, IDeserializer &s) {
	rose::ecs::deserialize(o.string, s);
}
}


#ifdef ROSE_PATH_IMPL
bool path::append(const char * element) {
	//implement me later
	return true;
}
#endif
