---@meta

-- Exported in src\xrGame\antirad_script.cpp

---@class CAntirad:game_object

-- Exported in src\xrGame\artefact_script.cpp

---@class CArtefact:game_object
---@field m_bCanSpawnZone boolean
---@field m_fHealthRestoreSpeed number
---@field m_fRadiationRestoreSpeed number
---@field m_fSatietyRestoreSpeed number
---@field m_fPowerRestoreSpeed number
---@field m_fBleedingRestoreSpeed number
---@field m_additional_weight number
CArtefact = {}

function CArtefact:ActivateArtefact() end
function CArtefact:CanBeActivated() end
function CArtefact:AdditionalInventoryWeight() end
function CArtefact:FollowByPath() end
function CArtefact:SwitchVisibility() end
function CArtefact:GetAfRank() end

---@class CMercuryBall:CArtefact
---@class CBlackDrops:CArtefact
---@class CBlackGraviArtefact:CArtefact
---@class CBastArtefact:CArtefact
---@class CDummyArtefact:CArtefact
---@class CZudaArtefact:CArtefact
---@class CThornArtefact:CArtefact
---@class CFadedBall:CArtefact
---@class CElectricBall:CArtefact
---@class CRustyHairArtefact:CArtefact
---@class CGalantineArtefact:CArtefact
---@class CGraviArtefact:CArtefact

-- Exported in src\xrGame\BottleItem_script.cpp

---@class CBottleItem:game_object
CBottleItem = {}

function CBottleItem:BreakToPieces() end

-- Exported in src\xrGame\CustomOutfit_script.cpp

---@class CCustomOutfit
---@field m_fPowerLoss number
---@field m_additional_weight number
---@field m_additional_weight2 number
---@field m_fHealthRestoreSpeed number
---@field m_fRadiationRestoreSpeed number
---@field m_fSatietyRestoreSpeed number
---@field m_fPowerRestoreSpeed number
---@field m_fBleedingRestoreSpeed number
---@field bIsHelmetAvaliable boolean readonly
---@field bIsBackpackAvaliable boolean readonly
CCustomOutfit = {}

function CCustomOutfit:BonePassBullet() end
function CCustomOutfit:get_HitFracActor() end
function CCustomOutfit:get_artefact_count() end
function CCustomOutfit:GetDefHitTypeProtection() end
function CCustomOutfit:GetHitTypeProtection() end
function CCustomOutfit:GetBoneArmor() end

---@class CHelmet
---@field m_fPowerLoss number
---@field m_fHealthRestoreSpeed number
---@field m_fRadiationRestoreSpeed number
---@field m_fSatietyRestoreSpeed number
---@field m_fPowerRestoreSpeed number
---@field m_fBleedingRestoreSpeed number
CHelmet = {}

function CHelmet:CHelmet() end
function CHelmet:get_HitFracActor() end
function CHelmet:GetDefHitTypeProtection() end
function CHelmet:GetHitTypeProtection() end
function CHelmet:GetBoneArmor() end

-- Exported in src\xrGame\CustomZone_script.cpp

---@class CCustomZone:game_object

-- Exported in src\xrGame\eatable_item_script.cpp

---@class CEatableItem
---@field m_bRemoveAfterUse boolean
---@field m_fWeightFull number
---@field m_fWeightEmpty number
CEatableItem = {}

function CEatableItem:Empty() end
function CEatableItem:CanDelete() end
function CEatableItem:GetMaxUses() end
function CEatableItem:GetRemainingUses() end
function CEatableItem:SetRemainingUses() end
function CEatableItem:Weight() end
function CEatableItem:Cost() end

-- Exported in src\xrGame\F1.cpp

---@class CF1:game_object

---@class CExplosiveItem:game_object

-- Exported in src\xrGame\FoodItem_script.cpp

---@class CFoodItem:game_object

-- Exported in src\xrGame\HairsZone_script.cpp

---@class CHairsZone:game_object

---@class CAmebaZone:game_object

---@class CNoGravityZone:game_object

-- Exported in src\xrGame\HangingLamp.cpp

---@class hanging_lamp
hanging_lamp = {}

function hanging_lamp:turn_on() end
function hanging_lamp:turn_off() end
function hanging_lamp:set_color_animator() end
function hanging_lamp:reset_color_animator() end
function hanging_lamp:is_on() end
function hanging_lamp:is_flickering() end

-- Exported in src\xrGame\helicopter_script.cpp

---@class CHelicopter:game_object
---@field m_use_rocket_on_attack boolean
---@field m_use_mgun_on_attack boolean
---@field m_min_rocket_dist number
---@field m_max_rocket_dist number
---@field m_min_mgun_dist number
---@field m_max_mgun_dist number
---@field m_time_between_rocket_attack number
---@field m_syncronize_rocket boolean
---@field m_flame_started boolean readonly
---@field m_light_started boolean readonly
---@field m_exploded boolean readonly
---@field m_dead boolean readonly
CHelicopter = {}

---@enum CHelicopter.state
CHelicopter.state = {
    eAlive = 0,
    eDead = 1
} -- TODO: Check values

