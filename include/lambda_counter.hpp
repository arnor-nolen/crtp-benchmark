#ifndef LAMBDA_COUNTER_HPP
#define LAMBDA_COUNTER_HPP

class LambdaCounter {
  public:
    explicit LambdaCounter(int counter) : m_counter{counter} {};

    void inc(int n) noexcept { m_counter += n; };

    [[nodiscard]]
    auto getCounter() const noexcept -> int {
        return m_counter;
    };

  private:
    int m_counter{0};
};

#endif
