modded class PlayerBase
{
    // DateTime
    protected int m_TimeOfKill = -1;

    void PlayerBase()
    {
        RegisterNetSyncVariableInt("m_TimeOfKill");

        GetGame().GetUpdateQueue(CALL_CATEGORY_GAMEPLAY).Insert(UpdateTimeToLive);
    }

    protected void UpdateTimeToLive()
    {
		NeckExplosive explosive = NeckExplosive.Cast(GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("Slot_NeckExplosive")));
        if (DateTime.Now() >= m_TimeOfKill && m_TimeOfKill != -1) {    
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
    }

    void SetTimeToLive(DateTime time)
    {
        if (!GetGame().IsServer()) {
            return;
        }

        m_TimeOfKill = time;
        SetSynchDirty();
    }

    void AddTimeToLive(int time)
    {
        if (!GetGame().IsServer()) {
            return;
        }

        m_TimeOfKill += time;
        SetSynchDirty();
    }

    DateTime GetTimeToLive()
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