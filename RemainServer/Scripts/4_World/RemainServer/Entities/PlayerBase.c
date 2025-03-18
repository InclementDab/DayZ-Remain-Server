class Remain_TimeCapsule_Base: ItemBase
{
	float GetAdditionalTime()
	{
		return 0;
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionConsumeAdditionalTime);
	}
}

class Remain_TimeCapsule_5min: Remain_TimeCapsule_Base
{
	override float GetAdditionalTime()
	{
		return 5 * 60;
	}
}

class Remain_TimeCapsule_15min: Remain_TimeCapsule_Base
{
	override float GetAdditionalTime()
	{
		return 15 * 60;
	}
}

class Remain_TimeCapsule_60min: Remain_TimeCapsule_Base
{
	override float GetAdditionalTime()
	{
		return 60 * 60;
	}
}

[RegisterAction(ActionConsumeAdditionalTime)]
class ActionConsumeAdditionalTime: ActionContinuousBase
{
	void ActionConsumeAdditionalTime()
	{		
		m_Text = "Add More Time";
		m_CallbackClass = ActionConsumeCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONMOD_EAT;
		m_CommandUIDProne 	= DayZPlayerConstants.CMD_ACTIONFB_EAT;
	}
	
	override void CreateConditionComponents()  
	{		
		m_ConditionItem 	= new CCIDummy();
		m_ConditionTarget 	= new CCTSelf();
	}
	
	override bool HasTarget()
	{
		return false;
	}
	
	override void OnStartServer(ActionData action_data)
	{
		super.OnStartServer(action_data);
		
		Remain_TimeCapsule_Base time_capsule = Remain_TimeCapsule_Base.Cast(action_data.m_MainItem);
		if (!time_capsule) {
			return;
		}

		float time_extra = time_capsule.GetAdditionalTime();
		action_data.m_Player.AddTimeToLive(time_extra);
		time_capsule.DeleteSave();
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return Remain_TimeCapsule_Base.Cast(item) != null;
	}
}

class RemainMainView: ScriptView
{
	protected PlayerBase m_Player;
	
	TextWidget TimeRemaining;
	
	void RemainMainView(PlayerBase player)
	{
		m_Player = player;
	}
	
	override void Update(float dt)
	{
		super.Update(dt);

		TimeSpan time_remaining = m_Player.GetTimeToLive();
		string time_remaining_string = time_remaining.Format();
		TimeRemaining.SetText(time_remaining_string);
	}
	
	override string GetLayoutFile()
	{
		return "RemainServer\\GUI\\layouts\\main_layout.layout";
	}
}

modded class PlayerBase
{
    // DateTime
    protected float m_TimeOfKill = -5;
	protected ref RemainMainView m_RemainMainView;

    void PlayerBase()
    {
        RegisterNetSyncVariableFloat("m_TimeOfKill");
    }
	
	override void OnSelectPlayer()
	{
		super.OnSelectPlayer();
		
#ifndef SERVER
		delete m_RemainMainView;
		
		m_RemainMainView = new RemainMainView(this);
#else
		
		GetGame().GetUpdateQueue(CALL_CATEGORY_GAMEPLAY).Insert(UpdateTimeToLive);
#endif
	}

    protected void UpdateTimeToLive(float dt)
    {
		m_TimeOfKill -= dt;
		
		NeckExplosive explosive = NeckExplosive.Cast(GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("Slot_NeckExplosive")));
        if (m_TimeOfKill < 0 && m_TimeOfKill != -5) {    
			if (explosive) {
				explosive.SetDetonationTimer(3);
			} else {
				SetHealth("GlobalHealth", "Health", 0);
			}
			
			GetGame().GetUpdateQueue(CALL_CATEGORY_GAMEPLAY).Remove(UpdateTimeToLive);
        } else {
			if (explosive) {
				explosive.ClearDetonationTimer();	
			}
		}
		
		SetSynchDirty();
    }

    void SetTimeToLive(float time)
    {
        if (!GetGame().IsServer()) {
            return;
        }

        m_TimeOfKill = time;
		
		m_TimeOfKill = Math.Clamp(m_TimeOfKill, 0, 3600 * 5);
        SetSynchDirty();
    }

    void AddTimeToLive(float time)
    {
        if (!GetGame().IsServer()) {
            return;
        }

        m_TimeOfKill += time;
		
		m_TimeOfKill = Math.Clamp(m_TimeOfKill, 0, 3600 * 5);
        SetSynchDirty();
    }

    float GetTimeToLive()
    {
        return m_TimeOfKill;
    }
	
			
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		
		ctx.Write(m_TimeOfKill);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version)) {
			return false;
		}
		
		ctx.Read(m_TimeOfKill);

		return true;
	}
}