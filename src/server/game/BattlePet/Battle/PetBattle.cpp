#include "PetBattle.h"
#include "PetBattleEvent.h"

#include "Player.h"
#include "ObjectMgr.h"
#include "../PetJournal/PetJounral.h"
#include "WorldPacket.h"
#include "Ability/BattlePetAbility.h"
#include "PetBattleMgr.h"

/*煖醴贍?訟軫? 哀蓀淳泣 壓採 綵葉帙凹荻 特釣?AddMember, 穽迪杖打贍了寮荻贍?渟桎?
찰晤循諺 SendInitialBattle
찰晤循諺 SendInitialPetPos (秧 魏輦謫?嵬尊魏 竣迹)
?述晤循諺 InitialBattle()

콧音?幽猥粧 剪穽設?奄 全惟? ?剪橓?壯 惟桎終?荏 哀飮裝 剪穽設嶢?SendInitialPet
?惟桎尊?櫛鴨阻嶢? 妖切鏃惺? ? 桎?攸?修鴨?軸怏潗 渟躁渾, 增城埰 依詢鮑????
?張?m_round = 0, 診?破?仲典檍 蓴憶?訟軫?余?菴蓮 張 增燮診腸乙.
毘?禎軸蓮 壯 桎, 破?荏 妖切鏃寮暢?遵躁儼 ?竣赤?莘桎純前震 綵設增脣循潗 ?訟軫?
?惟宸?翟?嵬尊魏 穽迪臟典麟尊循泣 - 增燮膣諺

腦??鴨乙諺
흇尊?剪穽設?奄 憙剪 全惟? 增設夭 鎭有緘壬 member-?增城埰 m_readyToStart = true
찰晤循諺 CheckStartBattle()
?惟桎尊?穽荻儼諺 破翟??翟迪?岫?m_readyToStart = true
쿡 鎭?禎?杖特莘 張 鴨乙諺. 間?桎蟻惟 ?翟迪?m_readyToStart = true

述晤循諺 UpdateFlags()
쯩寀鳥 張?荏 瘡暹顥齧?攸?溢蓮?軸怏潗 前狀述循?壯 仲典前震 渟桎?

TODO: 壯哀 夭奄?2 剪鴨蟻裝?渟釣靭牆酷 - m_moved ?m_canMove
嶠狀?全釣鴨?諺 禎軸怏?泣 嵬尊? 蕣典迹 - 溢蓮?泣 佺 軸怏潗.
쾰 昶翟增循 逡言齧?2 uint 渟釣靭牆酷 ?PetBattle, 修鴨?春陝嶢?憙?蓴?旬巍?茵仲?
燐翟?張 禎懿妬潗 魏輦渾 調?哀增蒼 ?memberData

찰譽贍?UpdateFlags. 咬?靭藺儼?夭廬?m_moved = false
杻? ?惟莘 靭贓袍 仲典前潗 夭檍?m_canMove = true, 蕣典迹 - m_canMove = false

찰增設堯?請說? 剪穽設堯?魏輦佃?SendInitialPet
?憙迹 締檣打?剪穽設?諺 張 m_roundTime/1000, ?PET_BATTLE_WAIT_FOR_FRONT_PET_MAX_SEC

述增設堯?m_round = 1, m_state = Running

屢渟綜 1 了 嵬尊惟?軸怏? 述晤循奄? HandleAction, 惟桎調 穽迪譽賊嶢?鴨栯軫猥
?裔淳茁溢增?剪 醇賊裝?菴牆紅

?惟莊?HandleAction 茵簇寮暢?嵬尊魏, 惟桎終?禎軸怏?魏?禎軸怏馴僥 (m_moved = true)
?裔穽余齧?諺?軸怏潗 (m_canMove = false)
?穽剪外杖有 述增設?諺 禎? 壯翟典剪 (m_canMove = true)

穽荻儼諺 禎軸怏震 泣 翟?嵬尊魏 (m_moved = true 秧 翟迪?
?嚴泣 菴 桎 述晤循諺 EndRound, ?惟莊?翟調蓀執循諺 櫛岫震 惟莊?調艙菴
?增燮膣諺 狀述?調艙?

鮫孼?循悅?破翟??HandleAction 岫?述譽陝 SendEvents
腦唯?佺 哀飮孼 岫潗 述譽陝 ?EndRound ??StartRound

烙言齧?締檣打?OnTurnMaked(PBOID side)
?惟桎尊?裔炡證循諺 攸?禎軸怏? 翟狀瞬諺 請說? 述吾脣?UpdateFlags
찰晤循諺 SendEvents()

?StartRound 診唯?述晤循諺 Update 秧 魏輦謫?MemberData
쯩寀鳥 MemberData::Update 述晤循諺 Update ?魏輦謫?渟診



?締檣打?StartRound 嚴潗 InitialRound
嵌桎調 穽荻儼奄 攸?渟躁渾 軸怏? 翟狀瞬奄 請說??剪穽設?奄 幽猥粧?
淃衆??StartRound 巍奄 述吾?MemberData::Update
콧音?Pet::Update 콧音?診?巍奄 述吾?戱輒攸荻 褻堯孺.
輕蓮?穽迪吾煜?茁膣惺?, 惟宸?軸怏潗 哀飮壯 增典佺?X
孔 增典佺?Y 脹儼乙 ?鎭特杖?Update

淃懿婆秩 診? 破?增典佺?X 重跡奄 訟潗 禎 槍?靭倧脣壬 渟膣

쾰 了悚縯杖 憙謫?張翟軸怏溢 渟釣?Update 剪穽設嶢?妖締 ?桎? 破?增燮桎循?狀述?調艙?
燐翟?債佺 岫?壯張遵?槍??狀脣? ?張 ?惟莊?增燮謫?
?禎衆?渟釣甑嶢城?請說??剪穽設嶢?余?1 SendEvents

淃 巍堰, ?渟躁佃 SendEvents ( 渟釣?Update) 荏 哀飮壯 翟迪?剪穽設嶢?7 請說



SendInitialPetPos - 調葺診瞬奄 渟桎?(述晤循諺 焌麟)
SendInitialBattle - 妖擾歪泣預宗奄 渟桎?(述晤循諺 焌麟)
SendInitialPet - 增燮膣諺 訟軫?




==============================================================================
淃 巍堰 姓終 哀飮裝 震魏潗 ?惟莊?魏輦謫?調艙菴, ?張 ?壯妬音. 

珞暈葉 震魏奄 ?壯妬音 魏輦謫???嚴泣 佺 修鴨?震魏潗 ?惟莊? 桎 裔 1 軸?穽剪凹齧?2 調裔
1 調?穽?壯依蓮杖? ?蕣典迹 調??惟莊?


給袍杖? 哀蓀瞬諺 渟釣靭牆策 m_round ?惟桎尊?櫛春陝夭 round ?惟桎尊?褻堯魏 岫乙 壯依蓮壯
?涉鴨煜?穽荻儼諺: 嚴泣 鎭有陷?調艙?調橓?調艙涯 了 褻堯孺, 桎 涉鴨煜 張 述晤循諺

==============================================================================
鸞燮膣奄 調艙? 述晤循諺 Update 蓴諺 渟診??靭藺儼閃
毘?腸悅?秧 桎莘 破翟?述譽城?Update ?姓??褻堯適 ?翟調灑診潗 Multi-turn 褻堯孺

찰增設?諺 請說?禎 惟桎終?全釣鴨?諺 攸?溢蓮?軸怏潗\禎軸怏?
輕蓮?軸怏潗 嚴泣: 靭倧述 堯?仲典前潗 灑蟻袍 特??全禎張粧? 躬躁忽?哀飮裝 軸怏潗 靭藺儼? 夭廬陷?靭倧脣莘 蟾震純謫?渟診
淃軸怏? 嚴潗 蟾震純? multi-turn 褻堯魏

較穽設堯?撓 ?SendEvents 幽猥粧?

콧音??OnTurnMaked 重剪鳥?

及艙?靭?奄? 惟宸?翟?綵葉帙凹?逡言贍?軸? 橓存檍 剪靭特裝 魏?禎軸怏馴猥



較穽設?諺 撓 幽猥粧?
*/

