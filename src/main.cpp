#include <chrono>
#include <cstdlib>
#include <fmt/format.h>
#include <memory>
#include <variant>

#include <crtp_interface.hpp>
#include <interface.hpp>

namespace {
constexpr size_t number_of_loops = 40000;
} // namespace

// Polymorphic class.
class Counter : public Interface {
  public:
    explicit Counter(int counter) : m_counter{counter} {};
    void inc(int n) noexcept override { m_counter += n; };
    [[nodiscard]] auto getCounter() const noexcept -> int override {
        return m_counter;
    };

  private:
    int m_counter{0};
};

// CRTP class.
class CrtpCounter : public CrtpInterface<CrtpCounter> {
  public:
    explicit CrtpCounter(int counter) : m_counter{counter} {};
    void inc(int n) noexcept { m_counter += n; };
    [[nodiscard]] auto getCounter() const noexcept -> int { return m_counter; };

  private:
    int m_counter{0};
};

// No inheritance class.
class LambdaCounter {
  public:
    explicit LambdaCounter(int counter) : m_counter{counter} {};
    void inc(int n) noexcept { m_counter += n; };
    [[nodiscard]] auto getCounter() const noexcept -> int { return m_counter; };

  private:
    int m_counter{0};
};

void test(Interface *counter) {
    for (auto i = 0u; i < number_of_loops; ++i) {
        for (auto j = 0u; j < i; ++j) {
            counter->inc(static_cast<int>(j));
        }
    }
}

template <typename T>
void crtpTest(CrtpInterface<T> *counter) {
    for (auto i = 0u; i < number_of_loops; ++i) {
        for (auto j = 0u; j < i; ++j) {
            counter->inc(static_cast<int>(j));
        }
    }
}

void lambdaTest(std::variant<LambdaCounter> *counter) {
    for (auto i = 0u; i < number_of_loops; ++i) {
        for (auto j = 0u; j < i; ++j) {
            std::visit(
                [=](auto &counterImpl) {
                    counterImpl.inc(static_cast<int>(j));
                },
                *counter);
        }
    }
}

template <typename T, typename F>
void benchmark(const std::unique_ptr<T> &counter, F function,
               std::string_view name) {
    auto start = std::chrono::steady_clock::now();

    function(counter.get());

    auto end = std::chrono::steady_clock::now();
    fmt::print(
        "{}: {}ms.\n", name,
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count());
}

auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {

    auto counter = std::make_unique<Counter>(0);
    benchmark(counter, test, "Polymorphism");
    fmt::print("Counter value: {}.\n\n", counter->getCounter());

    auto crtpCounter = std::make_unique<CrtpCounter>(0);
    benchmark(crtpCounter, crtpTest<CrtpCounter>, "CRTP");
    fmt::print("Counter value: {}.\n\n", crtpCounter->getCounter());

    auto lambdaCounter = std::make_unique<std::variant<LambdaCounter>>(
        std::in_place_type<LambdaCounter>, 0);
    benchmark(lambdaCounter, lambdaTest, "No inheritance");
    fmt::print(
        "Counter value: {}.\n\n",
        std::visit(
            [](const auto &counterImpl) { return counterImpl.getCounter(); },
            *lambdaCounter));

    return EXIT_SUCCESS;
}
