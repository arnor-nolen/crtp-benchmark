#ifndef CRTP_INTERFACE_HPP
#define CRTP_INTERFACE_HPP

template <typename T>
class CrtpInterface {
  public:
    ~CrtpInterface() = default;

    CrtpInterface(const CrtpInterface &) = delete;
    CrtpInterface(CrtpInterface &&) noexcept = delete;

    auto operator=(const CrtpInterface &) -> CrtpInterface & = delete;
    auto operator=(CrtpInterface &&) noexcept -> CrtpInterface & = delete;

    void inc(int n) noexcept { underlying().inc(n); }
    [[nodiscard]] auto getCounter() const noexcept -> int {
        return underlying().getCounter();
    }

    [[nodiscard]] auto underlying() noexcept -> T & {
        return static_cast<T &>(*this);
    }
    [[nodiscard]] auto underlying() const noexcept -> const T & {
        return static_cast<const T &>(*this);
    }

  private:
    explicit CrtpInterface() = default;
    friend T;
};

#endif
