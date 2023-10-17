#include <chrono>
#include <cstdlib>
#include <fmt/format.h>
#include <memory>
#include <variant>

#include <concept_counter.hpp>
#include <crtp_counter.hpp>
#include <lambda_counter.hpp>
#include <poly_counter.hpp>

namespace {
constexpr size_t number_of_loops = 100000;
} // namespace

void test(PolyInterface *counter) {
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

void conceptTest(ConceptInterface auto *counter) {
    for (auto i = 0u; i < number_of_loops; ++i) {
        for (auto j = 0u; j < i; ++j) {
            counter->inc(static_cast<int>(j));
        }
    };
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

    auto counter = std::make_unique<PolyCounter>(0);
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

    auto conceptCounter = std::make_unique<ConceptCounter>(0);
    benchmark(conceptCounter, conceptTest<ConceptCounter>, "Concepts");
    fmt::print("Counter value: {}.\n\n", conceptCounter->getCounter());

    return EXIT_SUCCESS;
}
