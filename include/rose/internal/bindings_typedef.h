#pragma once

///////////////////////////////////////////////////
// AUTOGENERATED: 
// DO NOT EDIT THIS FILE
// EDIT: roselib/internal/generate_bindings.py
// Bindings hash: 37325
///////////////////////////////////////////////////
#include <rose/hash.h>

typedef void * (*rose_internal_create_or_fetch_worldstate_ft)(int, const rose::reflection::TypeInfo & type);
typedef void (*rose_internal_register_utility_class_instance_ft)(int, rose::hash_value type_id, void * instance);
typedef void * (*rose_internal_get_utility_class_instance_ft)(int, rose::hash_value type_id);
typedef int (*rose_filewatcher_watch_path_ft)(int, const char * path);
typedef bool (*rose_filewatcher_unwatch_path_ft)(int, int id);
