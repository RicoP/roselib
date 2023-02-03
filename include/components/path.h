#pragma once

#include <serializer/serializer.h>

struct Path {
	//@String
	char string[260] = "";

	bool operator==(const Path & rhs) { return strcmp(string, rhs.string) == 0; }
	bool operator!=(const Path & rhs) { return strcmp(string, rhs.string) != 0; }
};

namespace rose {

inline void        serialize(Path &o, ISerializer &s) {
	rose::serialize(o.string, s);
}
inline void      deserialize(Path &o, IDeserializer &s) {
	rose::deserialize(o.string, s);
}

}