BattlePet::pAction Actions[BATTLE_PET_ACTION_MAX] =
{
    &BattlePet::Battle::ActionForfeit,
    &BattlePet::Battle::ActionUseAbility,
    &BattlePet::Battle::ActionSwapPet,
    &BattlePet::Battle::ActionUseTrap,
    &BattlePet::Battle::ActionEndBattle,
};

BattlePet::Battle::Battle(bool isPvp, bool isLfb)
    : m_isPvp(isPvp)
    , m_isLfb(isLfb)
    , m_canMoveMask(0)
    , m_movedMask(0)
    , m_round(0)
    , m_battleId(0LL)
    , m_roundTime(PET_BATTLE_WAIT_FOR_FRONT_PET_MAX_SEC * IN_MILLISECONDS)
    , m_state(PetBattleState::StateNone)
    , m_pos(nullptr)
    , m_event(nullptr)
{
    m_event = new EventHolder();
    m_pos = new PositionData();
}

BattlePet::Battle::~Battle()
{
    Cleanup();

    m_members.clear();

    delete m_event;
    m_event = nullptr;

    delete m_pos;
    m_pos = nullptr;
}

bool BattlePet::Battle::AddMember(Unit* owner, PBOID pboid)
{
    ASSERT(m_members.size() < PET_BATTLE_OPPONENT_COUNT);

    if (pboid == PBOID::PAD_0)
    {
        for (MemberPair const& pair : m_members)
        {
            sMemberData const& member = pair.second;

            ASSERT(member);

            if (member->IsInitiator())
            {
                // TODO: error - there is another initiator
                return false;
            }
        }

        m_battleId = owner->GetGUID();
    }

    SetPosition(G3D::Vector3(owner->GetPositionX(),
        owner->GetPositionY(), owner->GetPositionZ()), pboid);

    m_members[pboid] = std::make_shared<MemberData>(this, pboid, owner);
    if (!m_members[pboid]->Initial(owner))
        return false;

    owner->SetPetBattleId(m_battleId); // TODO: ugly hack

    if (pboid == PBOID::PAD_1)
    {
        m_members[PBOID::PAD_0]->m_opponent = m_members[PBOID::PAD_1];
        m_members[PBOID::PAD_1]->m_opponent = m_members[PBOID::PAD_0];
    }

    return true;
}

void BattlePet::Battle::EndBattle(uint64 guid)
{
    if (guid == 0LL || m_state == PetBattleState::StateEnding)
        return;

    if (GetMember(guid) == nullptr)
        return;

    PBOID side = GetMember(guid)->m_side;
    PBOID winner = side == PBOID::PAD_0 ? PBOID::PAD_1 : PBOID::PAD_0;

    EndBattle(winner, PetBattleEndReason::Forfeit);
}

