#ifndef CONCEPT_INTERFACE_HPP
#define CONCEPT_INTERFACE_HPP

#include <concepts>
#include <utility>

template <typename T>
concept ConceptInterface = requires {
    { std::declval<T>().inc(int{}) } noexcept -> std::same_as<void>;
    { std::declval<const T>().getCounter() } noexcept -> std::same_as<int>;
};

#endif
