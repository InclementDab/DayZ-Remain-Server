class CfgPatches
{
	class Remain_Characters_Necklace
	{
		requiredAddons[] =
		{
			"DZ_Data",
			"Remain_Characters"
		};
	};
};

class CfgVehicles
{
	class Clothing;
	class NeckExplosive: Clothing
	{
		scope = 2;
		displayName = "NiCOE Termination Device";
		descriptionShort = "A welded shut, human termination device (unisex). This lightweight neckwear single-handledly saved humanity after Sanctions 204b took place. Paid for by the NiCOE Humanity Research Division. Available in multiple colors.";
		model = "RemainServer\Characters\Neckwear\necklace_g.p3d";
		ammoType = "CollarExplosion";
		inventorySlot[] = {"neckexplosive"};
		simulation = "clothing";
		vehicleClass = "Clothing";
		itemInfo[] = {"Clothing"};
		rotationFlags = 16;
		visibilityModifier = 0.1;
		hideSelectionsByinventorySlot = 1;
		weight = 100;
		itemSize[] = {2,1};
		absorbency = 0.1;
		heatIsolation = 0.1;
		class ClothingTypes
		{
			male = "RemainServer\Characters\Neckwear\necklace_m.p3d";
			female = "RemainServer\Characters\Neckwear\necklace_f.p3d";
		};

		 class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints=5000;
                    transferToAttachmentsCoef=0;
                    healthLevels[]={{1, {"DZ\Characters\backpacks\data\taloon.rvmat"}}, {0.7, {"DZ\Characters\backpacks\data\taloon.rvmat"}}, {0.5, {"DZ\Characters\backpacks\data\taloon_damage.rvmat"}}, {0.3, {"DZ\Characters\backpacks\data\taloon_damage.rvmat"}}, {0, {"DZ\Characters\backpacks\data\taloon_destruct.rvmat"}}};
                };
            };
        };
	};

	class NeckToxicityReader : Clothing
	{
		scope = 2;
		displayName = "NiCOE Bio-Toxicity Reader";
		descriptionShort = "Wirelessly transmits blood infectivity levels to your personal NiCOE Termination Device. Please do not remove.";
		model = "RemainServer\Characters\Neckwear\BloodToxicity_g.p3d";
		simulation = "clothing";
		vehicleClass = "Clothing";
		itemInfo[]=
		{
			"Clothing",
			"Armband"
		};
		visibilityModifier = 0.1;
		inventorySlot[] = {"NeckToxicityReader"};
		rotationFlags = 16;
		weight = 120;
		itemSize[] = {1, 2};
		heatIsolation = 0.4;
        absorbency=0.3;
		hideSelectionsByinventorySlot = 1;
		hiddenSelections[]=
		{
            "Screen",
            "Detector",
			"personality"
		};
		hiddenSelectionsTextures[]=
		{
			"RemainServer\Characters\Neckwear\Data\Screen_co.paa",
			"RemainServer\Characters\Neckwear\Data\Detector_co.paa"
		};
        hiddenSelectionsMaterials[]=
		{
			"RemainServer\Characters\Neckwear\Data\Screen.rvmat",
            "RemainServer\Characters\Neckwear\Data\Detector.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 25;
				};
			};
		};
		class ClothingTypes
		{
			male = "\RemainServer\Characters\Neckwear\BloodToxicity_m.p3d";
			female = "\RemainServer\Characters\Neckwear\BloodToxicity_f.p3d";
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet = "Shirt_pickup_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "Shirt_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
};

class CfgAmmo
{
	class DefaultAmmo;
	class CollarExplosion : DefaultAmmo
	{
		indirectHit = 1;
		indirectHitRange = 0.5;
		explosive = 1;
		typicalSpeed = 3;
		initSpeed = 3;
		simulation = "shotShell";
		simulationStep = 0.05;
		soundSetExplosion[] = {"Grenade_explosion_SoundSet", "Grenade_Tail_SoundSet"};
		class DamageApplied
		{
			type = "FragGrenade";
			class Health
			{
				damage = 75;
			};
			class Blood
			{
				damage = 0;
			};
			class Shock
			{
				damage = 0;
			};
		};
		class NoiseExplosion
		{
			strength = 200;
			type = "shot";
		};
	};
};