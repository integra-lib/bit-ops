# bit-ops

Assemble and split unsigned integers byte-wise, all constexpr.

Part of [integra-lib](https://gitlab.integrasources.com/internal-projects/integra-lib).
Header-only C++20, no exceptions, no RTTI.

## Use it

```bash
git submodule add ../bit-ops.git external/integra/bit-ops
```

```cmake
add_subdirectory(external/integra/bit-ops)
target_link_libraries(app PRIVATE Integra::bit_ops)
```

```cpp
#include <integra/bit_ops.hpp>
```

## Develop it

```bash
cmake -S . -B build && cmake --build build -j && ctest --test-dir build
```

Tests are built only when this repository is the top-level project, so a consumer
never builds them. Style and pipeline come from the `ci-shared` submodule; run
`git submodule update --init` before `pre-commit`.
