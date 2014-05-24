#include "PapyrusScroll.h"
#include "PapyrusSpell.h"
#include "GameObjects.h"

namespace papyrusScroll
{
	float GetCastTime(ScrollItem* thisSpell)
	{
		return (thisSpell)? thisSpell->data.castTime : 0.0;
	}

	BGSPerk* GetPerk(ScrollItem* thisSpell)
	{
		return (thisSpell) ? thisSpell->data.spellPerk : NULL;
	}

	UInt32 GetNumEffects(ScrollItem* thisMagic)
	{ return magicItemUtils::GetNumEffects(thisMagic); }

	float GetNthEffectMagnitude(ScrollItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectMagnitude(thisMagic, index); }

	UInt32 GetNthEffectArea(ScrollItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectArea(thisMagic, index); }

	UInt32 GetNthEffectDuration(ScrollItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectDuration(thisMagic, index); }

	EffectSetting* GetNthEffectMagicEffect(ScrollItem* thisMagic, UInt32 index)
	{ return magicItemUtils::GetNthEffectMagicEffect(thisMagic, index); }

	UInt32 GetCostliestEffectIndex(ScrollItem* thisMagic)
	{ return magicItemUtils::GetCostliestEffectIndex(thisMagic); }

	void SetNthEffectMagnitude(ScrollItem* thisMagic, UInt32 index, float value)
	{ magicItemUtils::SetNthEffectMagnitude(thisMagic, index, value); }

	void SetNthEffectArea(ScrollItem* thisMagic, UInt32 index, UInt32 value)
	{ magicItemUtils::SetNthEffectArea(thisMagic, index, value); }

	void SetNthEffectDuration(ScrollItem* thisMagic, UInt32 index, UInt32 value)
	{ magicItemUtils::SetNthEffectDuration(thisMagic, index, value); }

	BGSEquipSlot * GetEquipType(ScrollItem* thisMagic)
	{
		if (thisMagic) {
			return thisMagic->equipType.GetEquipSlot();
		}

		// Invalid EquipSlot
		return NULL;
	}

	void SetEquipType(ScrollItem* thisMagic, BGSEquipSlot * slot)
	{
		if (thisMagic && slot) {
			thisMagic->equipType.SetEquipSlot(slot);
		}
	}
}

#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

void papyrusScroll::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0<ScrollItem, float>("GetCastTime", "Scroll", papyrusScroll::GetCastTime, registry));

	registry->RegisterFunction(
		new NativeFunction0<ScrollItem, UInt32>("GetNumEffects", "Scroll", papyrusScroll::GetNumEffects, registry));

	registry->RegisterFunction(
		new NativeFunction1<ScrollItem, float, UInt32>("GetNthEffectMagnitude", "Scroll", papyrusScroll::GetNthEffectMagnitude, registry));

	registry->RegisterFunction(
		new NativeFunction1<ScrollItem, UInt32, UInt32>("GetNthEffectArea", "Scroll", papyrusScroll::GetNthEffectArea, registry));

	registry->RegisterFunction(
		new NativeFunction1<ScrollItem, UInt32, UInt32>("GetNthEffectDuration", "Scroll", papyrusScroll::GetNthEffectDuration, registry));

	registry->RegisterFunction(
		new NativeFunction1<ScrollItem, EffectSetting*, UInt32>("GetNthEffectMagicEffect", "Scroll", papyrusScroll::GetNthEffectMagicEffect, registry));

	registry->RegisterFunction(
		new NativeFunction0<ScrollItem, UInt32>("GetCostliestEffectIndex", "Scroll", papyrusScroll::GetCostliestEffectIndex, registry));

	// Sets
	registry->RegisterFunction(
		new NativeFunction2<ScrollItem, void, UInt32, float>("SetNthEffectMagnitude", "Scroll", papyrusScroll::SetNthEffectMagnitude, registry));

	registry->RegisterFunction(
		new NativeFunction2<ScrollItem, void, UInt32, UInt32>("SetNthEffectArea", "Scroll", papyrusScroll::SetNthEffectArea, registry));

	registry->RegisterFunction(
		new NativeFunction2<ScrollItem, void, UInt32, UInt32>("SetNthEffectDuration", "Scroll", papyrusScroll::SetNthEffectDuration, registry));

	// EquipType
	registry->RegisterFunction(
		new NativeFunction0 <ScrollItem, BGSEquipSlot*>("GetEquipType", "Scroll", papyrusScroll::GetEquipType, registry));

	registry->RegisterFunction(
		new NativeFunction1 <ScrollItem, void, BGSEquipSlot*>("SetEquipType", "Scroll", papyrusScroll::SetEquipType, registry));
}