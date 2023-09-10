#ifndef INTERFACE_HPP
#define INTERFACE_HPP

class Interface {
  public:
    explicit Interface() = default;
    virtual ~Interface() = default;

    Interface(const Interface &) = delete;
    Interface(Interface &&) noexcept = delete;

    auto operator=(const Interface &) -> Interface & = delete;
    auto operator=(Interface &&) noexcept -> Interface & = delete;

    virtual void inc(int n) noexcept = 0;
    [[nodiscard]] virtual auto getCounter() const noexcept -> int = 0;
};

#endif
