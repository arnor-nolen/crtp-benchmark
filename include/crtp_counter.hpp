#ifndef CRTP_COUNTER_HPP
#define CRTP_COUNTER_HPP

#include <crtp_interface.hpp>

class CrtpCounter : public CrtpInterface<CrtpCounter> {
  public:
    explicit CrtpCounter(int counter) : m_counter{counter} {};

    void inc(int n) noexcept { m_counter += n; };

    [[nodiscard]] auto getCounter() const noexcept -> int { return m_counter; };

  private:
    int m_counter{0};
};

#endif
