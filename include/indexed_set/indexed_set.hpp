#ifndef INCLUDE_INDEXED_SET_INDEXED_SET_HPP_
#define INCLUDE_INDEXED_SET_INDEXED_SET_HPP_

#include <random>
#include <unordered_map>
#include <vector>
#include <optional>

namespace indexed_set {
  template <typename Key>
  class indexed_set {
  public:
    using key_type = Key;
    using value_type = Key;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;

    indexed_set() = default;

    const_iterator begin() const;
    iterator begin();
    const_iterator end() const;
    iterator end();

    size_t size() const;
    bool contains(const key_type& key) const;
    bool empty() const;
    const_reference at(size_t index) const;

    std::size_t erase(const key_type& key);
    bool insert(const key_type& key);

  private:
    std::vector<key_type> _values;
    std::unordered_map<key_type, size_t> _indices;
  };

  template <class Key, std::uniform_random_bit_generator Gen>
  std::optional<Key>
  try_random_sample(const indexed_set<Key>& iset, Gen& gen);

  template <class Key, std::uniform_random_bit_generator Gen>
  Key random_sample(const indexed_set<Key>& iset, Gen& gen);
}  // namespace indexed_set

#include "../../src/indexed_set.tpp"

#endif  // INCLUDE_INDEXED_SET_INDEXED_SET_HPP_
