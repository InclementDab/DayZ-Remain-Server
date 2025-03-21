class CfgPatches
{
	class MT_Scripts
	{
		requiredAddons[] = { "DZ_Scripts" };
	};
};

class CfgAddons
{
    class PreloadAddons
    {
        class RemainServer
        {
            list[]={};
        };
    };
};

class CfgMods
{
    class RemainServer
    {
        name="";
        dir="RemainServer";
        picture="";
        action="";
        author="";
        overview = "";
		inputs = "";
		type = "mod";
        defines[] = {};

        class defs
		{
			class imageSets
			{
				files[]= {};
			};
			class widgetStyles
			{
				files[]= {};
			};

			class engineScriptModule 
			{ 
				files[] = { "RemainServer/Scripts/1_Core"};
			};

			class gameScriptModule
			{
				files[] = { "RemainServer/Scripts/3_Game" };
			};
			class worldScriptModule
			{
				files[] = { "RemainServer/Scripts/4_World" };
			};

			class missionScriptModule 
			{
				files[] = { "RemainServer/Scripts/5_Mission" };
			};
		};
    };
};

class CfgSlots
{
	class Slot_NeckExplosive
	{
		name = "NeckExplosive";
		displayName = "Termination Device";
		ghostIcon = "set:dayz_inventory image:missing";
	};
};