void BattlePet::Battle::EndBattle(PBOID winner, PetBattleEndReason reason)
{
    if (m_state == PetBattleState::StateEnding)
        return;

    m_state = PetBattleState::StateEnding;

    GiveRewards(winner, reason);

    for (MemberPair const& pair : m_members)
    {
        if (sMemberData const& member = pair.second)
        {
            if (Player* owner = sObjectAccessor->FindPlayer(member->GetOwner()))
            {
                owner->GetPetJournal()->SendPetsUpdateInLoadoutSlots(false);
            }
        }
    }

    sPetBattleMgr->RemoveBattle(m_battleId);
}

void BattlePet::Battle::GiveRewards(PBOID winner, PetBattleEndReason reason)
{
    RewardInfo info(winner, reason);

    if (sMemberData const& team = m_members[winner]) // winner team
    {
        for (PetPair const& pair : team->m_pets)
        {
            Pet* pet = pair.second;
            if (!pet)
                continue;

            uint16 xp = PET_BATTLE_XP_REWARD; // TODO - calculate proper value based on pet activity and pet status
            if (pet->IsDead())
                xp /= 1.5f;

            pet->GixeXP(xp);

            info.m_rewards.push_back(RewardInfo::RewardData(pet, xp));
        }
    }

    SendRewards(info);
}

void BattlePet::Battle::SendRewards(RewardInfo const& info)
{
    if (m_state != PetBattleState::StateEnding)
        return;

    WorldPacket data(SMSG_PET_BATTLE_REWARD);

    data.WriteBits(info.m_rewards.size(), 20);
    for (MemberPair const& pair : m_members)
    {
        data.WriteBit(pair.first == info.m_winner);
    }

    for (RewardInfo::RewardData const& reward : info.m_rewards)
    {
        /*禎魏晤循奄 40% 剪 桎莘 婆衆? 破?荏 剪穽設堯?- wtf ?*/
        ////Captured | Caged | SeenAction | AwardedXP
        data.WriteBit(false); // unk
        data.WriteBit(false); // pet loose
        data.WriteBit(true); // SeenAction
        data.WriteBit(false); // Captured
        data.WriteBit(reward.m_level == 0);
        data.WriteBit(reward.m_xp == 0);
        data.WriteBit(reward.m_oldLevel == 0);
    }

    for (MemberPair const& pair : m_members)
    {
        if (pair.first != info.m_winner)
            data.WriteBit(info.m_reason == PetBattleEndReason::Forfeit);
        else
            data.WriteBit(false);
    }

    for (uint8 i = 0; i < PET_BATTLE_OPPONENT_COUNT; ++i)
    {
        data << uint32(0); // npcId
    }

    for (RewardInfo::RewardData const& reward : info.m_rewards)
    {
        data << uint8(reward.m_pboid);
        if (reward.m_level != 0)
            data << uint16(reward.m_level);
        if (reward.m_xp != 0)
            data << uint16(reward.m_xp);

        data << int32(reward.m_hp);
        data << int32(reward.m_maxHp);

        if (reward.m_oldLevel != 0)
            data << uint16(reward.m_oldLevel);
    }

    SendPacket(&data);
}

void BattlePet::Battle::Cleanup()
{
    for (MemberPair const& pair : m_members)
    {
        sMemberData const& member = pair.second;
        if (Player* player = sObjectAccessor->FindPlayer(member->GetOwner()))
            player->SetPetBattleId(0);
    }
}

PBOID BattlePet::Battle::GetInitialSide() const
{
    uint32 pad0 = 0;
    uint32 pad1 = 0;

    for (MemberPair const& pair : m_members)
    {
        if (sMemberData const& member = pair.second)
        {
            if (Pet const* pet = member->GetActivePet())
            {
                if (pet->IsDead())
                    return member->m_side;

                if (pet->HasActiveMultiturnAbility())
                    return member->m_side == PBOID::PAD_0 ? PBOID::PAD_1 : PBOID::PAD_0;

                if (member->m_side == PBOID::PAD_0)
                    pad0 = pet->GetSpeed();
                else
                    pad1 = pet->GetSpeed();
            }
        }

    }

    if (pad0 > pad1)
        return PBOID::PAD_0;

    return PBOID::PAD_1;
}

void BattlePet::Battle::SendInitialPetPos(Player* player)
{
    m_pos->Calculate();

    sMemberData member = GetMember(player->GetGUID());
    if (!member)
        return;

    WorldPacket data(SMSG_PET_BATTLE_POSITION);
    for (int i = 0; i < 2; ++i)
    {
        G3D::Vector3 const& pos = m_pos->m_positions[member->m_side == PBOID::PAD_0 ? 0 : 1];
        data << pos.z << pos.y << pos.x;
    }

    data
        << m_pos->m_center.z
        << m_pos->m_center.x
        << m_pos->m_center.y
        ;

    data.WriteBit(G3D::fuzzyEq(m_pos->m_orientation, 0.0f));
    data.WriteBit(!true);

    if (!G3D::fuzzyEq(m_pos->m_orientation, 0.0f))
        data << m_pos->m_orientation;
    if (true) // status
        data << uint32(21);

    player->SendDirectMessage(&data);
}

void BattlePet::Battle::SetPosition(G3D::Vector3 position, PBOID side)
{
    uint8 index = side == PBOID::PAD_0 ? 0 : 1;

    m_pos->m_positions[index] = position;
}

