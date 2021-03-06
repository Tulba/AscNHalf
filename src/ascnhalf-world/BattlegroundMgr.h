/*
  * AscNHalf MMORPG Server
  * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
  * Copyright (C) 2010 AscNHalf Team <http://ascnhalf.scymex.info/>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU Affero General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU Affero General Public License for more details.
  *
  * You should have received a copy of the GNU Affero General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

#ifndef __BATTLEGROUNDMGR_H
#define __BATTLEGROUNDMGR_H

class CBattleground;
class MapMgr;
class Player;
class Map;
class Group;
class Corpse;

enum BattleGroundTypes
{
	BATTLEGROUND_ALTERAC_VALLEY			= 1,
	BATTLEGROUND_WARSONG_GULCH			= 2,
	BATTLEGROUND_ARATHI_BASIN			= 3,
	BATTLEGROUND_ARENA_2V2				= 4,
	BATTLEGROUND_ARENA_3V3				= 5,
	BATTLEGROUND_ARENA_5V5				= 6,
	BATTLEGROUND_EYE_OF_THE_STORM		= 7,
	BATTLEGROUND_ARENA					= 8,
	BATTLEGROUND_STRAND_OF_THE_ANCIENTS	= 9,
	BATTLEGROUND_UNK1					= 10,
	BATTLEGROUND_UNK2					= 11,
	// 12-29 Non Existant
	BATTLEGROUND_ISLE_OF_CONQUEST		= 30,
	// 31 Non Existant
	BATTLEGROUND_UNK3					= 32,
	BATTLEGROUND_NUM_TYPES				= 33,
};

enum BattleGroundBracketId                                  // bracketId for level ranges
{
    BG_BRACKET_ID_FIRST          = 0,
    BG_BRACKET_ID_LAST           = 15
};

// must be max value in PvPDificulty slot+1
#define MAX_BATTLEGROUND_BRACKETS  16

struct BGScore
{
	uint32 KillingBlows;
	uint32 HonorableKills;
	uint32 Deaths;
	uint32 BonusHonor;
	uint32 DamageDone;
	uint32 HealingDone;

	// the max one for this is , for AV
	uint32 MiscData[5];
};

// bg score declarations
#define BG_SCORE_WSG_FLAG_CAPTURES			0
#define BG_SCORE_WSG_FLAG_RETURNS			1
#define BG_SCORE_AB_BASE_ASSAULTED			0
#define BG_SCORE_AB_BASE_DEFENDED			1
#define BG_SCORE_AV_GRAVEYARDS_ASSAULTED	0
#define BG_SCORE_AV_GRAVEYARDS_DEFENDED		1
#define BG_SCORE_AV_TOWERS_ASSAULTED		2
#define BG_SCORE_AV_TOWERS_DEFENDED			3
#define BG_SCORE_AV_MINES_CAPTURES			4
#define BG_SCORE_EOTS_FLAG_CAPTURES			0
#define BG_SCORE_SOTA_DESTROY_DEMOLISHER	0
#define BG_SCORE_SOTA_DESTROY_GATE			1
#define BG_SCORE_SOTA_BASE_ASSAULTED		2
#define BG_SCORE_SOTA_BASE_DEFENDED			3
#define BG_SCORE_IOC_BASE_ASSAULTED			0
#define BG_SCORE_IOC_BASE_DEFENDED			1

#define SOUND_BATTLEGROUND_BEGIN			0xD6F
#define SOUND_HORDE_SCORES					8213
#define SOUND_ALLIANCE_SCORES				8173
#define SOUND_ALLIANCE_CAPTURE				8174
#define SOUND_HORDE_CAPTURE					8212
#define SOUND_ALLIANCE_RETURNED				8192
#define SOUND_HORDE_RETURNED				8192	// huh?
#define SOUND_HORDEWINS						8454
#define SOUND_ALLIANCEWINS					8455
#define SOUND_HORDE_BGALMOSTEND				0x2108
#define SOUND_ALLIANCE_BGALMOSTEND			0x2109

#define RESURRECT_SPELL						21074   // Spirit Healer Res
#define BG_DESERTER							26013
#define BG_RECENTLY_DROPPED_FLAG			42792
#define BG_PREPARATION						44521
#define BG_REVIVE_PREPARATION				44535

// AV define's
#define AV_UNCONTROLED_SNOWFALL_GRAVE				0x7AE //1 -> show uncontrolled

#define AV_CONTROLED_ICEBLOOD_TOWER_HORDE			0x569 //1 -> horde controled
#define AV_CONTROLED_TOWER_POINT_HORDE				0x568 //1 -> horde controled
#define AV_CONTROLED_FROSTWOLF_RELIFHUNT_HORDE		0x532 //1 -> horde controled
#define AV_CONTROLED_EAST_FROSTWOLF_TOWER_HORDE		0x567 //1 -> horde controled
#define AV_CONTROLED_WEST_FROSTWOLF_TOWER_HORDE		0x566 //1 -> horde controled
#define AV_CONTROLED_ICEBLOOD_GRAVE_HORDE			0x543 //1 -> horde controled
#define AV_CONTROLED_FROSTWOLF_GRAVE_HORDE			0x53A //1 -> horde controled

#define AV_CONTROLED_IRONDEEP_MINE_TROGG			0x550 //1 -> trogg controled
#define AV_CONTROLED_COLDTHOOT_MINE_KOBOLT			0x54D //1 -> kobolt controled

#define AV_CONTROLED_STORMPIKE_GRAVE_ALLIANCE		0x535 //1 -> alliance controled
#define AV_CONTROLED_STONEHEART_BUNKER_ALLIANCE		0x554 //1 -> alliance controled
#define AV_CONTROLED_ICEWING_BUNKER_ALLIANCE		0x553 //1 -> alliance controled
#define AV_CONTROLED_DUBALDER_NORTH_BUNKER_ALLIANCE	0x552 //1 -> alliance controled
#define AV_CONTROLED_DUBALDER_SOUTH_BUNKER_ALLIANCE	0x551 //1 -> alliance controled
#define AV_CONTROLED_STORMPIKE_AID_STATION_ALLIANCE	0x52D //1 -> alliance controled
#define AV_CONTROLED_STONEHEART_GRAVE_ALLIANCE		0x516 //1 -> alliance controled

static inline uint32 GetLevelGrouping(uint32 level)
{
	if(level < 10)
		return 0;
	else if(level < 20)
		return 1;
	else if(level < 30)
		return 2;
	else if(level < 40)
		return 3;
	else if(level < 50)
		return 4;
	else if(level < 60)
		return 5;
	else if(level < 70)
		return 6;
	else if(level < 80)
		return 7;
	else
		return 8;
}
#define MAX_LEVEL_GROUP 9
#define LEVEL_GROUP_RATED_ARENA 8
#define BG_ANTI_CHEAT 1

class SERVER_DECL CBattlegroundManager : public Singleton<CBattlegroundManager>, public EventableObject
{
	/* Battleground Instance Map */
	map<uint32, CBattleground* > m_instances[BATTLEGROUND_NUM_TYPES];
	Mutex m_instanceLock;

	/* Max Id */
	uint32 m_maxBattlegroundId;
	
	/* Queue System */
	// Instance Id -> list<Player guid> [ BattlegroundType ] (instance 0 - first available)
	list<uint32> m_queuedPlayers[BATTLEGROUND_NUM_TYPES][MAX_LEVEL_GROUP];

	// Instance Id -> list<Group id> [BattlegroundType][LevelGroup]
	list<uint32> m_queuedGroups[BATTLEGROUND_NUM_TYPES];

	// Last 10 players average wait time
	uint32 m_averageQueueTimes[BATTLEGROUND_NUM_TYPES][10];

	Mutex m_queueLock;

