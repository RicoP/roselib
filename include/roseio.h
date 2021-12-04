#pragma once

#include <components/components.h>
#include <serializer/jsonserializer.h>

#include <cstdio>

namespace rose {
namespace io {

enum class Folder {
	Working
};

namespace json {

template<class COMPONENT>
int write(COMPONENT & component, ::rose::io::Folder folder, const char* name) {
  assert(folder == ::rose::io::Folder::Working);
  FILE* f = fopen(name, "wb");
  if(!f) return 1;
  JsonSerializer jsons(f);
  rose::ecs::serialize(component, jsons);
  fclose(f);
  return 0;
}


template <class COMPONENT>
void read_from_string(COMPONENT& component, char * json) {
  JsonDeserializer jsond(json);
  deserialize(component, jsond);
}

template <class COMPONENT>
bool read(COMPONENT& component, ::rose::io::Folder folder, const char* name) {
  assert(folder == ::rose::io::Folder::Working);
  FILE* f = fopen(name, "rb");

  if (!f) {
    // TODO: have an option to just return default value if file doesn't exist.
    construct_defaults(component);
    return false;
  }

  assert(f);

  fseek(f, 0, SEEK_END);
  long length = ftell(f) + 1;

  fseek(f, 0, SEEK_SET);
  // TODO: Actually stream the file instead.
  char* buffer = (char*)std::malloc(length);
  assert(buffer);

  fread(buffer, 1, length, f);
  buffer[length - 1] = 0;
  fclose(f);

  read_from_string(component, buffer);

  std::free(buffer);

  return true;
}

template<class COMPONENT>
COMPONENT read(::rose::io::Folder folder, const char* name) {
  COMPONENT component;
  read(component, folder, name);
  return component;
}

}
}
}