void BattlePet::Battle::SendInitialBattle(Player* player)
{
    bool hasFrontPet = true;
    bool hasRoundTimeSecs = false;

    WorldPacket data(SMSG_PET_BATTLE_INITIAL);
    for (MemberPair const& pair : m_members)
    {
        sMemberData const& member = pair.second;

        ObjectGuid guid = IS_PLAYER_GUID(member->GetOwner()) ? member->GetOwner() : 0LL;

        data.WriteBit(guid[0]);
        data.WriteBit(guid[4]);
        data.WriteBit(TrapStatus::TRAP_STATUS_CANT_CATCH_OPPONENTS_PET == TrapStatus::TRAP_STATUS_OK);
        data.WriteBit(guid[1]);
        data.WriteBit(guid[7]);
        data.WriteBit(guid[6]);
        data.WriteBit(guid[2]);
        data.WriteBit(!hasFrontPet);
        data.WriteBit(!hasRoundTimeSecs);
        data.WriteBit(guid[5]);
        data.WriteBits(member->m_pets.size(), 2);
        
        for (PetPair const& ppair : member->m_pets)
        {
            Pet const* pet = ppair.second;
            if (!pet)
                continue;

            ObjectGuid pguid = pet->GetProto()->GetId();

            data.WriteBit(pguid[4]);
            data.WriteBit(pguid[2]);
            data.WriteBits(pet->GetAuras().size(), 21);

            for (auto& apair : pet->GetAuras())
            {
                Ability const* aura = apair.second;

                data.WriteBit(aura->IsExpired());
                data.WriteBit(m_round == 0);
                data.WriteBit(!true); // aura->GetCaster()->GetPBOID() - should always present
            }

            data.WriteBit(pguid[6]);
            data.WriteBit(pguid[3]);
            data.WriteBit(!false);
            data.WriteBits(pet->GetStates().size(), 21);
            data.WriteBit(pguid[0]);
            data.WriteBits(pet->GetAbilities().size(), 20);
            data.WriteBit(pguid[1]);
            data.WriteBits(pet->GetProto()->GetNickname().size(), 7);

            for (uint32 abilityId : pet->GetAbilities())
            {
                data.WriteBit(!true); // pet->GetPBOID() - should always present
            }

            data.WriteBit(pguid[7]);
            data.WriteBit(pguid[5]);
            data.WriteBit(!true); // hasSlot
        }

        data.WriteBit(guid[3]);
    }

    for (int i = 0; i < BATTLE_PET_MAX_LOADOUT_SLOTS; ++i)
    {
        data.WriteBits(0, 21);
        data.WriteBits(0, 21);
    }

    sMemberData const& opponent = m_members[PBOID::PAD_1];

    data.WriteBit(!false);
    data.WriteBit(PET_BATTLE_FORFEIT_PENALTY == 0);
    data.WriteBit(!false);
    data.WriteBit(true); // CanRewardXP
    data.WriteBit(!PET_BATTLE_PVP_MAX_ROUND_SEC);
    data.WriteBit(!PET_BATTLE_WAIT_FOR_FRONT_PET_MAX_SEC);
    data.WriteBit(m_isPvp);
    data.WriteBit(false); // fake

    ObjectGuid wildPet = ObjectGuid(IS_PLAYER_GUID(opponent->GetOwner()) ? 0LL : opponent->GetOwner());

    data.WriteBit(wildPet[1]);
    data.WriteBit(wildPet[0]);
    data.WriteBit(wildPet[3]);
    data.WriteBit(wildPet[7]);
    data.WriteBit(wildPet[2]);
    data.WriteBit(wildPet[6]);
    data.WriteBit(wildPet[5]);
    data.WriteBit(wildPet[4]);

    data.WriteBit(!true); // Unk

    data.WriteByteSeq(wildPet[7]);
    data.WriteByteSeq(wildPet[2]);
    data.WriteByteSeq(wildPet[6]);
    data.WriteByteSeq(wildPet[0]);
    data.WriteByteSeq(wildPet[1]);
    data.WriteByteSeq(wildPet[5]);
    data.WriteByteSeq(wildPet[4]);
    data.WriteByteSeq(wildPet[3]);

    for (MemberPair const& pair : m_members)
    {
        sMemberData const& member = pair.second;

        if (hasFrontPet)
            data << uint8(0);

        uint8 slot = 0;
        for (PetPair const& ppair : member->m_pets)
        {
            Pet const* pet = ppair.second;
            if (!pet)
                continue;

            uint8 index = 0;
            for (uint32 abilityId : pet->GetAbilities())
            {
                data << uint16(0);
                data << uint8(index++);

                if (true)
                    data << uint8(pet->GetPBOID());

                data << uint32(abilityId);
                data << uint16(0);
            }

            ObjectGuid pguid = pet->GetProto()->GetId();

            data.WriteByteSeq(pguid[7]);

            for (auto& apair : pet->GetAuras())
            {
                Ability const* aura = apair.second;

                data << uint32(aura->GetId());
                if (!aura->IsExpired())
                    data << int32(aura->GetDuration());
                if (m_round)
                    data << uint32(m_round);
                if (true)
                    data << uint8(aura->GetCaster()->GetPBOID());
                data << uint32(1);
            }

            data << uint16(pet->GetLevel());
            data.WriteByteSeq(pguid[0]);
            data << uint32(pet->GetProto()->GetSpeed());
            data.WriteByteSeq(pguid[5]);
            data << uint32(pet->GetMaxHealth());
            data.WriteByteSeq(pguid[4]);
            data << uint16(pet->GetXP());
            data << uint8(slot++);
            data.WriteByteSeq(pguid[6]);
            data.WriteByteSeq(pguid[1]);
            data << uint32(pet->GetProto()->GetSpecies());
            data.WriteByteSeq(pguid[2]);

            for (auto const kvp : pet->GetStates())
            {
                data << uint32(kvp.second); // Value
                data << uint32(kvp.first); // StateId
            }

            data << uint16(pet->GetProto()->GetQuality());
            data << uint32(pet->GetHealth());
            data.WriteByteSeq(pguid[3]);
            data << uint32(0);
            data << uint32(pet->GetProto()->GetPower());
            data << uint32(sObjectMgr->GetCreatureTemplate(pet->GetProto()->GetNPCId())->Modelid1/*pet->GetProto()->GetModel()*/);
            data.WriteString(pet->GetProto()->GetNickname());
            data << uint32(0);
        }

        ObjectGuid guid = IS_PLAYER_GUID(member->GetOwner()) ? member->GetOwner() : 0LL;

        data.WriteByteSeq(guid[5]);
        data.WriteByteSeq(guid[4]);
        if (hasRoundTimeSecs)
            data << uint16(0);

        data.WriteByteSeq(guid[1]);
        data << uint8(6);
        data.WriteByteSeq(guid[6]);

        data << uint32(TRAP_STATUS_CANT_CATCH_OPPONENTS_PET);

        data.WriteByteSeq(guid[2]);
        data << uint32(PET_BATTLE_TRAP_ABILITY_ID); // TODO:
        data.WriteByteSeq(guid[0]);
        data.WriteByteSeq(guid[7]);
        data.WriteByteSeq(guid[3]);
    }

    data << uint8(PET_BATTLE_FORFEIT_PENALTY);
    data << uint16(PET_BATTLE_WAIT_FOR_FRONT_PET_MAX_SEC);

    data << uint32(m_round);

    data << uint8(1); // CurPetBattleState
    data << uint16(PET_BATTLE_PVP_MAX_ROUND_SEC);

    player->SendDirectMessage(&data);
}