public:
	CBattlegroundManager();
	~CBattlegroundManager();
	void Init();

	/* Packet Handlers */
	void HandleBattlegroundListPacket(WorldSession * m_session, uint32 BattlegroundType, bool battlemaster = true, bool random = false);
	void HandleArenaJoin(WorldSession * m_session, uint32 BattlegroundType, uint8 as_group, uint8 rated_match);

	/* Player Logout Handler */
	void OnPlayerLogout(Player* plr);

	/* Handler On Update Event */
	void EventQueueUpdate(bool forceStart);

	/* Handle Battleground Join */
	void HandleBattlegroundJoin(WorldSession * m_session, WorldPacket & pck);

	/* Remove Player From All Queues */
	void RemovePlayerFromQueues(Player* plr);
	void RemoveGroupFromQueues(Group * grp);

	/* Create a battleground instance of type x */
	CBattleground* CreateInstance(uint32 Type, uint32 LevelGroup);

	/* Can we create a new instance of type x level group y? (NO LOCK!) */
	bool CanCreateInstance(uint32 Type, uint32 LevelGroup);

	/* Deletes a battleground (called from MapMgr) */
	void DeleteBattleground(CBattleground* bg);

	/* Build SMSG_BATTLEFIELD_STATUS */
	//void SendBattlefieldStatus(Player* plr, uint32 Status, uint32 Type, uint32 InstanceID, uint32 Time, uint32 MapId, uint8 RatedMatch);

	/* Gets ArenaTeam info from group */
	uint32 GetArenaGroupQInfo(Group * group, int type, uint32 *avgRating);

	/* Creates an arena with groups group1 and group2 */
	int CreateArenaType(int type, Group * group1, Group * group2);

	/* Add player to bg team */
	void AddPlayerToBgTeam(CBattleground* bg, deque<Player*  > *playerVec, uint32 i, uint32 j, int Team);

	/* Add player to bg */
	void AddPlayerToBg(CBattleground* bg, deque<Player*  > *playerVec, uint32 i, uint32 j);

	/* Add a group to an arena */
	void AddGroupToArena(CBattleground* bg, Group * group, int nteam);

	void SendBattlegroundQueueStatus(Player* plr, uint32 queueSlot);

	/* Gets the average queue time (from last 10 players) */
	uint32 GetAverageQueueTime(uint32 BgType);

	/* Adds a new queueTime for average calculation */
	void AddAverageQueueTime(uint32 BgType, uint32 queueTime);
	
	uint32 GetBGMinlevel(uint32 mapid)
	{
		for(uint32 i = 0; i < dbcPvPDifficulty.GetNumRows(); ++i)
		{
			if (PvPDifficultyEntry* entry = dbcPvPDifficulty.LookupEntry(i))
				if (entry->mapId == mapid && entry->bracketId == 0)
				{
					return (entry->minLevel);			
				}
		}
		return 0;
	}
};

