#include "precomp.h"
#include "util.h"
#include "offsets.h"
#include "globals.h"

int main()
{
	util::init();
	uintptr_t localPlayer = moduleBase + 0x18AC00;
	uintptr_t mHealth = util::Read<uintptr_t>(localPlayer, offsets::mHealth);
	uintptr_t mArmor = util::Read<uintptr_t>(localPlayer, offsets::mArmor);
	uintptr_t mRecoil = util::Read<uintptr_t>(localPlayer, offsets::mRecoil);
	uintptr_t mKnockback = util::Read<uintptr_t>(localPlayer, offsets::mKnockBack);
	uintptr_t mVisualKick = util::Read<uintptr_t>(localPlayer, offsets::mVisualKick);
	uintptr_t mRapid = util::Read<uintptr_t>(localPlayer, offsets::mRapidFire);
	uintptr_t mAmmo = util::Read<uintptr_t>(localPlayer, offsets::mAmmo);

	Sleep(1000);

	if (!bFound)
	{
		std::cout << "[+] Exiting the cheat.." << std::endl;
		return 0;
	}

	std::cout << "[+] Loading the cheat..";

	Sleep(1000);

	 /* std::cout << "[+] Press F1 to enable/disable Health!" << std::endl;
	std::cout << "[+] Press F2 to enable/disable Armor!" << std::endl;
	std::cout << "[+] Press F3 to enable/disable No-Recoil!" << std::endl;
	std::cout << "[+] Press F4 to enable/disable No-Knockback!" << std::endl;
	std::cout << "[+] Press F5 to enable/disable Infinite Ammo!" << std::endl;
	std::cout << "[+] Press F6 to enable/disable RapidFire!" << std::endl;
	std::cout << "[+] Press END to exit!" << std::endl; */

	while (!GetAsyncKeyState(VK_END))
	{
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			bHealth = !bHealth;
			if (bHealth)
			{
				util::Write<int>(mHealth, 1337);
			}
			else
			{
				util::Write<int>(mHealth, 100);
			}
		}

		if (GetAsyncKeyState(VK_F2) & 1)
		{
			bArmor = !bArmor;
			if (bArmor)
			{
				util::Write<int>(mArmor, 1337);
			}
			else
			{
				util::Write<int>(mArmor, 0);
			}
		}

		if (GetAsyncKeyState(VK_F3) & 1)
		{
			bRecoil = !bRecoil;
			if (bRecoil)
			{
				util::Write<int>(mRecoil, 0);
			}
			else
			{
				util::Write<int>(mRecoil, 25);
			}
		}

		if (GetAsyncKeyState(VK_F4) & 1)
		{
			bKnockback = !bKnockback;
			if (bKnockback)
			{
				util::Write<int>(mKnockback, 0);
			}
			else
			{
				util::Write<int>(mKnockback, 30);
			}
		}

		if (GetAsyncKeyState(VK_F5) & 1)
		{
			bTweaks = !bTweaks;
			if (bTweaks)
			{
				util::Write<int>(mAmmo, 9999);
				util::Write<int>(mRapid, 0);
				util::Write<int>(mVisualKick, 0);
			}
			else
			{
				util::Write<int>(mAmmo, 30);
				util::Write<int>(mRapid, 15);
				util::Write<int>(mVisualKick, 15);
			}
		}

		util::consoleUpdate();
		Sleep(100);
	}
}