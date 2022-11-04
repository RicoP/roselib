#pragma once

namespace rose {
template <typename... Ts>
void unused(Ts const&...) { /* do nothing */ }
}  // namespace rose