class SERVER_DECL CBattleground : public EventableObject
{
protected:
	/* Groups */
	Group * m_groups[2];

	time_t m_nextPvPUpdateTime;
	MapMgr* m_mapMgr;
	uint32 m_id;
	uint32 m_type;
	uint32 m_levelGroup;
	int32 m_deltaRating[2];

	uint32 startTime;

public:
	// for av node usage
	friend class AVNode;

	/* Team->Player Map */
	set<Player*  > m_players[2];
	void Lock() { m_mainLock.Acquire(); }
	void Unlock() { m_mainLock.Release(); }
	INLINE bool IsArena() { return (m_type >= BATTLEGROUND_ARENA_2V2 && m_type <= BATTLEGROUND_ARENA_5V5); }

protected:
	/* PvP Log Data Map */
	map<uint32, BGScore> m_pvpData;

	/* Lock for all player data */
	Mutex m_mainLock;

	/* Player count per team */
	uint32 m_playerCountPerTeam;

	/* "pending" players */
	set<uint32> m_pendPlayers[2];

	/* starting time */
	uint32 m_startTime;
	bool m_started;
	bool m_shadowsightspawned;

	/* countdown stuff */
	uint32 m_countdownStage;

	/* winner stuff */
	bool m_ended;
	uint8 m_losingteam;

	/* resurrect queue */
	map<Creature*, set<uint32> > m_resurrectMap;
	uint32 m_lastResurrect;

	bool m_isWeekend;

public:

	void SendChatMessage(uint32 Type, uint64 Guid, const char * Format, ...);

	/* Hook Functions */
	virtual void HookOnPlayerDeath(Player* plr) = 0;

	/* Repopping - different battlegrounds have different ways of handling this */
	virtual bool HookHandleRepop(Player* plr) = 0;

	/* In CTF battlegrounds mounting will cause you to lose your flag. */
	virtual void HookOnMount(Player* plr) = 0;

	/* Only used in CTF (as far as I know) */
	virtual void HookFlagDrop(Player* plr, GameObject* obj) = 0;
	virtual void HookFlagStand(Player* plr, GameObject* obj) = 0;

	/* Used when a player kills a unit/Player* */
	virtual void HookOnPlayerKill(Player* plr, Unit* pVictim) = 0;
	virtual void HookOnHK(Player* plr) = 0;

	/* On Area Trigger */
	virtual void HookOnAreaTrigger(Player* plr, uint32 id) = 0;

	/* On Shadow Sight */
	virtual void HookOnShadowSight() = 0;

