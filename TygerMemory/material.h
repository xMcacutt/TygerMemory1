#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#include "colour.h"
#include "vector4f.h"

//May be wrong for the PC version (also not the correct size)
struct TYGERMEM Material
{
    char Name[0x20];
    int CollisionFlags;
    int TextureFilterSize;
    int Type;
    int BlendMode;
    int Flags;
    int Grass;
    RGBA Colour;
    Vector4f field_48;
    int ReferenceCount;
    Material* pOverlayMat;
    void* Texture1;
    void* Texture2;

    static Material* Create(const char* textureName);
    void Destroy();
};