void BattlePet::Battle::SendInitialPet(Player* player)
{
    ASSERT(player);

    WorldPacket data(SMSG_PET_BATTLE_EVENT_AT_START);
    data.WriteBits(PET_BATTLE_OPPONENT_COUNT, 22);
    for (uint8 i = 0; i < PET_BATTLE_OPPONENT_COUNT; ++i)
    {
        data.WriteBit(!false);
        data.WriteBit(!PetBattleEvents::PET_SWAP); // m_eventId
        data.WriteBit(!false);
        data.WriteBit(!true);                      // m_eventTargetType
        data.WriteBit(!false);
        data.WriteBit(!false);
        data.WriteBit(!false);

        data.WriteBits(1, 25);
        {
            data.WriteBit(!true); // m_hasEventValue
            data.WriteBits(6, 3); // 6 - with 0 arguments
        }
    }

    data.WriteBits(0, 3);
    data.WriteBit(!true);
    data.WriteBits(0, 20); // m_abilityCount

    for (uint8 i = 0; i < PET_BATTLE_OPPONENT_COUNT; ++i)
    {
        PBOID target = i == 0 ? PBOID::P0_PET_0 : PBOID::P1_PET_0;
        {
            data << uint8(target); // m_eventValue
        }

        data << uint8(target);
        data << uint8(PetBattleEvents::PET_SWAP);
    }

    data << uint8(2);

    for (MemberPair const& pair : m_members)
    {
        sMemberData const& member = pair.second;

        data << uint16(m_isPvp ? PET_BATTLE_WAIT_FOR_FRONT_PET_MAX_SEC : 0);
        data << uint8(member->GetFlags());
        data << uint8(member->GetTrapStatus());
    }

    data << uint32(m_round);

    player->SendDirectMessage(&data);
}

void BattlePet::Battle::SendPacket(WorldPacket* data)
{
    for (MemberPair const& pair : m_members)
    {
        sMemberData const& member = pair.second;
        if (Player* player = sObjectAccessor->FindPlayer(member->GetOwner()))
        {
            if (player->IsInWorld())
                player->SendDirectMessage(data);
        }
    }
}

void BattlePet::Battle::SetActivePet(sMemberData& member, PBOID pboid)
{
    if (pboid == member->GetActivePet()->GetPBOID())
        return;

    member->SetActivePet(pboid);

    if (m_event)
        m_event->Make(Event::EventInfo(PetBattleEvents::PET_SWAP, pboid, 0, 0), Event::EventValue(pboid));
}

void BattlePet::Battle::CreateBattle(Unit* initiator, Unit* opponent, bool start, bool isLfb)
{
    if (initiator == nullptr || opponent == nullptr)
        return;

    BattlePet::Battle* battle = new BattlePet::Battle(true, isLfb);
    if (!battle->AddMember(initiator, PBOID::PAD_0))
    {
        delete battle;
        return;
    }

    if (!battle->AddMember(opponent, PBOID::PAD_1))
    {
        delete battle;
        return;
    }

    if (start)
        battle->InitialAllMembers();

    sPetBattleMgr->AddBattle(battle, battle->GetId());
}

void BattlePet::Battle::InitialAllMembers()
{
    for (MemberPair const& pair : m_members)
    {
        sMemberData const& member = pair.second;
        if (Player* player = sObjectAccessor->FindPlayer(member->GetOwner()))
            SendInitialToPlayer(player);
    }
}

void BattlePet::Battle::SendNewRound()
{
    WorldPacket data(SMSG_PET_BATTLE_EVENT_2);

    for (MemberPair const& pair : m_members)
    {
        if (sMemberData const& member = pair.second)
        {
            data << uint8(member->GetFlags());
            data << uint8(member->GetTrapStatus());
            data << uint16(m_isPvp ? (m_roundTime / IN_MILLISECONDS) : 0);
        }
    }

    data << uint32(m_round);

    data.WriteBits(0, 20);
    data.WriteBits(m_state == PetBattleState::StateEnding, 3);

    data.WriteBit(!m_state);
    data.WriteBits(0, 22);

    if (m_state)
        data << uint8(m_state);
    if (m_state == PetBattleState::StateEnding)
        data << uint8(3);

    SendPacket(&data);
}

