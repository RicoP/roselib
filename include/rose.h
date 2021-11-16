#pragma once

#include <components/components.h>
#include <roselib/context.h>

namespace rose {
# define FUNC_SIG(ns, rt, name, sig, call) \
  namespace ns {                           \
    inline rt name sig;                    \
  }

# define PROC_SIG(ns, name, sig, call) \
  FUNC_SIG(ns, void, name, sig, call)

# include <roselib/internal/funcs.inc>
}

#undef FUNC_SIG
#undef PROC_SIG
