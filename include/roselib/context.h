#pragma once

#include <rosemath.h>
#include <rose/eventqueue.h>
#include <components/components.h>
#include <components/padevents.h>

#define ROSE_EXPORT extern "C" __declspec(dllexport)

namespace rose {
typedef unsigned long long GenericHandle;
static_assert(sizeof(GenericHandle) == 8, "Size of GenericAssetID must be 64 Bit");

struct GenericAssetID {
  GenericHandle ID;

  bool ok() const { return ID != 0; }
};
static_assert(sizeof(GenericAssetID) == 8, "Size of GenericAssetID must be 64 Bit");

struct Mesh : public GenericAssetID {};
static_assert(sizeof(Mesh) == 8, "Size of Mesh  must be 64 Bit");

struct Texture : public GenericAssetID {};
static_assert(sizeof(Texture) == 8, "Size of Texture must be 64 Bit");

struct Context {
  virtual ~Context() {}
# define FUNC_SIG(ns, rt, name, sig, call) virtual rt ns##_##name sig = 0;
# define PROC_SIG(ns, name, sig, call) virtual void ns##_##name sig = 0;
# include <roselib/internal/funcs.inc>
# undef FUNC_SIG
# undef PROC_SIG
};
}
