class CfgPatches
{
	class Remain_Characters
	{
		requiredAddons[] =  {
			"DZ_Characters",
			"DZ_Characters_Tops",
			"DZ_Gear_Consumables",
			"DZ_Characters_Pants",
			"DZ_Gear_Food"
		};
	};
};

class CfgVehicles
{
	class Edible_Base;
	class Man;
	class InventoryEquipment;
	class SurvivorBase : Man
	{
		attachments[] += {"NeckExplosive"};
		class InventoryEquipment : InventoryEquipment
		{
			playerSlots[] += {"Slot_NeckExplosive"};
		};
	};
	class SurvivorMale_Base : SurvivorBase
    {
		model = "RemainServer\Characters\character_proxies.p3d";
		hiddenSelections[] = {""};
		hiddenSelectionsTextures[] = {""};
		hiddenSelectionsMaterials[] = {"dz\data\data\penetration\explosiontransparent.rvmat"};
    };
	class SurvivorFemale_Base : SurvivorBase
    {
        model = "RemainServer\Characters\character_proxies.p3d";
		hiddenSelections[] = {""};
		hiddenSelectionsTextures[] = {""};
		hiddenSelectionsMaterials[] = {"dz\data\data\penetration\explosiontransparent.rvmat"};
		
    };

	class Inventory_Base;

	class Remain_TimeCapsule_Base: Inventory_Base
	{
		scope = 1;
	};

	class Remain_TimeCapsule_5min: Remain_TimeCapsule_Base
	{
		scope=2;
		displayName = "5 Minute Additional Time";
		descriptionShort = "Consume for an additional 5 minutes of time on this precious rock";
		model = "DZ\gear\consumables\BatteryD.p3d";
	};

	class Remain_TimeCapsule_15min: Remain_TimeCapsule_Base
	{
		scope=2;
		displayName = "15 Minute Additional Time";
		descriptionShort = "Consume for an additional 15 minutes of time on this precious rock";
		model = "DZ\gear\consumables\BatteryD.p3d";
	};

	class Remain_TimeCapsule_60min: Remain_TimeCapsule_Base
	{
		scope=2;
		displayName = "60 Minute Additional Time";
		descriptionShort = "Consume for an additional 60 minutes of time on this precious rock. Score!";
		model = "DZ\gear\consumables\BatteryD.p3d";
	};
};

class CfgNonAIVehicles
{
	class Proxyneckexplosive
	{
        scope=2;
        simulation="ProxyInventory";
        inventorySlot="neckexplosive";
        autocenter=0;
        animated=0;
        model="\RemainServer\Characters\proxies\neckexplosive.p3d";
        shadow=1;
        reversed=1;
	};
};	