#ifndef MODERN_UI_H
#define MODERN_UI_H

// MineBoost "modern" UI kit
// ---------------------------------------------------------------------
// Small, header-only set of Irrlicht draw2D helpers that give every
// MineBoost panel (settings menu chrome, category tiles, picker panels,
// in-game HUD preview boxes, etc.) a consistent look: rounded corners,
// a soft drop shadow, and translucent fills -- instead of the old sharp
// 1px-outline debug rectangles (SColor(255,255,0,255) / (255,255,0,0)
// placeholders) that were scattered across Menu.cpp and hud.cpp.
//
// Everything here is built purely out of Irrlicht's existing IVideoDriver
// primitives (draw2DRectangle for the straight edges/center, and
// draw2DVertexPrimitiveList triangle fans for the 4 rounded corners), so
// it needs no new textures, no shaders, and no CMakeLists.txt changes --
// just #include "gui/custom_menu/ModernUI.h" wherever it's used.
//
// Usage: replace the old
//     driver->draw2DRectangle(fillColor, rect);
//     driver->draw2DRectangleOutline(rect, borderColor);
// pairs with
//     ModernUI::panel(driver, rect, ModernUI::Radius, fillColor, borderColor);
// (or the lower-level roundedRectFilled/roundedRectOutline/dropShadow
// calls directly, for one-off cases that don't want the shadow, etc).

#include <irrlicht.h>
#include "irrlichttypes_extrabloated.h"
#include "IVideoDriver.h"
#include <vector>
#include <cmath>
#include <algorithm>

