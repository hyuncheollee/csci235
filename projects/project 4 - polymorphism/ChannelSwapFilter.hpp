/*
Hyuncheol Lee
2025/11/15

this file is the header file for ChannelSwapFilter
*/

#pragma once

#include "ImageFilter.hpp"

#include <utility>

class ChannelSwapFilter : public ImageFilter {
private:
    Channel c1_;
    Channel c2_;

public:
    /**
     * Constructs a ChannelSwapFilter with two channels
     * to swap and an optional strength.
     *
     * @param c1 The first channel as a Channel Enum
     * @param c2 The second channel as a Channel Enum
     * @param strength A double between [0.0, 1.0] indicating overlay intensity. Defaults to 1.0 if omitted.
     */
    ChannelSwapFilter(Channel c1, Channel c2, double strength = 1.0);

    /**
     * Sets the channels to be swapped by the filter.
     *
     * @param c1 The first channel to swap as a Channel enum
     * @param c2 The second channel to swap as a Channel enum
     */
    void setSwapChannels(Channel c1, Channel c2);

    /**
     * Getter for swapped RGB channels.
     *
     * @return A std::pair of Channels representing the swapped channels.
     */
    std::pair<Channel, Channel> getSwapChannels() const;

    /**
     * Swaps the values of the filter's channels for every pixel,
     * then blends with the original pixel by strength.
     */
    void apply(ImageFile& image) const override;

    /**
     * Returns the filter name and swap details.
     * Example: "ChannelSwapper [RED, BLUE]".
     */
    std::string name() const override;
};
