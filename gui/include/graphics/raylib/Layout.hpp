/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Layout.hpp
*/

#pragma once

#include <algorithm>
#include "IGraphicalModule.hpp"
#include "raylib-cpp.hpp"

namespace Zappy
{
    // The 2D overlays were authored against GUI_WIDTH x GUI_HEIGHT. Those macros stay
    // the *design* resolution; these helpers map a design-space coordinate onto the
    // window's live size, so the HUD anchors to the real edges at any resolution.
    //
    //   left(13)                 -> 13px from the left edge, scaled
    //   right(1657)              -> keeps its distance to the right edge
    //   bottom(GUI_HEIGHT - 200) -> keeps its distance to the bottom edge
    //   s(25)                    -> a scaled size (font sizes, widths, margins)
    namespace Layout
    {
        inline int w(void) { return GetScreenWidth(); }
        inline int h(void) { return GetScreenHeight(); }

        // Uniform factor so text stays legible on large panels instead of only moving.
        inline float scale(void)
        {
            return std::min(static_cast<float>(w()) / static_cast<float>(GUI_WIDTH),
                static_cast<float>(h()) / static_cast<float>(GUI_HEIGHT));
        }

        inline int s(float designPx) { return static_cast<int>(designPx * scale()); }

        inline int left(float designX) { return s(designX); }
        inline int top(float designY) { return s(designY); }
        inline int right(float designX) { return w() - s(GUI_WIDTH - designX); }
        inline int bottom(float designY) { return h() - s(GUI_HEIGHT - designY); }

        // Centres an element of the given design-space size.
        inline int centerX(float designWidth) { return (w() - s(designWidth)) / 2; }
        inline int centerY(float designHeight) { return (h() - s(designHeight)) / 2; }
    } // namespace Layout
} // namespace Zappy
