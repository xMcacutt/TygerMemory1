#include "pch.h"
#include "animation.h"
#include "core.h"

using TyAnimationTween_t = void(__thiscall*)(Animation* pAnim, float currentFrame, float tweenBlend);
using TyAnimationGetNodeIndex_t = int(__thiscall*)(Animation* pAnim, const char* nodeName);
using TyAnimationGetNodeMatrix_t = Matrix * (__thiscall*)(Animation* pAnim, int nodeIndex);

TyAnimationTween_t TyAnimationTween = nullptr;
TyAnimationGetNodeIndex_t TyAnimationGetNodeIndex = nullptr;
TyAnimationGetNodeMatrix_t TyAnimationGetNodeMatrix = nullptr;

using TyAnimScriptInit_t = void(__thiscall*)(MKAnimScript* pScript, const char* badName);
using TyGetAnim_t = MKAnim * (__thiscall*)(MKAnimScript* pScript, const char* badName);
using TyApply_t = void(__thiscall*)(MKAnimScript* pScript, Animation* anim);
using TySetAnim_t = void(__thiscall*)(MKAnimScript* pScript, MKAnim* anim);
using TyTweenAnim_t = void(__thiscall*)(MKAnimScript* pScript, MKAnim* targetAnim, int tweenDuration);
using TyAnimScriptCharThisCall_t = char* (__thiscall*)(MKAnimScript* pScript);
using TyAnimScriptVoidThisCall_t = void(__thiscall*)(MKAnimScript* pScript);

TyAnimScriptInit_t TyAnimScriptInit = nullptr;
TyGetAnim_t TyGetAnim = nullptr;
TyApply_t TyApply = nullptr;
TySetAnim_t TySetAnim = nullptr;
TyTweenAnim_t TyTweenAnim = nullptr;
TyAnimScriptCharThisCall_t TyGetAnimName = nullptr;
TyAnimScriptCharThisCall_t TyGetMeshName = nullptr;
TyAnimScriptCharThisCall_t TyAnimate = nullptr;
TyAnimScriptVoidThisCall_t TyScriptDeinit = nullptr;

void Animation::Tween(float currentFrame, float tweenBlend)
{
	if (!TyAnimationTween)
		TyAnimationTween = (TyAnimationTween_t)(Core::moduleBase + 0x19d260);
	TyAnimationTween(this, currentFrame, tweenBlend);
}

int Animation::GetNodeIndex(const char* nodeName)
{
	if (!TyAnimationGetNodeIndex)
		TyAnimationGetNodeIndex = (TyAnimationGetNodeIndex_t)(Core::moduleBase + 0x19d080);
	return TyAnimationGetNodeIndex(this, nodeName);
}

Matrix* Animation::GetNodeMatrix(int nodeIndex)
{
	if (!TyAnimationGetNodeMatrix)
		TyAnimationGetNodeMatrix = (TyAnimationGetNodeMatrix_t)(Core::moduleBase + 0x19d0d0);
	return TyAnimationGetNodeMatrix(this, nodeIndex);
}

void MKAnimScript::Init(const char* badName)
{
	if (!TyAnimScriptInit)
		TyAnimScriptInit = (TyAnimScriptInit_t)(Core::moduleBase + 0x1a5a70);
	TyAnimScriptInit(this, badName);
}

void MKAnimScript::Deinit()
{
	if (!TyScriptDeinit)
		TyScriptDeinit = (TyAnimScriptVoidThisCall_t)(Core::moduleBase + 0x1a5580);
	TyScriptDeinit(this);
}

MKAnim* MKAnimScript::GetAnim(const char* animName)
{
	if (!TyGetAnim)
		TyGetAnim = (TyGetAnim_t)(Core::moduleBase + 0x1a5660);
	return TyGetAnim(this, animName);
}

char* MKAnimScript::GetAnimName()
{
	if (!TyGetAnimName)
		TyGetAnimName = (TyAnimScriptCharThisCall_t)(Core::moduleBase + 0x1a56f0);
	return TyGetAnimName(this);
}

char* MKAnimScript::GetMeshName()
{
	if (!TyGetMeshName)
		TyGetMeshName = (TyAnimScriptCharThisCall_t)(Core::moduleBase + 0x1a5920);
	return TyGetMeshName(this);
}

void MKAnimScript::Animate()
{
	if (!TyAnimate)
		TyAnimate = (TyAnimScriptCharThisCall_t)(Core::moduleBase + 0x1a52e0);
	TyAnimate(this);
}

void MKAnimScript::TweenAnim(MKAnim* targetAnim, int tweenDuration)
{
	if (!TyTweenAnim)
		TyTweenAnim = (TyTweenAnim_t)(Core::moduleBase + 0x1a65a0);
	TyTweenAnim(this, targetAnim, tweenDuration);
}

void MKAnimScript::Apply(Animation* anim)
{
	if (!TyApply)
		TyApply = (TyApply_t)(Core::moduleBase + 0x1a5490);
	TyApply(this, anim);
}

void MKAnimScript::SetAnim(MKAnim* anim)
{
	if (!TySetAnim)
		TySetAnim = (TySetAnim_t)(Core::moduleBase + 0x1a62f0);
	TySetAnim(this, anim);
}
