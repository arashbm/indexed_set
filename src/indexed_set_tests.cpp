#include <vector>
#include <random>
#include <cmath>
#include <unordered_map>

#include <catch2/catch.hpp>

#include <indexed_set/indexed_set.hpp>

using Catch::Matchers::UnorderedEquals;

TEST_CASE("constructs correctly", "[indexed_set]") {
  indexed_set::indexed_set<std::size_t> iset;
  REQUIRE(iset.size() == 0);
  REQUIRE(iset.empty());
}

TEST_CASE("inserting items", "[insert]") {
  indexed_set::indexed_set<std::size_t> iset;
  REQUIRE(iset.insert(42));
  REQUIRE(iset.size() == 1);
  REQUIRE_FALSE(iset.empty());
  REQUIRE(iset.contains(42));
  REQUIRE(iset.at(0) == 42);

  REQUIRE_FALSE(iset.insert(42));
  REQUIRE(iset.size() == 1);

  iset.insert(43);
  iset.insert(44);
  iset.insert(45);

  REQUIRE_THAT(std::vector<std::size_t>(iset.begin(), iset.end()),
      UnorderedEquals(std::vector<std::size_t>{42, 43, 44, 45}));
}

TEST_CASE("erasing items", "[erase]") {
  indexed_set::indexed_set<std::size_t> iset;
  iset.insert(42);


  REQUIRE(iset.erase(42) == 1);
  REQUIRE(iset.size() == 0);
  REQUIRE(iset.empty());
  REQUIRE_FALSE(iset.contains(42));

  REQUIRE(iset.erase(42) == 0);
  REQUIRE(iset.size() == 0);
  REQUIRE(iset.empty());
}

TEST_CASE("random sample", "[try_random_sample]") {
  indexed_set::indexed_set<std::size_t> iset;

  std::mt19937_64 gen(42);
  REQUIRE_THROWS(indexed_set::random_sample(iset, gen));
  REQUIRE_FALSE(indexed_set::try_random_sample(iset, gen));

  std::size_t n = 10;
  for (std::size_t i = 0; i < n; i++)
    iset.insert(i);

  std::unordered_map<std::size_t, std::size_t> counts;
  std::size_t s = 100000;
  for (std::size_t i = 0; i < s; i++)
    counts[indexed_set::try_random_sample(iset, gen).value()]++;

  double mean = static_cast<double>(s)/static_cast<double>(n);
  double sigma = std::sqrt(mean);
  REQUIRE(std::ranges::all_of(counts, [mean, sigma](
          const std::pair<std::size_t, std::size_t> count) {
            return static_cast<double>(count.second) >= mean - 3*sigma &&
              static_cast<double>(count.second) <= mean + 3*sigma;
        }));
}

struct blaah {
  std::size_t i, j;
  auto operator<=>(const blaah&) const = default;
};

struct blaah_hasher {
  std::size_t operator()(const blaah& b) const noexcept {
    return b.i ^ (b.j + 0x9E3779B97F4A7C15 + (b.i << 6) + (b.i >> 2));
  }
};

TEST_CASE("constructs with custom hasher", "[hasher]") {
  indexed_set::indexed_set<blaah, blaah_hasher> iset;
  REQUIRE(iset.size() == 0);
  REQUIRE(iset.empty());

  REQUIRE(iset.insert({42, 42}));
  REQUIRE(iset.size() == 1);
  REQUIRE_FALSE(iset.empty());

  REQUIRE(iset.insert({42, 43}));
  REQUIRE(iset.size() == 2);
}
