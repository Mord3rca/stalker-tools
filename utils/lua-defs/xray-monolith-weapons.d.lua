---@meta

-- Exported in src\xrGame\WeaponAK74.cpp

---@class CWeaponAK74:CGameObject
CWeaponAK74 = {}

---@class CWeapon:CGameObject
CWeapon = {}

---@return boolean
function CWeapon:can_kill() end

---@return boolean
function CWeapon:IsGrenadeLauncherAttached() end

---@return boolean
function CWeapon:GrenadeLauncherAttachable() end

---@return string
function CWeapon:GetGrenadeLauncherName() end

---@return boolean
function CWeapon:IsScopeAttached() end

---@return boolean
function CWeapon:ScopeAttachable() end

---@return string
function CWeapon:GetScopeName() end

---@return boolean
function CWeapon:IsSilencerAttached() end

---@return boolean
function CWeapon:SilencerAttachable() end

---@return string
function CWeapon:GetSilencerName() end

---@return boolean
function CWeapon:IsZoomEnabled() end

---@return boolean
function CWeapon:IsZoomed() end

---@return number
function CWeapon:GetZoomFactor() end

---@param f number
function CWeapon:SetZoomFactor(f) end

---@return boolean
function CWeapon:IsSingleHanded() end

---@param cartridge_k number
---@return number
function CWeapon:GetBaseDispersion(cartridge_k) end

---@return number
function CWeapon:GetFireDispersion() end

---@return number
function CWeapon:GetMisfireStartCondition() end

---@return number
function CWeapon:GetMisfireEndCondition() end

---@return number
function CWeapon:GetAmmoElapsed() end

---@return number
function CWeapon:GetAmmoMagSize() end

---@param use_item_to_spawn? boolean
---@return number
function CWeapon:GetSuitableAmmoTotal(use_item_to_spawn) end

---@param ammo_count number
function CWeapon:SetAmmoElapsed(ammo_count) end

---@param flags number
---@return boolean
function CWeapon:SwitchAmmoType(flags) end

---@return number
function CWeapon:GetMagazineWeight() end

---@param type string
---@return number
function CWeapon:GetAmmoCount_forType(type) end

---@param type number
function CWeapon:set_ef_main_weapon_type(type) end

---@param type number
function CWeapon:set_ef_weapon_type(type) end

---@param type number
function CWeapon:SetAmmoType(type) end

---@return number
function CWeapon:GetAmmoType() end

---@param funct fun(i: number, type: string): boolean
function CWeapon:AmmoTypeForEach(funct) end

---@return number
function CWeapon:RPM() end

---@return number
function CWeapon:RealRPM() end

---@return number
function CWeapon:ModeRPM() end

---@return number
function CWeapon:ModeRealRPM() end

---@return number
function CWeapon:GetZoomType() end

---@return number
function CWeapon:Get_PDM_Base() end

---@return number
function CWeapon:Get_Silencer_PDM_Base() end

---@return number
function CWeapon:Get_Scope_PDM_Base() end

---@return number
function CWeapon:Get_Launcher_PDM_Base() end

---@return number
function CWeapon:Get_PDM_BuckShot() end

---@return number
function CWeapon:Get_PDM_Vel_F() end

---@return number
function CWeapon:Get_Silencer_PDM_Vel() end

---@return number
function CWeapon:Get_Scope_PDM_Vel() end

---@return number
function CWeapon:Get_Launcher_PDM_Vel() end

---@return number
function CWeapon:Get_PDM_Accel_F() end

---@return number
function CWeapon:Get_Silencer_PDM_Accel() end

---@return number
function CWeapon:Get_Scope_PDM_Accel() end

---@return number
function CWeapon:Get_Launcher_PDM_Accel() end

---@return number
function CWeapon:Get_PDM_Crouch() end

---@return number
function CWeapon:Get_PDM_Crouch_NA() end

---@return number
function CWeapon:GetCrosshairInertion() end

---@return number
function CWeapon:Get_Silencer_CrosshairInertion() end

---@return number
function CWeapon:Get_Scope_CrosshairInertion() end

---@return number
function CWeapon:Get_Launcher_CrosshairInertion() end

---@return number
function CWeapon:GetFirstBulletDisp() end

---@return number
function CWeapon:GetHitPower() end

---@return number
function CWeapon:GetHitPowerCritical() end

---@return number
function CWeapon:GetHitImpulse() end

---@return number
function CWeapon:GetFireDistance() end

---@return number
function CWeapon:GetFireMode() end

---@return number
function CWeapon:GetInertionAimFactor() end

---@param val number
function CWeapon:SetFireDispersion(val) end

---@param val number
function CWeapon:SetMisfireStartCondition(val) end

---@param val number
function CWeapon:SetMisfireEndCondition(val) end

