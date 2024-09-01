#pragma once
#include "precomp.h"

namespace offsets
{
	std::vector<unsigned int> mHealth = { 0xEC };
	std::vector<unsigned int> mArmor = { 0xF0 };
	std::vector<unsigned int> mRapidFire = { 0x364, 0xC, 0x48 };
	std::vector<unsigned int> mAmmo = { 0x364, 0x14, 0x0 };
	std::vector<unsigned int> mVisualKick = { 0x364, 0xC, 0x5A };
	std::vector<unsigned int> mKnockBack = { 0x364, 0xC, 0x54 };
	std::vector<unsigned int> mRecoil = { 0x364, 0xC, 0x5E };
}