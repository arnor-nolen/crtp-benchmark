#ifndef CONCEPT_COUNTER_HPP
#define CONCEPT_COUNTER_HPP

#include <concept_interface.hpp>

class ConceptCounter {
  public:
    explicit ConceptCounter(int counter) : m_counter{counter} {};

    void inc(int n) noexcept { m_counter += n; };

    [[nodiscard]]
    auto getCounter() const noexcept -> int {
        return m_counter;
    };

  private:
    int m_counter{0};
};

static_assert(ConceptInterface<ConceptCounter>);

#endif
