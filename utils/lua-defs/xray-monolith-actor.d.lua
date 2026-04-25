---@meta

-- Exported in src\xrGame\ActorCondition_script.cpp

---@class SBooster
---@field fBoostTime number
---@field fBoostValue number
---@field m_type number -- TODO: not sure.

---@class CWound
CWound = {}

function CWound:TypeSize() end
function CWound:BloodSize() end
function CWound:AddHit() end
function CWound:Incarnation() end
function CWound:TotalSize() end
function CWound:SetBoneNum() end
function CWound:GetBoneNum() end
function CWound:GetParticleBoneNum() end
function CWound:SetParticleBoneNum() end
function CWound:SetDestroy() end
function CWound:GetDestroy() end

---@class CEntityCondition
CEntityCondition = {}

function CEntityCondition:AddWound() end
function CEntityCondition:ClearWounds() end
function CEntityCondition:GetWhoHitLastTimeID() end
function CEntityCondition:GetPower() end
function CEntityCondition:SetPower() end
function CEntityCondition:GetRadiation() end
function CEntityCondition:GetPsyHealth() end
function CEntityCondition:GetSatiety() end
function CEntityCondition:GetEntityMorale() end
function CEntityCondition:GetHealthLost() end
function CEntityCondition:IsLimping() end
function CEntityCondition:ChangeSatiety() end
function CEntityCondition:ChangeHealth() end
function CEntityCondition:ChangePower() end
function CEntityCondition:ChangeRadiation() end
function CEntityCondition:ChangePsyHealth() end
function CEntityCondition:ChangeAlcohol() end
function CEntityCondition:SetMaxPower() end
function CEntityCondition:GetMaxPower() end
function CEntityCondition:ChangeEntityMorale() end
function CEntityCondition:ChangeBleeding() end
function CEntityCondition:BleedingSpeed() end

---@enum CEntityCondition.EBoostParams
CEntityCondition.EBoostParams = {
    eBoostHpRestore = 0,
    eBoostPowerRestore = 1,
    eBoostRadiationRestore = 2,
    eBoostBleedingRestore = 3,
    eBoostMaxWeight = 4,
    eBoostRadiationProtection = 5,
    eBoostTelepaticProtection = 6,
    eBoostChemicalBurnProtection = 7,
    eBoostBurnImmunity = 8,
    eBoostShockImmunity = 9,
    eBoostRadiationImmunity = 10,
    eBoostTelepaticImmunity = 11,
    eBoostChemicalBurnImmunity = 12,
    eBoostExplImmunity = 13,
    eBoostStrikeImmunity = 14,
    eBoostFireWoundImmunity = 15,
    eBoostWoundImmunity = 16
}  -- TODO: Verify values

---@class CActorCondition
---@field m_MaxWalkWeight number
---@field m_fJumpPower number
---@field m_fStandPower number
---@field m_fJumpWeightPower number
---@field m_fWalkWeightPower number
---@field m_fOverweightWalkK number
---@field m_fOverweightJumpK number
---@field m_fAccelK number
---@field m_fSprintK number
---@field m_condition_flags flags16
CActorCondition = {}

function CActorCondition:ClearAllBoosters() end
function CActorCondition:ApplyBooster() end
function CActorCondition:BoosterForEach() end
function CActorCondition:WoundForEach() end
function CActorCondition:V_Satiety() end
function CActorCondition:V_SatietyPower() end
function CActorCondition:V_SatietyHealth() end
function CActorCondition:SatietyCritical() end
function CActorCondition:GetSatiety() end
function CActorCondition:SetPsyBar() end
function CActorCondition:GetPsyBar() end
function CActorCondition:BoostMaxWeight() end
function CActorCondition:BoostHpRestore() end
function CActorCondition:BoostPowerRestore() end
function CActorCondition:BoostRadiationRestore() end
function CActorCondition:BoostBleedingRestore() end
function CActorCondition:BoostBurnImmunity() end
function CActorCondition:BoostShockImmunity() end
function CActorCondition:BoostRadiationImmunity() end
function CActorCondition:BoostTelepaticImmunity() end
function CActorCondition:BoostChemicalBurnImmunity() end
function CActorCondition:BoostExplImmunity() end
function CActorCondition:BoostStrikeImmunity() end
function CActorCondition:BoostFireWoundImmunity() end
function CActorCondition:BoostWoundImmunity() end
function CActorCondition:BoostRadiationProtection() end
function CActorCondition:BoostTelepaticProtection() end
function CActorCondition:BoostChemicalBurnProtection() end
function CActorCondition:IsLimping() end
function CActorCondition:IsCantWalk() end
function CActorCondition:IsCantWalkWeight() end
function CActorCondition:IsCantSprint() end

---@enum CActorCondition.condition_flags
CActorCondition.condition_flags = {
    eCriticalPowerReached = 0,
    eCriticalBleedingSpeed = 1,
    eCriticalSatietyReached = 2,
    eCriticalRadiationReached = 5,
    eWeaponJammedReached = 8,
    ePhyHealthMinReached = 16,
    eCantWalkWeight = 32,
    eCantWalkWeightReached = 64
}

-- Exported in src\xrGame\actor_script.cpp

---@class CActor
CActor = {}

function CActor:conditions() end
function CActor:inventory_disabled() end
function CActor:set_inventory_disabled() end

---@class CLevelChanger