namespace ModernUI {

using namespace irr;

// Default corner radius / border thickness used throughout MineBoost's
// panels. Kept as named constants (rather than repeating "10"/"2"
// everywhere) so the whole UI's roundedness can be tuned from one place.
static const s32 Radius = 10;
static const s32 RadiusSmall = 6;
static const s32 BorderThickness = 2;

// Palette for the "аккуратный современный" (clean modern) redesign:
// dark, semi-transparent slate panels with a soft cyan-blue accent
// border, replacing the old flat near-opaque black + magenta/yellow
// debug outline combo.
static const video::SColor PanelFill(215, 24, 26, 34);       // translucent dark slate
static const video::SColor PanelFillLight(200, 34, 37, 48);  // slightly lighter, for nested/inner panels
static const video::SColor PanelBorder(255, 90, 150, 250);   // soft accent blue
static const video::SColor PanelBorderDim(140, 90, 150, 250);// dimmer accent, for less prominent panels
static const video::SColor ShadowColor(255, 0, 0, 0);        // shadow tint (alpha supplied separately)

// ---------------------------------------------------------------------
// Low-level: filled quarter-disc (one rounded corner), built as a
// triangle fan around `center` with radius `r`, spanning the 90 degree
// arc starting at `startDeg` (screen-space angle, y-down, 0deg = +X).
static void filledQuarterDisc(video::IVideoDriver *driver,
        core::vector2d<s32> center, s32 r, video::SColor color,
        f32 startDeg, int segments = 10)
{
    if (r <= 0)
        return;

    // Reused across calls (see comment above) instead of allocating a new
    // std::vector every single corner/frame -- .clear() keeps the
    // already-reserved capacity.
    thread_local std::vector<video::S3DVertex> verts;
    thread_local std::vector<u16> indices;
    verts.clear();
    indices.clear();
    verts.reserve(segments + 2);

    verts.push_back(video::S3DVertex((f32)center.X, (f32)center.Y, 0.f,
            0.f, 0.f, -1.f, color, 0.f, 0.f));

    for (int i = 0; i <= segments; i++) {
        f32 deg = startDeg + 90.f * (f32)i / (f32)segments;
        f32 rad = deg * core::DEGTORAD;
        f32 vx = (f32)center.X + r * std::cos(rad);
        f32 vy = (f32)center.Y + r * std::sin(rad);
        verts.push_back(video::S3DVertex(vx, vy, 0.f, 0.f, 0.f, -1.f, color, 0.f, 0.f));
    }

    for (u16 i = 1; i + 1 < verts.size(); i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    driver->draw2DVertexPrimitiveList(verts.data(), (u32)verts.size(),
            indices.data(), (u32)indices.size() / 3,
            video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
}

// Quarter-ring (stroke of one rounded corner): the area between radius
// `rOuter` and `rOuter - thickness`, spanning the same 90 degree arc.
// Built as a triangle-strip-style fan (pairs of outer/inner vertices).
static void strokeQuarterRing(video::IVideoDriver *driver,
        core::vector2d<s32> center, s32 rOuter, s32 thickness,
        video::SColor color, f32 startDeg, int segments = 10)
{
    s32 rInner = rOuter - thickness;
    if (rOuter <= 0 || rInner < 0)
        return;

    thread_local std::vector<video::S3DVertex> verts;
    thread_local std::vector<u16> indices;
    verts.clear();
    indices.clear();
    verts.reserve((segments + 1) * 2);

    for (int i = 0; i <= segments; i++) {
        f32 deg = startDeg + 90.f * (f32)i / (f32)segments;
        f32 rad = deg * core::DEGTORAD;
        f32 c = std::cos(rad), s = std::sin(rad);
        verts.push_back(video::S3DVertex((f32)center.X + rOuter * c, (f32)center.Y + rOuter * s, 0.f,
                0.f, 0.f, -1.f, color, 0.f, 0.f));
        verts.push_back(video::S3DVertex((f32)center.X + rInner * c, (f32)center.Y + rInner * s, 0.f,
                0.f, 0.f, -1.f, color, 0.f, 0.f));
    }

    for (int i = 0; i < segments; i++) {
        u16 o0 = (u16)(i * 2), i0 = (u16)(i * 2 + 1);
        u16 o1 = (u16)(i * 2 + 2), i1 = (u16)(i * 2 + 3);
        indices.push_back(o0); indices.push_back(o1); indices.push_back(i0);
        indices.push_back(i0); indices.push_back(o1); indices.push_back(i1);
    }

    driver->draw2DVertexPrimitiveList(verts.data(), (u32)verts.size(),
            indices.data(), (u32)indices.size() / 3,
            video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
}

// ---------------------------------------------------------------------
// Filled rounded rectangle: a center cross of two plain draw2DRectangle
// calls (cheap, and Irrlicht already alpha-blends these correctly) plus
// 4 filled quarter-discs for the corners.
static void roundedRectFilled(video::IVideoDriver *driver,
        const core::rect<s32> &rectIn, s32 radius, video::SColor color)
{
    core::rect<s32> rect = rectIn;
    rect.repair();
    s32 w = rect.getWidth(), h = rect.getHeight();
    s32 r = std::max(0, std::min({radius, w / 2, h / 2}));

    if (r == 0) {
        driver->draw2DRectangle(color, rect);
        return;
    }

    s32 x0 = rect.UpperLeftCorner.X, y0 = rect.UpperLeftCorner.Y;
    s32 x1 = rect.LowerRightCorner.X, y1 = rect.LowerRightCorner.Y;

    // Vertical center strip: full width, minus the top/bottom corner bands.
    driver->draw2DRectangle(color, core::rect<s32>(x0, y0 + r, x1, y1 - r));
    // Top / bottom horizontal strips, minus the left/right corner bands.
    driver->draw2DRectangle(color, core::rect<s32>(x0 + r, y0, x1 - r, y0 + r));
    driver->draw2DRectangle(color, core::rect<s32>(x0 + r, y1 - r, x1 - r, y1));

    filledQuarterDisc(driver, core::vector2d<s32>(x0 + r, y0 + r), r, color, 180.f); // top-left
    filledQuarterDisc(driver, core::vector2d<s32>(x1 - r, y0 + r), r, color, 270.f); // top-right
    filledQuarterDisc(driver, core::vector2d<s32>(x1 - r, y1 - r), r, color, 0.f);   // bottom-right
    filledQuarterDisc(driver, core::vector2d<s32>(x0 + r, y1 - r), r, color, 90.f);  // bottom-left
}

// Rounded rectangle outline/stroke: 4 straight edge segments (as thin
// draw2DRectangle strips) plus 4 stroked corner arcs.
static void roundedRectOutline(video::IVideoDriver *driver,
        const core::rect<s32> &rectIn, s32 radius, video::SColor color,
        s32 thickness = BorderThickness)
{
    core::rect<s32> rect = rectIn;
    rect.repair();
    s32 w = rect.getWidth(), h = rect.getHeight();
    s32 r = std::max(0, std::min({radius, w / 2, h / 2}));
    thickness = std::max(1, std::min(thickness, r > 0 ? r : thickness));

    if (r == 0) {
        driver->draw2DRectangleOutline(rect, color, thickness);
        return;
    }

    s32 x0 = rect.UpperLeftCorner.X, y0 = rect.UpperLeftCorner.Y;
    s32 x1 = rect.LowerRightCorner.X, y1 = rect.LowerRightCorner.Y;

    // Top / bottom / left / right straight edges, between the corners.
    driver->draw2DRectangle(color, core::rect<s32>(x0 + r, y0, x1 - r, y0 + thickness));
    driver->draw2DRectangle(color, core::rect<s32>(x0 + r, y1 - thickness, x1 - r, y1));
    driver->draw2DRectangle(color, core::rect<s32>(x0, y0 + r, x0 + thickness, y1 - r));
    driver->draw2DRectangle(color, core::rect<s32>(x1 - thickness, y0 + r, x1, y1 - r));

    strokeQuarterRing(driver, core::vector2d<s32>(x0 + r, y0 + r), r, thickness, color, 180.f);
    strokeQuarterRing(driver, core::vector2d<s32>(x1 - r, y0 + r), r, thickness, color, 270.f);
    strokeQuarterRing(driver, core::vector2d<s32>(x1 - r, y1 - r), r, thickness, color, 0.f);
    strokeQuarterRing(driver, core::vector2d<s32>(x0 + r, y1 - r), r, thickness, color, 90.f);
}

// Soft drop shadow: several expanding rounded rects at falling alpha,
// offset slightly down-right, faking a gaussian blur cheaply without
// needing an offscreen blur pass.
static void dropShadow(video::IVideoDriver *driver, const core::rect<s32> &rect,
        s32 radius, s32 spread = 14, u8 baseAlpha = 70,
        core::vector2d<s32> offset = core::vector2d<s32>(0, 3))
{
    const int layers = 5;
    for (int i = layers; i >= 1; i--) {
        f32 t = (f32)i / (f32)layers;
        s32 grow = (s32)(spread * t);
        u8 alpha = (u8)(baseAlpha * (1.f - t) * 0.9f + baseAlpha * 0.08f);
        core::rect<s32> r(rect.UpperLeftCorner.X - grow + offset.X,
                rect.UpperLeftCorner.Y - grow + offset.Y,
                rect.LowerRightCorner.X + grow + offset.X,
                rect.LowerRightCorner.Y + grow + offset.Y);
        video::SColor c(alpha, 0, 0, 0);
        if (radius <= 0)
            driver->draw2DRectangle(c, r);
        else
            roundedRectFilled(driver, r, radius + grow, c);
    }
}

// ---------------------------------------------------------------------
// High-level convenience: the standard MineBoost panel -- soft shadow +
// translucent rounded fill + accent rounded outline. This is the direct
// drop-in replacement for the old
//     driver->draw2DRectangle(fill, rect);
//     driver->draw2DRectangleOutline(rect, border);
// pattern used throughout Menu.cpp / hud.cpp.
static void panel(video::IVideoDriver *driver, const core::rect<s32> &rect,
        s32 radius = Radius,
        video::SColor fill = PanelFill,
        video::SColor border = PanelBorder,
        bool shadow = true,
        s32 borderThickness = BorderThickness)
{
    if (shadow)
        dropShadow(driver, rect, radius);
    roundedRectFilled(driver, rect, radius, fill);
    if (border.getAlpha() > 0)
        roundedRectOutline(driver, rect, radius, border, borderThickness);
}

} // namespace ModernUI

#endif // MODERN_UI_H