void BattlePet::Battle::SendEvents()
{
    if (!m_event)
        return;

    uint32 cooldowns = 0;
    for (MemberPair const& pair : m_members)
    {
        if (sMemberData const& member = pair.second)
        {
            for (PetPair const& ppair : member->m_pets)
            {
                if (Pet const* pet = ppair.second)
                    cooldowns += pet->GetCooldowns().size();
            }
        }
    }

    WorldPacket data(SMSG_PET_BATTLE_EVENT_2);

    for (MemberPair const& pair : m_members)
    {
        if (sMemberData const& member = pair.second)
        {
            data << uint8(member->GetFlags());
            data << uint8(member->GetTrapStatus());
            data << uint16(m_isPvp ? (m_roundTime / IN_MILLISECONDS) : 0);
        }
    }

    data << uint32(m_round);

    data.WriteBits(cooldowns, 20);
    data.WriteBits(0, 3); // died pets count

    for (uint32 i = 0; i < cooldowns; ++i)
    {
        data.WriteBit(!true); // PBOID of the cooldown owner - present always in data
    }

    data.WriteBit(!m_state);
    data.WriteBits(m_event->GetEvents().size(), 22);
    for (Event const* _event : m_event->GetEvents())
    {
        Event::EventInfo const& info = _event->m_info;

        data.WriteBit(!true); // _event->m_info.m_provider - should always present
        data.WriteBit(info.m_flag == 0);
        data.WriteBit(!true); // 6
        data.WriteBit(!true); // 7
        data.WriteBit(info.m_event == PetBattleEvents::SET_HEALTH);
        data.WriteBit(!false); // 5
        data.WriteBit(info.m_abilityEffectId == 0); // effect Id to play visual
        data.WriteBits(_event->m_values.size(), 25); // targets count

        for (Event::EventValue const& value : _event->m_values)
        {
            data.WriteBit(!true); // value.m_provider - should always present
            data.WriteBits(info.GetType(), 3);

            if (info.m_event == PetBattleEvents::SET_STATE) // 3
            {
                data.WriteBit(value.state.m_stateId == 0);
                data.WriteBit(value.state.m_value == 0);
            }
            else if (info.m_event == PetBattleEvents::AURA_APPLY
                || info.m_event == PetBattleEvents::AURA_CHANGE
                || info.m_event == PetBattleEvents::AURA_CANCEL) // 1
            {
                data.WriteBit(value.aura.m_amount == 0);
                data.WriteBit(value.aura.m_currentRound == 0);
                data.WriteBit(value.aura.m_abilityId == 0);
                data.WriteBit(value.aura.m_remaingCooldown == 0);
            }
            else if (info.m_event == PetBattleEvents::STATUS_CHANGE) // 4
            {
                data.WriteBit(value.status.m_status == 0);
            }
            else if (info.m_event == PetBattleEvents::SET_SPEED) // 4
            {
                data.WriteBit(value.speed.m_speed == 0);
            }
            else if (info.m_event == PetBattleEvents::SET_MAX_HEALTH) // 4
            {
                data.WriteBit(value.maxHealth.m_health == 0);
            }
            else if (info.m_event == PetBattleEvents::SET_HEALTH)
            {
                data.WriteBit(value.health.m_health == 0); // 5
            }
            else if (info.m_event == PetBattleEvents::TRIGGER_ABILTY)
            {
                data.WriteBit(value.trigger.m_abilityId == 0); // 0
            }
        }
    }

    /*m_event->GetEvents() - > GetEffects()*/
    for (Event const* _event : m_event->GetEvents())
    {
        Event::EventInfo const& info = _event->m_info; // effects

        for (Event::EventValue const& value : _event->m_values) // _event->m_values -> m_targets
        {
            if (info.GetType() != 4)
            {
                if (true)
                    data << uint8(value.m_target);
            }

            if (info.m_event == PetBattleEvents::SET_STATE) // 3
            {
                if (value.state.m_value)
                    data << int32(value.state.m_value);
                if (value.state.m_stateId)
                    data << int32(value.state.m_stateId);
            }
            else if (info.m_event == PetBattleEvents::AURA_APPLY
                || info.m_event == PetBattleEvents::AURA_CHANGE
                || info.m_event == PetBattleEvents::AURA_CANCEL) // 1
            {
                if (value.aura.m_currentRound)
                    data << int32(value.aura.m_currentRound);
                if (value.aura.m_amount)
                    data << int32(value.aura.m_amount);
                if (value.aura.m_remaingCooldown)
                    data << int32(value.aura.m_remaingCooldown);
                if (value.aura.m_abilityId)
                    data << int32(value.aura.m_abilityId);
            }
            else if (info.m_event == PetBattleEvents::STATUS_CHANGE) // 4
            {
                if (value.status.m_status)
                    data << int32(value.status.m_status);
            }
            else if (info.m_event == PetBattleEvents::SET_SPEED) // 4
            {
                if (value.speed.m_speed)
                    data << int32(value.speed.m_speed);
            }
            else if (info.m_event == PetBattleEvents::SET_HEALTH) // 4
            {
                if (value.health.m_health)
                    data << int32(value.health.m_health);
            }
            else if (info.m_event == PetBattleEvents::SET_MAX_HEALTH) // 4
            {
                if (value.maxHealth.m_health)
                    data << int32(value.maxHealth.m_health);
            }
            else if (info.m_event == PetBattleEvents::TRIGGER_ABILTY) // 0
            {
                if (value.trigger.m_abilityId)
                    data << int32(value.trigger.m_abilityId);
            }
            //PetBattleEvents -> PetBattleEffectType

            if (info.GetType() == 4)
            {
                if (true)
                    data << uint8(value.m_target);
            }
        }
        if (info.m_flag != 0) 
            data << uint16(info.m_flag);
        if (true)
            data << uint8(info.m_provider);
        if (info.m_event)
            data << uint8(info.m_event);
        if (info.m_abilityEffectId != 0)
            data << uint32(info.m_abilityEffectId);
        if (true) // 7
            data << uint16(1);
        if (true) // 6
            data << uint8(1);
    }

    for (MemberPair const& pair : m_members)
    {
        if (sMemberData const& member = pair.second)
        {
            for (PetPair const& ppair : member->m_pets)
            {
                if (Pet const* pet = ppair.second)
                {
                    for (auto const& kvp : pet->GetCooldowns())
                    {
                        data << uint16(0); // lockdown remaing
                        data << uint16(kvp.second); // cooldown remaing
                        data << uint32(kvp.first); // ability
                        if (true)
                            data << uint8(pet->GetPBOID());

                        data << uint8(pet->GetAbilityIndex(kvp.first));
                    }
                }
            }
        }
    }

    if (m_state)
        data << uint8(m_state);
    if (false /*died pets count*/)
        data << uint8(3);

    SendPacket(&data);

    m_event->Clear();
}