---@enum CHelicopter.movement_state
CHelicopter.movement_state = {
    eMovNone = 0,
    eMovToPoint = 1,
    eMovPatrolPath = 2,
    eMovRoundPath = 3,
    eMovLanding = 4,
    eMovTakeOff = 5
} -- TODO: Check values

---@enum CHelicopter.hunt_state
CHelicopter.hunt_state = {
    eEnemyNone = 0,
    eEnemyPoint = 1,
    eEnemyEntity = 2
}  -- TODO: Check values

---@enum CHelicopter.body_state
CHelicopter.body_state = {
    eBodyByPath = 0,
    eBodyToPoint = 1
} -- TODO: Check values

function CHelicopter:GetState() end
function CHelicopter:GetMovementState() end
function CHelicopter:GetHuntState() end
function CHelicopter:GetBodyState() end
function CHelicopter:GetCurrVelocity() end
function CHelicopter:GetMaxVelocity() end
function CHelicopter:SetMaxVelocity() end
function CHelicopter:GetCurrVelocityVec() end
function CHelicopter:GetfHealth() end
function CHelicopter:SetfHealth() end
function CHelicopter:SetSpeedInDestPoint() end
function CHelicopter:GetSpeedInDestPoint() end
function CHelicopter:SetLinearAcc() end
function CHelicopter:SetOnPointRangeDist() end
function CHelicopter:GetOnPointRangeDist() end
function CHelicopter:GetDistanceToDestPosition() end
function CHelicopter:ClearEnemy() end
function CHelicopter:SetEnemy() end
function CHelicopter:SetEnemy() end
function CHelicopter:GoPatrolByPatrolPath() end
function CHelicopter:GoPatrolByRoundPath() end
function CHelicopter:SetDestPosition() end
function CHelicopter:LookAtPoint() end
function CHelicopter:SetFireTrailLength() end
function CHelicopter:SetBarrelDirTolerance() end
function CHelicopter:UseFireTrail() end
function CHelicopter:UseFireTrail() end
function CHelicopter:Die() end
function CHelicopter:StartFlame() end
function CHelicopter:Explode() end
function CHelicopter:isVisible() end
function CHelicopter:GetRealAltitude() end
function CHelicopter:GetSafeAltitude() end
function CHelicopter:TurnLighting() end
function CHelicopter:TurnEngineSound() end

-- Exported in src\xrGame\InventoryBox_script.cpp

---@class CInventoryBox:game_object
CInventoryBox = {}

function CInventoryBox:can_take() end
function CInventoryBox:set_can_take() end
function CInventoryBox:set_closed() end

-- Exported in src\xrGame\medkit_script.cpp

---@class CMedkit:game_object

-- Exported in src\xrGame\mincer_script.cpp

---@class CMincer:game_object

---@class CRadioactiveZone:game_object

-- Exported in src\xrGame\Missile.cpp

---@class CMissile:game_object
CMissile = {}

---@enum CMissile.EMissileStates
CMissile.EMissileStates = {
    eThrowStart = 0,
    eReady = 1,
    eThrow = 2,
    eThrowEnd = 3,
} -- TODO: check values

function CMissile:GetMinForce() end
function CMissile:GetMaxForce() end
function CMissile:GetThrowForce() end
function CMissile:GetConstForce() end
function CMissile:IsConstPower() end
function CMissile:GetThrowPoint() end
function CMissile:GetThrowDir() end

-- Exported in src\xrGame\MosquitoBald_script.cpp

---@class CTorridZone:game_object

---@class CMosquitoBald:game_object

---@class CZoneCampfire:game_object
CZoneCampfire = {}

function CZoneCampfire:turn_on() end
function CZoneCampfire:turn_off() end
function CZoneCampfire:is_on() end

-- Exported in src\xrGame\PhysicObject_script.cpp

---@class CDestroyablePhysicsObject:game_object

---@class CPhysicObject:game_object
CPhysicObject = {}

function CPhysicObject:run_anim_forward() end
function CPhysicObject:run_anim_back() end
function CPhysicObject:stop_anim() end
function CPhysicObject:anim_time_get() end
function CPhysicObject:anim_time_set() end
function CPhysicObject:play_bones_sound() end
function CPhysicObject:stop_bones_sound() end
function CPhysicObject:set_door_ignore_dynamics() end
function CPhysicObject:unset_door_ignore_dynamics() end

-- Exported in src\xrGame\RGD5.cpp

---@class CRGD5:game_object

-- Exported in src\xrGame\Scope.cpp

---@class CScope:game_object

---@class CSilencer:game_object

---@class CGrenadeLauncher:game_object

-- Exported in src\xrGame\StalkerOutfit.cpp

---@class CStalkerOutfit:game_object

-- Exported in src\xrGame\torch_script.cpp

---@class CTorch:game_object

---@class CPda:game_object

---@class CScientificDetector:game_object

---@class CEliteDetector:game_object

---@class CAdvancedDetector:game_object

---@class CSimpleDetector:game_object
