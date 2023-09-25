#ifndef POLY_INTERFACE_HPP
#define POLY_INTERFACE_HPP

class PolyInterface {
  public:
    explicit PolyInterface() = default;
    virtual ~PolyInterface() = default;

    PolyInterface(const PolyInterface &) = delete;
    PolyInterface(PolyInterface &&) noexcept = delete;

    auto operator=(const PolyInterface &) -> PolyInterface & = delete;
    auto operator=(PolyInterface &&) noexcept -> PolyInterface & = delete;

    virtual void inc(int n) noexcept = 0;

    [[nodiscard]]
    virtual auto getCounter() const noexcept -> int = 0;
};

#endif