	/* Used to generate loot for players (AV) */
	virtual void HookGenerateLoot(Player* plr, Corpse* pCorpse) = 0;
	virtual bool SupportsPlayerLoot() = 0;

	/* Retreival Functions */
	INLINE uint32 GetId() { return m_id; }
	INLINE uint32 GetLevelGroup() { return m_levelGroup; }
	INLINE MapMgr* GetMapMgr() { return m_mapMgr; }

	/* Creating a battleground requires a pre-existing map manager */
	CBattleground( MapMgr* mgr, uint32 id, uint32 levelgroup, uint32 type);
	virtual ~CBattleground();
	virtual void Init();

	/* Has it ended? */
	INLINE bool HasEnded() { return m_ended; }
	INLINE bool HasStarted() { return m_started; }

	/* Send the pvp log data of all players to this player. */
	void SendPVPData(Player* plr);

	/* Get the starting position for this team. */
	virtual LocationVector GetStartingCoords(uint32 Team) = 0;

	/* Send a packet to the entire battleground */
	void DistributePacketToAll(WorldPacket * packet);

	/* send a packet to only this team */
	void DistributePacketToTeam(WorldPacket * packet, uint32 Team);

	/* play sound to this team only */
	void PlaySoundToTeam(uint32 Team, uint32 Sound);

	/* play sound to all */
	void PlaySoundToAll(uint32 Sound);

	/* Full? */
	INLINE bool IsFull() { return !(HasFreeSlots(0) || HasFreeSlots(1)); }

	/* Are we full? */
	bool HasFreeSlots(uint32 Team)
	{
		m_mainLock.Acquire();
		bool res = ((m_players[Team].size() + m_pendPlayers[Team].size()) < m_playerCountPerTeam);
		m_mainLock.Release();
		return res;
	}

	/* Add Player* */
	void AddPlayer(Player* plr, uint32 team);
	virtual void OnAddPlayer(Player* plr) = 0;

	/* Remove Player* */
	void RemovePlayer(Player* plr, bool logout);
	virtual void OnRemovePlayer(Player* plr) = 0;

	/* Port Player* */
	void PortPlayer(Player* plr, bool skip_teleport = false);
	virtual void OnCreate() = 0;

	/* Remove pending Player* */
	void RemovePendingPlayer(Player* plr);

	/* Gets the number of free slots */
	uint32 GetFreeSlots(uint32 t)
	{
		m_mainLock.Acquire();
		size_t s = m_playerCountPerTeam - m_players[t].size() - m_pendPlayers[t].size();
		m_mainLock.Release();
		return (uint32)s;
	}

	GameObject* SpawnGameObject(uint32 entry,float x, float y, float z, float o, uint32 flags, uint32 faction, float scale);
	Creature* SpawnCreature(uint32 entry,float x, float y, float z, float o);
	Vehicle* SpawnVehicle(uint32 entry, float x, float y, float z, float o);
	void UpdatePvPData();

	INLINE uint32 GetStartTime() { return m_startTime; }
	INLINE uint32 GetType() { return m_type; }

	// events should execute in the correct context
	int32 event_GetInstanceID();
	void EventCreate();

	virtual const char * GetName() = 0;
	void EventCountdown();

	virtual void Start();
	virtual void OnStart() {}
	void Close();
	virtual void OnClose() {}

	Creature* SpawnSpiritGuide(float x, float y, float z, float o, uint32 horde);

	INLINE uint32 GetLastResurrect() { return m_lastResurrect; }
	void AddSpiritGuide(Creature* pCreature);
	void RemoveSpiritGuide(Creature* pCreature);
	void QueuePlayerForResurrect(Player* plr, Creature* spirit_healer);
	void RemovePlayerFromResurrect(Player* plr, Creature* spirit_healer);
	void EventResurrectPlayers();
	virtual bool CanPlayerJoin(Player* plr);
	virtual bool CreateCorpse(Player* plr) { return true; }
	virtual bool HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell);

	void BuildPvPUpdateDataPacket(WorldPacket * data);
	virtual uint8 Rated() { return 0; }
	void OnPlayerPushed(Player* plr);
	void QueueAtNearestSpiritGuide(Player* plr, Creature* old);
	void GiveHonorToTeam(uint32 team, uint32 amt);

	virtual void SetIsWeekend(bool isweekend) {}
};

#define BattlegroundManager CBattlegroundManager::getSingleton( )

	
#endif
