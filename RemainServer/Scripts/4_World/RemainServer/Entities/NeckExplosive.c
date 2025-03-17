class NeckExplosive: Clothing
{	
	static const float FUSE_TIMER = 10.0;
	static const string EXPLOSION_TYPE = "CollarExplosion";
	static const string MEMORY_POINT_SPEAKER = "speaker_pos";
	
	static const int SLOT_ID = InventorySlots.GetSlotIdFromString("NeckExplosive");
	
	protected ref EffectSound m_DetontationSound;
	
	protected int m_DetonationTime = -1;
	protected ScriptedLightBase m_StatusLight;
	
	void NeckExplosive()
	{
		RegisterNetSyncVariableInt("m_DetonationTime", -1, int.MAX);
	}
	
	void ~NeckExplosive()
	{
		if (GetGame()) {
			GetGame().GetUpdateQueue(CALL_CATEGORY_SYSTEM).Remove(OnExplosiveTimer);
		}
		
		StopSoundSet(m_DetontationSound);
	}
	
	override void EEInit()
	{
		super.EEInit();
		
#ifndef SERVER
		m_StatusLight = PointLightBase.CreateLight(PointLightBase);
#endif
	}
			
	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);
		
		parent.GetInventory().SetSlotLock(slot_id, true);
	}
		
	override void OnDamageDestroyed(int oldLevel)
	{
		super.OnDamageDestroyed(oldLevel);
		
		//PlayNarratorLine(NarratorLine.TERMINATING);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(Terminate, 1000);
	}
	
	protected void Terminate()
	{
		Explode(DT_EXPLOSION, EXPLOSION_TYPE);
		PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
		if (player) {			
			//player.SetHeadInvisible(true);
		}
		
#ifdef SERVER
		DamageSystem.ExplosionDamage(this, player, EXPLOSION_TYPE, GetWorldPosition(), DamageType.EXPLOSION);
#else
		vector head_position = GetWorldPosition();
		if (player) {
			MiscGameplayFunctions.GetHeadBonePos(player, head_position);
		}
		
		Particle.PlayInWorld(ParticleList.M67, head_position);
		StopSoundSet(m_DetontationSound);
#endif
	}
		
	protected void OnExplosiveTimer()
	{
		if (m_DetonationTime == -1) {
			// Disarmed
			GetGame().GetUpdateQueue(CALL_CATEGORY_SYSTEM).Remove(OnExplosiveTimer);
			return;
		}
		
		int now = DateTime.Now();		
		if (now > m_DetonationTime) {
			GetGame().GetUpdateQueue(CALL_CATEGORY_SYSTEM).Remove(OnExplosiveTimer);
			SetHealth("GlobalHealth", "Health", 0);
		}
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if (GetDetonationTimeRemaining() > 0 && IsAlive()) {
			StopSoundSet(m_DetontationSound);
			m_DetontationSound = SEffectManager.PlaySoundOnObject("Beep_SoundSet", this, 0, 0, true);
		} else {
			StopSoundSet(m_DetontationSound);
		}
	}
		
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version)) {
			return false;
		}

		return true;
	}
		
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
	}
	
	void SetDetonationTimer(TimeSpan time)
	{
		m_DetonationTime = DateTime.Now() + time;
		DumpStack();
#ifdef SERVER
		GetGame().GetUpdateQueue(CALL_CATEGORY_SYSTEM).Insert(OnExplosiveTimer);
		SetSynchDirty();
		
		PlayerBase player_owner = PlayerBase.Cast(GetHierarchyRootPlayer());
		if (player_owner) {
			//player_owner.PlayerTagImageState = ePlayerTagImageState.WARNING_TOXICITY;
			player_owner.SetSynchDirty();
		}
#endif
	}
	
	void ClearDetonationTimer()
	{
		m_DetonationTime = -1;
	}
	
	int GetDetonationTimeRemaining()
	{
		if (m_DetonationTime == -1) {
			return -1;
		}
		
		return m_DetonationTime - DateTime.Now();
	}
		
	bool IsDetonated()
	{
		return IsDamageDestroyed();
	}
}