---@param newOneShotTime number
function CWeapon:SetRPM(newOneShotTime) end

---@param rpm number
function CWeapon:SetRealRPM(rpm) end

---@param newOneShotTime number
function CWeapon:SetModeRPM(newOneShotTime) end

---@param rpm number
function CWeapon:SetModeRealRPM(rpm) end

---@param val number
function CWeapon:Set_PDM_Base(val) end

---@param val number
function CWeapon:Set_Silencer_PDM_Base(val) end

---@param val number
function CWeapon:Set_Scope_PDM_Base(val) end

---@param val number
function CWeapon:Set_Launcher_PDM_Base(val) end

---@param val number
function CWeapon:Set_PDM_BuckShot(val) end

---@param val number
function CWeapon:Set_PDM_Vel_F(val) end

---@param val number
function CWeapon:Set_Silencer_PDM_Vel(val) end

---@param val number
function CWeapon:Set_Scope_PDM_Vel(val) end

---@param val number
function CWeapon:Set_Launcher_PDM_Vel(val) end

---@param val number
function CWeapon:Set_PDM_Accel_F(val) end

---@param val number
function CWeapon:Set_Silencer_PDM_Accel(val) end

---@param val number
function CWeapon:Set_Scope_PDM_Accel(val) end

---@param val number
function CWeapon:Set_Launcher_PDM_Accel(val) end

---@param val number
function CWeapon:Set_PDM_Crouch(val) end

---@param val number
function CWeapon:Set_PDM_Crouch_NA(val) end

---@param val number
function CWeapon:SetCrosshairInertion(val) end

---@param val number
function CWeapon:Set_Silencer_CrosshairInertion(val) end

---@param val number
function CWeapon:Set_Scope_CrosshairInertion(val) end

---@param val number
function CWeapon:Set_Launcher_CrosshairInertion(val) end

---@param val number
function CWeapon:SetFirstBulletDisp(val) end

---@param val number
function CWeapon:SetHitPower(val) end

---@param val number
function CWeapon:SetHitPowerCritical(val) end

---@param val number
function CWeapon:SetHitImpulse(val) end

---@param val number
function CWeapon:SetFireDistance(val) end

---@return number
function CWeapon:GetZoomRotateTime() end

---@param val number
function CWeapon:SetZoomRotateTime(val) end

---@param position vector
---@param orientation vector
function CWeapon:Set_mOffset(position, orientation) end

---@param position vector
---@param orientation vector
function CWeapon:Set_mStrapOffset(position, orientation) end

---@param fire_point vector
function CWeapon:Set_mFirePoint(fire_point) end

---@param fire_point vector
function CWeapon:Set_mFirePoint2(fire_point) end

---@param fire_point vector
function CWeapon:Set_mShellPoint(fire_point) end

---@return matrix
function CWeapon:Get_mOffset() end

---@return matrix
function CWeapon:Get_mStrapOffset() end

---@return string
function CWeapon:Get_strap_bone0() end

---@return string
function CWeapon:Get_strap_bone1() end

---@return boolean
function CWeapon:Get_strapped_mode() end

---@return number -- See src\xrGame\inventory_item.h:21 (EHandDependence) for more info
function CWeapon:HandDependence() end

---@return number
function CWeapon:GetCamRelaxSpeed() end

---@return number
function CWeapon:GetCamRelaxSpeed_AI() end

---@return number
function CWeapon:GetCamDispersion() end

---@return number
function CWeapon:GetCamDispersionInc() end

---@return number
function CWeapon:GetCamDispersionFrac() end

---@return number
function CWeapon:GetCamMaxAngleVert() end

---@return number
function CWeapon:GetCamMaxAngleHorz() end

---@return number
function CWeapon:GetCamStepAngleHorz() end

---@return number
function CWeapon:GetZoomCamRelaxSpeed() end

---@return number
function CWeapon:GetZoomCamRelaxSpeed_AI() end

---@return number
function CWeapon:GetZoomCamDispersion() end

---@return number
function CWeapon:GetZoomCamDispersionInc() end

---@return number
function CWeapon:GetZoomCamDispersionFrac() end

---@return number
function CWeapon:GetZoomCamMaxAngleVert() end

---@return number
function CWeapon:GetZoomCamMaxAngleHorz() end

---@return number
function CWeapon:GetZoomCamStepAngleHorz() end

---@param val number
function CWeapon:SetCamRelaxSpeed(val) end

---@param val number
function CWeapon:SetCamRelaxSpeed_AI(val) end

---@param val number
function CWeapon:SetCamDispersion(val) end

---@param val number
function CWeapon:SetCamDispersionInc(val) end

---@param val number
function CWeapon:SetCamDispersionFrac(val) end

---@param val number
function CWeapon:SetCamMaxAngleVert(val) end

---@param val number
function CWeapon:SetCamMaxAngleHorz(val) end