void BattlePet::Battle::SendSwapReq(PBOID diedPet, PBOID side)
{
    /*WorldPacket data(SMSG_PET_BATTLE_SWAP_REQ);
    data.WriteBits(1, 22);
    //for (uint8 i = 0; i < 1; ++i)
    {
        data.WriteBit(!false); // bit6
        data.WriteBit(!false); // effectId
        data.WriteBit(!false); // bit7
        data.WriteBit(!false); // bit5
        data.WriteBit(!PetBattleEvents::PET_SWAP); // m_eventId
        data.WriteBit(!false); // bit3
        data.WriteBit(!true);                      // m_eventTargetType

        data.WriteBits(1, 25);
        {
            data.WriteBits(6, 3); // 6 - with 0 arguments
            data.WriteBit(!true); // m_hasEventValue
        }
    }

    data.WriteBits(0, 3);
    data.WriteBits(0, 20); // m_abilityCount
    data.WriteBit(!true);

    data << uint8(m_state);

    //for (uint8 i = 0; i < 1; ++i)
    {
        //PBOID target = i == 0 ? PBOID::P0_PET_0 : PBOID::P1_PET_0;
        {
            data << uint8(diedPet); // m_eventValue
        }

        data << uint8(diedPet);
        data << uint8(PetBattleEvents::PET_SWAP);
    }

    for (MemberPair const& pair : m_members)
    {
        MemberData const * member = pair.second;

        uint8 flags = 0;
        if (member->SwapReq())
            flags = BattlePetDisableFlags::Pass | BattlePetDisableFlags::Ability;
        if (member->HasMoved() || !member->CanMove())
            flags |= BattlePetDisableFlags::Pass | BattlePetDisableFlags::Ability | BattlePetDisableFlags::Swap;

        data << uint8(0);
        data << uint16(m_isPvp ? PET_BATTLE_WAIT_FOR_FRONT_PET_MAX_SEC : 0);
        data << uint8(member->GetTrapStatus());
    }

    data << uint32(m_round);

    if (Player* player = sObjectAccessor->FindPlayer(m_members[side]->GetOwner()))
        player->SendDirectMessage(&data);*/
}

void BattlePet::Battle::HandleAction(Unit* unit, ActionInfo const* action)
{
    if (!unit || !action)
        return;

    if (m_state == PetBattleState::StateEnding)
        return;

    if (action->m_action >= BATTLE_PET_ACTION_MAX)
        return;

    sMemberData member = GetMember(unit->GetGUID());
    if (!(*this.*Actions[action->m_action])(action, member))
        return;

    OnActionPerformed(member->m_side, (BattlePetActionType)action->m_action);
}

void BattlePet::Battle::InitialBattle()
{
    if (IsStarted())
    {
        sLog->OutTrinity("BattlePet::Battle:StartBattle error! Trying to start battle, but battle already started");
        return;
    }

    UpdateFlags();

    for (MemberPair const& pair : m_members)
    {
        if (sMemberData const& member = pair.second)
        {
            if (Player* player = sObjectAccessor->FindPlayer(member->GetOwner()))
                SendInitialPet(player);
        }
    }

    m_round = 1;
    m_state = PetBattleState::StateBeginning;
    m_roundTime = PET_BATTLE_WAIT_FOR_FRONT_PET_MAX_SEC * IN_MILLISECONDS;
}

void BattlePet::Battle::InitialMember(Player* player)
{
    if (IsStarted() || IsEnded())
        return;

    if (!player || !player->GetSession())
        return; 

    if (player->GetSession()->PlayerLogout())
        return;

    sMemberData member = GetMember(player->GetGUID());
    if (member->m_initialized)
        return; // already initialized

    member->m_initialized = true;
    sMemberData const& opponent = member->GetOpponent();
    if (opponent->m_initialized)
        InitialBattle();
}

