#include "pch.h"
#include "core.h"
#include "hero.h"
#include <variant>
#include "vector3f.h"

void Hero::setState(int state)
{
	uintptr_t addr = isBull() ? 0x254564 : 0x271590;
	Core::tryWriteMemory(addr, true, state);
}

void Hero::setState(BullState state)
{
	Core::tryWriteMemory(0x254564, true, state);
}

void Hero::setState(TyState state)
{
	Core::tryWriteMemory(0x271590, true, state);
}

int Hero::getState() {
	uintptr_t addr = isBull() ? 0x254564 : 0x271590;
	return Core::tryReadMemory<int>(addr, true);
}

void Hero::setPosition(Vector3f coords) {
	uintptr_t addr = isBull() ? 0x254268 : 0x270B78;
	Core::tryWriteMemory<Vector3f>(0x270B78, true, coords);
}

Vector3f Hero::getPosition() {
	uintptr_t addr = isBull() ? 0x254268 : 0x270B78;
	return Core::tryReadMemory<Vector3f>(addr, true);
}

int Hero::getHealth(){
	uintptr_t addr = isBull() ? 0x273814 : 0x2737CC;
	return Core::tryReadMemory<int>(addr, true);
}

void Hero::setHealth(int health){
	uintptr_t addr = isBull() ? 0x273814 : 0x2737CC;
	Core::tryWriteMemory(addr, true, health);
}

int Hero::getBreath(){
	if (isBull)
		return 0;
	return Core::tryReadMemory<int>(0x2737F0, true);
}

void Hero::setBreath(int breath){
	if (isBull)
		return;
	Core::tryWriteMemory(0x2737F0, true, breath);
}

float Hero::getSwimSpeed(){
	return Core::tryReadMemory<float>(0x1F982C, true);
}

void Hero::setSwimSpeed(float speed = 20.0f){
	Core::tryWriteMemory(0x1F982C, true, speed);
}

float Hero::getRunSpeed(){
	return Core::tryReadMemory<float>(0x288914, true);
}

void Hero::setRunSpeed(float speed = 10.0f){
	Core::tryWriteMemory(0x288914, true, speed);
}

float Hero::getGravity(){
	return Core::tryReadMemory<float>(0x288940, true);
}

void Hero::setGravity(float gravity = 0.75f){
	Core::tryWriteMemory(0x288940, true, gravity);
}

float Hero::getAirSpeed(){
	return Core::tryReadMemory<float>(0x288920, true);
}

void Hero::setAirSpeed(float speed = 10.0f){
	Core::tryWriteMemory(0x288920, true, speed);
}

float Hero::getDoubleJumpHeight(){
	return Core::tryReadMemory<float>(0x28894C, true);
}

void Hero::setDoubleJumpHeight(float height = 8.37f){
	Core::tryWriteMemory(0x28894C, true, height);
}

float Hero::getJumpHeight() {
	return Core::tryReadMemory<float>(0x28893C, true);
}

void Hero::setJumpHeight(float height = 18.57f) {
	Core::tryWriteMemory(0x28893C, true, height);
}

float Hero::getLedgeGrabTolerance(){
	return Core::tryReadMemory<float>(0x288968, true);
}

void Hero::setLedgeGrabTolerance(float tolerance = 20.0f){
	Core::tryWriteMemory(0x288968, true, tolerance);
}

float Hero::getGlideSpeed(){
	return Core::tryReadMemory<float>(0x288928, true);
}

void Hero::setGlideSpeed(float speed = 7.0f){
	Core::tryWriteMemory(0x288928, true, speed);
}

bool Hero::getInvincibility(){
	return Core::tryReadMemory<bool>(0x288A55, true);
}

void Hero::setInvincibility(bool status){
	Core::tryWriteMemory(0x288A55, true, status);
}

void Hero::kill(){
	if (isBull())
		setState(BullState::Dying);
	else
		setState(TyState::Dying);
}

void Hero::setMainSkin(int index){
	auto address = Core::getPointerAddress(0x289298, std::vector<int>{ 0x5E8 });
	uintptr_t targetAddress = address - 68 - (76 * index);
	Core::tryWriteMemory<uintptr_t>(address, false, targetAddress);
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
	return Core::tryReadMemory<bool>(0x27E544, true);
}