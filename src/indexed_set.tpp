namespace indexed_set {
  template <typename Key, typename Hash>
  typename indexed_set<Key, Hash>::const_iterator
  indexed_set<Key, Hash>::begin() const {
    return _values.begin();
  }

  template <typename Key, typename Hash>
  typename indexed_set<Key, Hash>::iterator
  indexed_set<Key, Hash>::begin() {
    return _values.begin();
  }

  template <typename Key, typename Hash>
  typename indexed_set<Key, Hash>::const_iterator
  indexed_set<Key, Hash>::end() const {
    return _values.end();
  }

  template <typename Key, typename Hash>
  typename indexed_set<Key, Hash>::iterator
  indexed_set<Key, Hash>::end() {
    return _values.end();
  }

  template <typename Key, typename Hash>
  std::size_t indexed_set<Key, Hash>::size() const {
    return _values.size();
  }

  template <typename Key, typename Hash>
  bool indexed_set<Key, Hash>::contains(const Key& key) const {
    return _indices.contains(key);
  }

  template <typename Key, typename Hash>
  bool indexed_set<Key, Hash>::empty() const {
    return _values.empty();
  }

  template <typename Key, typename Hash>
  typename indexed_set<Key, Hash>::const_reference
  indexed_set<Key, Hash>::at(std::size_t index) const {
    return _values.at(index);
  }

  template <typename Key, typename Hash>
  std::size_t indexed_set<Key, Hash>::erase(const Key& key) {
    auto it = _indices.find(key);
    if (it == _indices.end())
      return 0;

    std::size_t key_index = it->second;
    key_type original_key = _values.back();
    std::iter_swap(
        _values.begin() + static_cast<std::ptrdiff_t>(key_index),
        _values.end() - 1);
    _indices[original_key] = key_index;
    _values.pop_back();
    _indices.erase(it);
    return 1;
  }

  template <typename Key, typename Hash>
  bool indexed_set<Key, Hash>::insert(const Key& key) {
    if (_indices.contains(key))
      return false;
    _values.push_back(key);
    _indices.emplace(key, _values.size() - 1);
    return true;
  }

  template <typename Key, typename Hash, std::uniform_random_bit_generator Gen>
  std::optional<Key>
  try_random_sample(const indexed_set<Key, Hash>& iset, Gen& gen) {
    if (iset.empty())
      return std::nullopt;
    return iset.at(
        std::uniform_int_distribution<size_t>(0, iset.size() - 1)(gen));
  }

  template <typename Key, typename Hash, std::uniform_random_bit_generator Gen>
  Key random_sample(const indexed_set<Key, Hash>& iset, Gen& gen) {
    return try_random_sample(iset, gen).value();
  }
}  // namespace indexed_set
