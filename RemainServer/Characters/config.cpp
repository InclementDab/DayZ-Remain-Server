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