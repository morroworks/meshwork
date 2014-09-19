#pragma once

#include "..\..\..\..\MwGlobals.h"

class SrRenderThread;

typedef void (*SrShaderOperation)(SrRenderThread *renderThread);

class MWDLLCLASS SrShaderOperations
{
public:
    static void Lighting(SrRenderThread *renderThread);
    static void BasicLighting(SrRenderThread *renderThread);
    static void CellLighting(SrRenderThread *renderThread);
    static void CellBasicLighting(SrRenderThread *renderThread);
    static void Fog(SrRenderThread *renderThread);
    static void NormalOut(SrRenderThread *renderThread);
    static void VectorNoise(SrRenderThread *renderThread);
    static void Noise(SrRenderThread *renderThread);
    static void Grayscale(SrRenderThread *renderThread);
    static void Tint(SrRenderThread *renderThread);
    static void ColorMap(SrRenderThread *renderThread);
    static void EnvMap(SrRenderThread *renderThread);
    static void CellEnvMap(SrRenderThread *renderThread);
    static void NormalMap(SrRenderThread *renderThread);
    static void FlatMap(SrRenderThread *renderThread);
    static void RefractionMap(SrRenderThread *renderThread);

	static void Color_Set(SrRenderThread *renderThread);
    static void Color_Add(SrRenderThread *renderThread);
    static void Color_AlphaAdd(SrRenderThread *renderThread);
    static void Color_Subtract(SrRenderThread *renderThread);
    static void Color_AlphaSubtract(SrRenderThread *renderThread);
    static void Color_Modulate(SrRenderThread *renderThread);
    static void Color_Translucency(SrRenderThread *renderThread);
};