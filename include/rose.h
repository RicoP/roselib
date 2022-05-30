#pragma once

#include <components/components.h>
#include <roselib/context.h>
#include <rose/eventqueue.h>

namespace rose {
# define FUNC_SIG(ns, rt, name, sig, call) \
  namespace ns {                           \
    inline rt name sig;                    \
  }

# define PROC_SIG(ns, name, sig, call) \
  FUNC_SIG(ns, void, name, sig, call)

# include <roselib/internal/funcs.inc>

  namespace events {
  template <class T>
  void broadcast(T& event) {
    internal::get_event_queue().push_back(event);
  }
  }  // namespace events
}

#undef FUNC_SIG
#undef PROC_SIG

#include <rose/internal/bindings_subsystem.h>