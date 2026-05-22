#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include "matrix.h"
#include "vector4f.h"

struct AnimationTemplate
{
    char Name[0x20];
    int ReferenceCount;
    void* pAnimData;
};
struct TYGERMEM Animation
{
    void Tween(float currentFrame, float tweenBlend);
    int GetNodeIndex(const char* nodeName);
    Matrix* GetNodeMatrix(int nodeIndex);
    AnimationTemplate* Template;
    Matrix* Matrices;
};

struct AnimEvent
{
    char* field_0;
    SHORT StartEventFrame;
    SHORT EndEventFrame;
};
struct AnimRange
{
    SHORT StartFrame;
    SHORT EndFrame;
    SHORT Speed;
    SHORT EventCount;
    AnimEvent* pEvents;
    int field_c;
};

struct MKAnim
{
    char* pAnimName;
    SHORT RangeCount;
    SHORT FrameCount;
    UINT16 field_8;
    UINT8 CycleType;
    UINT8 field_b;
    AnimRange* pAnimRanges;
};
struct MKAnimTemplateSection
{
    char* pMeshName;
    char* pAnimName;
    UINT16 AnimCount;
    UINT16 field_a;
    UINT16 field_c;
    MKAnim* Anims;
};
struct MKAnimScriptTemplate
{
    char BadName[0x20];
    int ReferenceCount;
    int TemplateSize;
    int field_28;
    int field_2c;
    MKAnimTemplateSection* pSelection;
};
struct TYGERMEM MKAnimScript
{
    void Init(const char* badName);
    void Deinit();
    MKAnim* GetAnim(const char* animName);
    char* GetAnimName();
    char* GetMeshName();
    void Animate();
    void TweenAnim(MKAnim* targetAnim, int tweenDuration);
    void Apply(Animation* anim);
    void SetAnim(MKAnim* anim);
    MKAnimScriptTemplate* pTemplate;
    MKAnim* CurrAnim;
    MKAnim* NextAnim;
    float field_c;
    float field_10;
    float field_14;
    SHORT field_18;
    SHORT field_1a;
    SHORT TweenBlend; //Not 100% certain
    UINT16 field_1e;
};