---@param val number
function CWeapon:SetCamStepAngleHorz(val) end

---@param val number
function CWeapon:SetZoomCamRelaxSpeed(val) end

---@param val number
function CWeapon:SetZoomCamRelaxSpeed_AI(val) end

---@param val number
function CWeapon:SetZoomCamDispersion(val) end

---@param val number
function CWeapon:SetZoomCamDispersionInc(val) end

---@param val number
function CWeapon:SetZoomCamDispersionFrac(val) end

---@param val number
function CWeapon:SetZoomCamMaxAngleVert(val) end

---@param val number
function CWeapon:SetZoomCamMaxAngleHorz(val) end

---@param val number
function CWeapon:SetZoomCamStepAngleHorz(val) end

---@return number
function CWeapon:Cost() end

---@return number
function CWeapon:Weight() end

---@return boolean
function CWeapon:IsMisfire() end

---@param b boolean
function CWeapon:SetMisfire(b) end

---@return boolean
function CWeapon:IsPending() end

---@param H boolean
function CWeapon:SetPending(H) end

---@enum CWeapon.EWeaponStates
CWeapon.EWeaponStates = {
    eFire = 5,
    eFire2 = 6,
    eReload = 7,
    eMisfire = 8,
    eSwitch = 9,
    eSwitchMode = 10
}

---@enum CWeapon.EWeaponSubStates
CWeapon.EWeaponSubStates = {
    eSubstateReloadBegin = 0,
    eSubstateReloadInProcess = 1,
    eSubstateReloadEnd = 2
}

---@class CWeaponMagazined:CGameObject
CWeaponMagazined = {}

function CWeaponMagazined:SetFireMode() end

---@class CWeaponMagazinedWGrenade:CGameObject
CWeaponMagazinedWGrenade = {}

function CWeaponMagazinedWGrenade:GetGrenadeLauncherMode() end
function CWeaponMagazinedWGrenade:SetGrenadeLauncherMode() end
function CWeaponMagazinedWGrenade:SetAmmoElapsed2() end
function CWeaponMagazinedWGrenade:GetAmmoElapsed2() end
function CWeaponMagazinedWGrenade:GetAmmoMagSize2() end
function CWeaponMagazinedWGrenade:SetAmmoType2() end
function CWeaponMagazinedWGrenade:GetAmmoType2() end
function CWeaponMagazinedWGrenade:AmmoTypeForEach2() end

-- Exported in src\xrGame\WeaponAmmo_script.cpp

---@class CWeaponAmmo:CGameObject
---@field m_boxSize number
---@field m_boxCurr number
---@field m_tracer boolean
---@field m_4to1_tracer boolean
CWeaponAmmo = {}

---@return number
function CWeaponAmmo:Weight() end

---@return number
function CWeaponAmmo:Cost() end

-- Exported in src\xrGame\WeaponBinoculars_script.cpp

---@class CWeaponBinoculars:CGameObject
CWeaponBinoculars = {}

-- Exported in src\xrGame\weaponBM16_script.cpp

---@class CWeaponBM16:CGameObject
CWeaponBM16 = {}

-- Exported in src\xrGame\WeaponFN2000.cpp

---@class CWeaponFN2000:CGameObject
CWeaponFN2000 = {}

-- Exported in src\xrGame\WeaponFORT.cpp

---@class CWeaponFORT:CGameObject
CWeaponFORT = {}

-- Exported in src\xrGame\WeaponGroza.cpp

---@class CWeaponGroza:CGameObject
CWeaponGroza = {}

-- Exported in src\xrGame\WeaponHPSA_script.cpp

---@class CWeaponHPSA:CGameObject
CWeaponHPSA = {}

-- Exported in src\xrGame\WeaponKnife_script.cpp

---@class CWeaponKnife:CGameObject
CWeaponKnife = {}

---@return number
function CWeaponKnife:GetHit1Power() end

---@return number
function CWeaponKnife:GetHit2Power() end

---@return number
function CWeaponKnife:GetHit1PowerCritical() end

---@return number
function CWeaponKnife:GetHit2PowerCritical() end

---@return number
function CWeaponKnife:GetHit1Impulse() end

---@return number
function CWeaponKnife:GetHit2Impulse() end

---@param power number
function CWeaponKnife:SetHit1Power(power) end

---@param power number
function CWeaponKnife:SetHit2Power(power) end

---@param power number
function CWeaponKnife:SetHit1PowerCritical(power) end

---@param power number
function CWeaponKnife:SetHit2PowerCritical(power) end

---@param impulse number
function CWeaponKnife:SetHit1Impulse(impulse) end

---@param impulse number
function CWeaponKnife:SetHit2Impulse(impulse) end

-- Exported in src\xrGame\WeaponLR300.cpp

