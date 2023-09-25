#ifndef POLY_COUNTER_HPP
#define POLY_COUNTER_HPP

#include <poly_interface.hpp>

class PolyCounter : public PolyInterface {
  public:
    explicit PolyCounter(int counter) : m_counter{counter} {};

    void inc(int n) noexcept override { m_counter += n; };

    [[nodiscard]]
    auto getCounter() const noexcept -> int override {
        return m_counter;
    };

  private:
    int m_counter{0};
};

#endif
