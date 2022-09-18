# Indexed Set: Unordered set with constant-time uniform sampling

```c++
#include <iostream>

#include <indexed_set/indexed_set.hpp>

int main() {
  indexed_set::indexed_set<std::size_t> iset;
  iset.insert(1);
  iset.insert(2);
  iset.insert(3);

  iset.erase(2);

  std::cout << iset.size() << "\n";

  std::mt19937_64 gen;
  std::cout << indexed_set::random_sample(iset, gen) << "\n";
}
```

The function `random_sample` throws an exception when `indexed_set` is empty.
You can alternatively use `try_random_sample` which returns an optional to avoid
exceptions.