---@class CWeaponLR300:CGameObject
CWeaponLR300 = {}

-- Exported in src\xrGame\WeaponPM.cpp

---@class CWeaponPM:CGameObject
CWeaponPM = {}

-- Exported in src\xrGame\WeaponRG6_script.cpp

---@class CWeaponRG6:CGameObject
CWeaponRG6 = {}

-- Exported in src\xrGame\WeaponRPG7_script.cpp

---@class CWeaponRPG7:CGameObject
CWeaponRPG7 = {}

-- Exported in src\xrGame\weaponshotgun_script.cpp

---@class CWeaponShotgun:CGameObject
CWeaponShotgun = {}

---@class CWeaponAutomaticShotgun:CGameObject
CWeaponAutomaticShotgun = {}

-- Exported in src\xrGame\WeaponSSRS_script.cpp

---@class CWeaponSSRS:CGameObject
CWeaponSSRS = {}

-- Exported in src\xrGame\WeaponStatMgunIR.cpp

---@class CWeaponStatMgun:CGameObject
CWeaponStatMgun = {}

---@enum CWeaponStatMgun.stm_wpn
CWeaponStatMgun.stm_wpn = {
    eWpnActivate = 0,
    eWpnFire = 1,
    eWpnDesiredPos = 2,
    eWpnDesiredDir = 3,
    eWpnDesiredAng = 4,
    eWpnReload = 5
}

---@param id number
---@param flags number
function CWeaponStatMgun:Action(id, flags) end

---@param id number
---@param val vector2
function CWeaponStatMgun:SetParam(id, val) end

---@return boolean
function CWeaponStatMgun:IsWorking() end

---@enum CWeaponStatMgun.stm_state
CWeaponStatMgun.stm_state = {
    eStateIdle = 0,
    eStateFire = 1,
    eStateReload = 2
}

---@return number
function CWeaponStatMgun:GetState() end

---@return number
function CWeaponStatMgun:GetStateDelay() end

---@return number
function CWeaponStatMgun:GetReloadDelay() end

---@return game_object
function CWeaponStatMgun:GetOwner() end

---@return vector
function CWeaponStatMgun:GetFirePos() end

---@return vector
function CWeaponStatMgun:GetFireDir() end

---@return vector
function CWeaponStatMgun:ExitPosition() end

---@return vector2
function CWeaponStatMgun:GetTraverseLimitHorz() end

---@param vec vector2
function CWeaponStatMgun:SetTraverseLimitHorz(vec) end

---@return vector2
function CWeaponStatMgun:GetTraverseLimitVert() end

---@param vec vector2
function CWeaponStatMgun:SetTraverseLimitVert(vec) end

---@return vector
function CWeaponStatMgun:GetActorOffsets() end

---@param vec vector
function CWeaponStatMgun:SetActorOffsets(vec) end

---@param cartridge_k number
---@return number
function CWeaponStatMgun:GetBaseDispersion(cartridge_k) end

---@param with_cartridge boolean
---@param for_crosshair? boolean
---@return number
function CWeaponStatMgun:GetFireDispersion(with_cartridge, for_crosshair) end

---@enum CWeaponStatMgun.stm_animation
CWeaponStatMgun.stm_animation = {
    eAnimBody = 0,
    eAnimLegs = 1
}

---@param id number
---@return string
function CWeaponStatMgun:GetAnimation(id) end

---@param id number
---@param anim string
function CWeaponStatMgun:SetAnimation(id, anim) end

---@return number
function CWeaponStatMgun:GetAmmoMagSize() end

---@return number
function CWeaponStatMgun:GetAmmoElapsed() end

---@param ammo_count number
function CWeaponStatMgun:SetAmmoElapsed(ammo_count) end

---@return number
function CWeaponStatMgun:GetAmmoType() end

---@param type number
function CWeaponStatMgun:SetAmmoType(type) end

---@param ammo_type? number
function CWeaponStatMgun:SetNextAmmoTypeOnReload(ammo_type) end

-- Exported in src\xrGame\WeaponSVD.cpp

---@class CWeaponSVD:CGameObject
CWeaponSVDC = {}

-- Exported in src\xrGame\WeaponSVU.cpp

---@class CWeaponSVU:CGameObject
CWeaponSVU = {}

-- Exported in src\xrGame\WeaponUSP45.cpp

---@class CWeaponUSP45:CGameObject
CWeaponUSP45 = {}

-- Exported in src\xrGame\WeaponVal.cpp

---@class CWeaponVal:CGameObject
CWeaponVal = {}

-- Exported in src\xrGame\WeaponVintorez.cpp

---@class CWeaponVintorez:CGameObject
CWeaponVintorez = {}

-- Exported in src\xrGame\WeaponWalther.cpp

---@class CWeaponWalther:CGameObject
CWeaponWalther = {}
