#include "pch.h"
#include "core.h"
#include "hero.h"
#include "vector3f.h"

void Hero::setState(int state)
{
	uintptr_t addr = isBull() ? 0x254564 : 0x271590;
	*(uintptr_t*)(Core::moduleBase + addr) = state;
}

void Hero::setState(BullState state)
{
	*(int*)(Core::moduleBase + 0x254564) = (int)state;
}

void Hero::setState(TyState state)
{
	*(int*)(Core::moduleBase + 0x271590) = (int)state;
}

int Hero::getState() {
	uintptr_t addr = isBull() ? 0x254564 : 0x271590;
	return *(uintptr_t*)(Core::moduleBase + addr);
}

void Hero::setPosition(Vector3f coords) {
	uintptr_t addr = isBull() ? 0x254268 : 0x270B78;
	*(Vector3f*)(Core::moduleBase + addr) = coords;
}

Vector3f Hero::getPosition() {
	uintptr_t addr = isBull() ? 0x254268 : 0x270B78;
	return *(Vector3f*)(Core::moduleBase + addr);
}

int Hero::getHealth(){
	uintptr_t addr = isBull() ? 0x273814 : 0x2737CC;
	return *(int*)(Core::moduleBase + addr);
}

void Hero::setHealth(int health){
	uintptr_t addr = isBull() ? 0x273814 : 0x2737CC;
	*(int*)(Core::moduleBase + addr) = health;
}

int Hero::getBreath(){
	if (isBull())
		return 0;
	return *(int*)(Core::moduleBase + 0x2737F0);
}

void Hero::setBreath(int breath){
	if (isBull())
		return;
	*(int*)(Core::moduleBase + 0x2737F0) = breath;
}

float Hero::getSwimSpeed(){
	return *(float*)(Core::moduleBase + 0x1F982C);
}

void Hero::setSwimSpeed(float speed = 20.0f){
	*(float*)(Core::moduleBase + 0x1F982C) = speed;
}

float Hero::getRunSpeed(){
	return *(float*)(Core::moduleBase + 0x288914);
}

void Hero::setRunSpeed(float speed = 10.0f){
	*(float*)(Core::moduleBase + 0x288914) = speed;
}

float Hero::getGravity(){
	return *(float*)(Core::moduleBase + 0x288940);
}

void Hero::setGravity(float gravity = 0.75f) {
	*(float*)(Core::moduleBase + 0x288940) = gravity;
}

float Hero::getAirSpeed(){
	return *(float*)(Core::moduleBase + 0x288920);
}

void Hero::setAirSpeed(float speed = 10.0f){
	*(float*)(Core::moduleBase + 0x288920) = speed;
}

float Hero::getDoubleJumpHeight(){
	return *(float*)(Core::moduleBase + 0x28894C);
}

void Hero::setDoubleJumpHeight(float height = 8.37f){
	*(float*)(Core::moduleBase + 0x28894C) = height;
}

float Hero::getJumpHeight() {
	return *(float*)(Core::moduleBase + 0x28893C);
}

void Hero::setJumpHeight(float height = 18.57f) {
	*(float*)(Core::moduleBase + 0x28894C) = height;
}

float Hero::getLedgeGrabTolerance(){
	return *(float*)(Core::moduleBase + 0x288968);
}

void Hero::setLedgeGrabTolerance(float tolerance = 20.0f){
	*(float*)(Core::moduleBase + 0x288968) = tolerance;
}

float Hero::getGlideSpeed(){
	return *(float*)(Core::moduleBase + 0x288928);
}

void Hero::setGlideSpeed(float speed = 7.0f){
	*(float*)(Core::moduleBase + 0x288928) = speed;
}

bool Hero::getInvincibility(){
	return *(bool*)(Core::moduleBase + 0x288A55);
}

void Hero::setInvincibility(bool status){
	*(bool*)(Core::moduleBase + 0x288A55) = status;
}

void Hero::kill(){
	if (isBull())
		setState(BullState::Dying);
	else
		setState(TyState::Dying);
}

void Hero::setMainSkin(int index){
	auto address = Core::getPointerAddress(0x289298, std::vector<int>{ 0x5E8 });
	*(uintptr_t*)(address - 68 - (76 * index)) = index;
}

void Hero::resetValues(){
	setSwimSpeed();
	setRunSpeed();
	setGravity();
	setGlideSpeed();
	setAirSpeed();
	setJumpHeight();
	setLedgeGrabTolerance();
	setDoubleJumpHeight();
}

bool Hero::isBull()
{
	return *(bool*)(Core::moduleBase + 0x27E544);
}