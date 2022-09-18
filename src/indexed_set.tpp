namespace indexed_set {
  template <class Key>
  typename indexed_set<Key>::const_iterator indexed_set<Key>::begin() const {
    return _values.begin();
  }

  template <class Key>
  typename indexed_set<Key>::iterator indexed_set<Key>::begin() {
    return _values.begin();
  }

  template <class Key>
  typename indexed_set<Key>::const_iterator indexed_set<Key>::end() const {
    return _values.end();
  }

  template <class Key>
  typename indexed_set<Key>::iterator indexed_set<Key>::end() {
    return _values.end();
  }

  template <class Key>
  size_t indexed_set<Key>::size() const {
    return _values.size();
  }

  template <class Key>
  bool indexed_set<Key>::contains(const Key& key) const {
    return _indices.contains(key);
  }

  template <class Key>
  bool indexed_set<Key>::empty() const {
    return _values.empty();
  }

  template <class Key>
  typename indexed_set<Key>::const_reference
  indexed_set<Key>::at(size_t index) const {
    return _values.at(index);
  }

  template <class Key>
  std::size_t indexed_set<Key>::erase(const Key& key) {
    auto it = _indices.find(key);
    if (it == _indices.end())
      return 0;

    size_t key_index = it->second;
    key_type original_key = _values.back();
    std::iter_swap(
        _values.begin() + static_cast<std::ptrdiff_t>(key_index),
        _values.end() - 1);
    _indices[original_key] = key_index;
    _values.pop_back();
    _indices.erase(it);
    return 1;
  }

  template <class Key>
  bool indexed_set<Key>::insert(const Key& key) {
    if (_indices.contains(key))
      return false;
    _values.push_back(key);
    _indices.emplace(key, _values.size() - 1);
    return true;
  }

  template <class Key, std::uniform_random_bit_generator Gen>
  std::optional<Key>
  try_random_sample(const indexed_set<Key>& iset, Gen& gen) {
    if (iset.empty())
      return std::nullopt;
    return iset.at(
        std::uniform_int_distribution<size_t>(0, iset.size() - 1)(gen));
  }

  template <class Key, std::uniform_random_bit_generator Gen>
  Key random_sample(const indexed_set<Key>& iset, Gen& gen) {
    return try_random_sample(iset, gen).value();
  }
}  // namespace indexed_set
