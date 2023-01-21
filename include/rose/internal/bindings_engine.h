#pragma once

///////////////////////////////////////////////////
// AUTOGENERATED: 
// DO NOT EDIT THIS FILE
// EDIT: roselib/internal/generate_bindings.py
// Bindings hash: 24331
///////////////////////////////////////////////////
#include <rose/hash.h>
#include <rose/world.h>
#include <rose/eventqueue.h>
#include <rose/internal/singletonregister.h>

#include <rose/internal/bindings_typedef.h>

namespace subsystem_bindings {
rose::EventQueue* g_rose_internal_get_event_queue(int);
void * g_rose_internal_create_or_fetch_worldstate(int, const rose::reflection::TypeInfo & type);
int g_rose_filewatcher_watch_path(int, const char * path);
bool g_rose_filewatcher_unwatch_path(int, int id);
}

template<class Lambda1, class Lambda2>
void inject_bindings(Lambda1 get_symbol_address, Lambda2 not_found_cb) {
  {
    auto fun = (rose_internal_get_event_queue_ft*)(get_symbol_address("c_rose_internal_get_event_queue"));
    if(fun) {
      *fun = subsystem_bindings::g_rose_internal_get_event_queue;
    } else {
      not_found_cb("c_rose_internal_get_event_queue");
    }
  }
  {
    auto fun = (rose_internal_create_or_fetch_worldstate_ft*)(get_symbol_address("c_rose_internal_create_or_fetch_worldstate"));
    if(fun) {
      *fun = subsystem_bindings::g_rose_internal_create_or_fetch_worldstate;
    } else {
      not_found_cb("c_rose_internal_create_or_fetch_worldstate");
    }
  }
  {
    auto fun = (rose_filewatcher_watch_path_ft*)(get_symbol_address("c_rose_filewatcher_watch_path"));
    if(fun) {
      *fun = subsystem_bindings::g_rose_filewatcher_watch_path;
    } else {
      not_found_cb("c_rose_filewatcher_watch_path");
    }
  }
  {
    auto fun = (rose_filewatcher_unwatch_path_ft*)(get_symbol_address("c_rose_filewatcher_unwatch_path"));
    if(fun) {
      *fun = subsystem_bindings::g_rose_filewatcher_unwatch_path;
    } else {
      not_found_cb("c_rose_filewatcher_unwatch_path");
    }
  }
}
