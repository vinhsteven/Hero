
#ifndef _GD_COLOR_HELPER_H_
#define _GD_COLOR_HELPER_H_

#define makeColor3B(red, green, blue)           (ccColor3B){ red, green, blue }
#define makeColor4B(red, green, blue, alpha)    (ccColor4B){ red, green, blue, alpha }
#define makeColor4F(red, green, blue, alpha)    (ccColor4F){ red, green, blue, alpha }

#define getColor3BFromColor4F(sColor)           makeColor3B((GLubyte)(sColor.r * 255), (GLubyte)(sColor.g * 255), (GLubyte)(sColor.b * 255))
#define getColor3BFromReverseColor4F(sColor)    makeColor3B((GLubyte)((1.0f - sColor.r) * 255), (GLubyte)((1.0f - sColor.g) * 255), (GLubyte)((1.0f - sColor.b) * 255))
#define getReverseColor3B(sColor)               makeColor3B(255 - sColor.r, 255 - sColor.g, 255 - sColor.b)
#define getReverseColor4F(sColor)               makeColor4F(1.0f - sColor.r, 1.0f - sColor.g, 1.0f - sColor.b, sColor.a)

USING_NS_CC;

static const ccColor3B BLACK_3B   = {   0,   0,   0 };
static const ccColor3B BLUE_3B    = {   0,   0, 255 };
static const ccColor3B GREEN_3B   = {   0, 255,   0 };
static const ccColor3B CYAN_3B    = {   0, 255, 255 };
static const ccColor3B RED_3B     = { 255,   0,   0 };
static const ccColor3B MAGENTA_3B = { 255,   0, 255 };
static const ccColor3B YELLOW_3B  = { 255, 255,   0 };
static const ccColor3B WHITE_3B   = { 255, 255, 255 };
static const ccColor3B ORANGE_3B  = { 255, 128,   0 };
static const ccColor3B GRAY_3B    = { 128, 128, 128 };

static const ccColor4B BLACK_4B   = {   0,   0,   0, 255 };
static const ccColor4B BLUE_4B    = {   0,   0, 255, 255 };
static const ccColor4B GREEN_4B   = {   0, 255,   0, 255 };
static const ccColor4B CYAN_4B    = {   0, 255, 255, 255 };
static const ccColor4B RED_4B     = { 255,   0,   0, 255 };
static const ccColor4B MAGENTA_4B = { 255,   0, 255, 255 };
static const ccColor4B YELLOW_4B  = { 255, 255,   0, 255 };
static const ccColor4B WHITE_4B   = { 255, 255, 255, 255 };
static const ccColor4B ORANGE_4B  = { 255, 128,   0, 255 };
static const ccColor4B GRAY_4B    = { 128, 128, 128, 255 };

static const ccColor4F BLACK_4F   = { 0.0f, 0.0f, 0.0f, 1.0f };
static const ccColor4F BLUE_4F    = { 0.0f, 0.0f, 1.0f, 1.0f };
static const ccColor4F GREEN_4F   = { 0.0f, 1.0f, 0.0f, 1.0f };
static const ccColor4F CYAN_4F    = { 0.0f, 1.0f, 1.0f, 1.0f };
static const ccColor4F RED_4F     = { 1.0f, 0.0f, 0.0f, 1.0f };
static const ccColor4F MAGENTA_4F = { 1.0f, 0.0f, 1.0f, 1.0f };
static const ccColor4F YELLOW_4F  = { 1.0f, 1.0f, 0.0f, 1.0f };
static const ccColor4F WHITE_4F   = { 1.0f, 1.0f, 1.0f, 1.0f };
static const ccColor4F ORANGE_4F  = { 1.0f, 0.5f, 0.0f, 1.0f };
static const ccColor4F GRAY_4F    = { 0.5f, 0.5f, 0.5f, 1.0f };

#endif // _GD_COLOR_HELPER_H_
