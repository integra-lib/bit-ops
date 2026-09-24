#pragma once
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace hwlib::utilities
{

/// @brief Assemble an unsigned integer from individual bytes LSB-first
///
/// @tparam ReturnType The type of an integer to assemble
/// @param first The least significant byte
/// @param args A parameter pack with the rest of the bytes
template<
    typename ReturnType, typename... Args,
    typename = std::enable_if_t<(sizeof(ReturnType) > sizeof...(Args)) && std::is_integral_v<ReturnType> &&
                                std::is_unsigned_v<ReturnType> && !std::is_same_v<bool, std::remove_cv_t<ReturnType>> &&
                                (... && std::is_same_v<std::uint8_t, Args>)>>
[[nodiscard]] constexpr ReturnType AssembleBytes(std::uint8_t first, Args... args) noexcept
{
    if constexpr (sizeof...(Args) > 0U)
    {
        return static_cast<ReturnType>(first | AssembleBytes<ReturnType>(args...) << 8U);
    }
    return first;
}

static_assert(AssembleBytes<std::uint16_t>(std::uint8_t{0x12U}, std::uint8_t{0x34U}) == 0x3412U);

/// @brief Extract a single byte from an unsigned integer by its index
///
/// @tparam INDEX A zero-based index of a byte to extract starting from the
/// least significant byte
/// @param value An integer value to extract a byte from it
/// @return A byte at the specified index of the value param
template<std::size_t INDEX, typename Value,
         typename = std::enable_if_t<std::is_integral_v<Value> && std::is_unsigned_v<Value> &&
                                     !std::is_same_v<bool, std::remove_cv_t<Value>> && (sizeof(Value) > INDEX)>>
[[nodiscard]] constexpr std::uint8_t GetByteByIndex(Value value) noexcept
{
    return static_cast<std::uint8_t>(Value{0xFFU} & (value >> 8U * INDEX));
}

static_assert(GetByteByIndex<0>(0x0123456789ABCDEFU) == 0xEFU);
static_assert(GetByteByIndex<7>(0x0123456789ABCDEFU) == 0x01U);

} // namespace hwlib::utilities
