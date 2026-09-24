#include <gtest/gtest.h>

#include <cstdint>
#include <hwlib/utilities/bit_ops.hpp>

namespace
{

TEST(BitOpsTest, AssemblesTwoBytesLsbFirst)
{
    EXPECT_EQ(hwlib::utilities::AssembleBytes<std::uint16_t>(std::uint8_t{0x12U}, std::uint8_t{0x34U}), 0x3412U);
}

TEST(BitOpsTest, AssemblesFourBytesLsbFirst)
{
    EXPECT_EQ(hwlib::utilities::AssembleBytes<std::uint32_t>(
                  std::uint8_t{0x78U}, std::uint8_t{0x56U}, std::uint8_t{0x34U}, std::uint8_t{0x12U}),
              0x12345678U);
}

TEST(BitOpsTest, AssemblesASingleByte)
{
    EXPECT_EQ(hwlib::utilities::AssembleBytes<std::uint16_t>(std::uint8_t{0xABU}), 0x00ABU);
}

TEST(BitOpsTest, ExtractsEveryByteOfAWord)
{
    constexpr std::uint64_t VALUE = 0x0123456789ABCDEFU;
    EXPECT_EQ(hwlib::utilities::GetByteByIndex<0>(VALUE), 0xEFU);
    EXPECT_EQ(hwlib::utilities::GetByteByIndex<1>(VALUE), 0xCDU);
    EXPECT_EQ(hwlib::utilities::GetByteByIndex<6>(VALUE), 0x23U);
    EXPECT_EQ(hwlib::utilities::GetByteByIndex<7>(VALUE), 0x01U);
}

TEST(BitOpsTest, RoundTripsThroughBytes)
{
    constexpr std::uint16_t VALUE = 0xBEEFU;
    EXPECT_EQ(hwlib::utilities::AssembleBytes<std::uint16_t>(
                  hwlib::utilities::GetByteByIndex<0>(VALUE), hwlib::utilities::GetByteByIndex<1>(VALUE)),
              VALUE);
}

} // namespace