void BattlePet::Battle::SendInitialToPlayer(Player* player)
{
    if (IsStarted() || IsEnded())
        return;

    if (!player || !player->GetSession())
        return;

    if (player->GetSession()->PlayerLogout())
        return;

    SendInitialPetPos(player);
    SendInitialBattle(player);
}

void BattlePet::Battle::Update(uint32 const diff)
{
    if (!IsStarted())
        return;

    if (m_state == PetBattleState::StateEnding)
        return;

    m_roundTime -= diff;
    if (m_roundTime <= 0)
    {
        EndRound();
    }
}

void BattlePet::Battle::StartRound()
{
    if (!IsStarted())
        return;

    SendEvents(); // 剪穽設?諺 妖締 ?重孼?調艙菴

    UpdateFlags(); // 全釣鴨?諺 攸?軸怏?渟躁渾
    SendNewRound();

    TryEndRound(); // 憙?壯哀 壯 衆綵纖 嚴泣 2 渟診 夭廬?multi-turn 褻堯孺.
}

void BattlePet::Battle::EndRound()
{
    for (auto& pair : m_members)
    {
        if (sMemberData& member = pair.second)
            member->Update();
    }

    for (auto& pair : m_members)
    {
        sMemberData& data = pair.second;
        if (!data || !data->SwapReq())
            continue;

        for (PetPair const& ppair : data->m_pets)
        {
            Pet* temp = ppair.second;
            if (temp->IsDead())
                continue;

            SetActivePet(data, temp->GetPBOID());
            SendEvents();
            break;
        }
    }

    m_round += 1;
    m_roundTime = PET_BATTLE_WAIT_FOR_FRONT_PET_MAX_SEC * IN_MILLISECONDS;

    StartRound();
}

void BattlePet::PositionData::Calculate()
{
    /*TODO: distance between 2 players must equal 10*/

    G3D::Vector3 minimum = m_positions[0].min(m_positions[1]);
    G3D::Vector3 maximum = m_positions[0].max(m_positions[1]);

    m_center = m_positions[0].min(m_positions[1]);
    m_center += (maximum - minimum) / 2.0f;

    G3D::Vector3 const& one = m_positions[0];
    G3D::Vector3 const& second = m_positions[1];

    float dx = second.x - one.x;
    float dy = second.y - one.y;

    float angle = atan2(dy, dx);
    m_orientation = (angle >= 0) ? angle : 2 * M_PI + angle;
}

void BattlePet::Battle::UpdateFlags()
{
    PBOID side = GetInitialSide();

    m_movedMask = 0;
    m_canMoveMask = 1 << side;

    for (auto& pair : m_members)
    {
        if (sMemberData const& member = pair.second)
        {
            /*찔?調灑診奄, 狀 賊狀 狀 - ??multi turn 褻堯孺 春陝潗? 張 ?魏增儼? ??墮泣, 桎
            壯?壯哀 穽荻儼潗 壯泣婆?診惟?褻堯孺 ?余?重剪釣潗 攸?檍 瞬雪言業.
            
            輕悅??惟章疾瘡桎釣 增設嶢?魏增儼?m_hasActiveMultiTurnAbility = true
            ??鴨增宗攸典?false*/
            if (member->GetActivePet()->HasActiveMultiturnAbility())
            {
                m_movedMask |= 1 << member->m_side;
            }
        }
    }
}

void BattlePet::Battle::OnActionPerformed(PBOID side, BattlePetActionType action)
{
    SetMoved(side, true);
    SetCanMove(side, false);

    PBOID opponent = side == PBOID::PAD_0 ? PBOID::PAD_1 : PBOID::PAD_0;
    if (!HasMoved(opponent))
        SetCanMove(opponent, true);

    SendEvents();

    TryEndRound();
}

void BattlePet::Battle::TryEndRound()
{
    uint8 count = 0;
    for (uint8 pad = PBOID::PAD_0; pad <= PBOID::PAD_1; ++pad)
    {
        if (HasMoved(PBOID(pad)))
            ++count;
    }

    if (count != PET_BATTLE_OPPONENT_COUNT)
        return;

    EndRound();
}

bool BattlePet::Battle::ActionForfeit(ActionInfo const* action, BattlePet::sMemberData member)
{
    EndBattle((member && member->IsInitiator()) ? PBOID::PAD_1 : PBOID::PAD_0, PetBattleEndReason::Forfeit);
    return false;
}

bool BattlePet::Battle::ActionUseAbility(ActionInfo const* action, BattlePet::sMemberData member)
{
    if (!member || !member->GetOpponent())
        return false;

    if (!CanMove(member->m_side) || HasMoved(member->m_side))
        return false; // TODO: cheater ?

    if (action->m_abilityId == 0)
        return false;

    member->GetActivePet()->CastAbility(action->m_abilityId);
    return true;
}

bool BattlePet::Battle::ActionSwapPet(ActionInfo const* action, BattlePet::sMemberData member)
{
    if (!CanMove(member->m_side) || HasMoved(member->m_side))
        return false; // TODO: cheater ?

    uint32 index = action->m_petIndex;

    ASSERT(index < member->m_pets.size());

    PBOID pboid = member->IsInitiator() ? PBOID(P0_PET_0 + index) : PBOID(P1_PET_0 + index);
    if (pboid != member->GetActivePet()->GetPBOID())
        SetActivePet(member, pboid);
    //else
        // Pass round

    return true;
}

bool BattlePet::Battle::ActionUseTrap(ActionInfo const* action, BattlePet::sMemberData member)
{
    //TODO: not implemented
    return true;
}

bool BattlePet::Battle::ActionEndBattle(ActionInfo const* action, BattlePet::sMemberData member)
{
    return false;
}
