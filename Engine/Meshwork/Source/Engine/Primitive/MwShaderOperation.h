#pragma once

#include "..\..\MwGlobals.h"

enum MwShaderOperation
{
    MwShaderOperation_None = 0,
    MwShaderOperation_BasicShading = 1,
    MwShaderOperation_Material = 2,
    MwShaderOperation_LightSource = 3,
    MwShaderOperation_VertexLighting = 4,
    MwShaderOperation_PixelLighting = 5,
    MwShaderOperation_ColorMap = 6,
    MwShaderOperation_EnvMap = 7,
    MwShaderOperation_NormalMap = 8,
    MwShaderOperation_RefractionMap = 9,
    MwShaderOperation_AlignScreenQuad = 10,
    MwShaderOperation_BlurMap = 11,
    MwShaderOperation_Tint = 12,
    MwShaderOperation_HBlur = 13,
    MwShaderOperation_VBlur = 14,
    MwShaderOperation_ProjectTexture = 15,
    MwShaderOperation_ProjectPicture = 16,
    MwShaderOperation_ShadowMapWriter = 17,
    MwShaderOperation_ShadowMap = 18,
    MwShaderOperation_BlendTexture = 19,
    MwShaderOperation_TextureTransform = 20,
    MwShaderOperation_Skinning = 21,
};
