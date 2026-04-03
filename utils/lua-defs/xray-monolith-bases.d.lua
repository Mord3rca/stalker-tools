---@meta

-- Exported object by src\xrGame\base_client_classes_script.cpp

---@class DLL_Pure
DLL_Pure = {}

function DLL_Pure:_construct() end

---@class ISheduled
ISheduled = {}

---@class IRenderable
IRenderable = {}

---@class ICollidable
ICollidable = {}

---@class CGameObject: DLL_Pure, ISheduled, ICollidable, IRenderable
CGameObject = {}

function CGameObject:_construct() end

---@return IRender_Visual
function CGameObject:Visual() end

function CGameObject:net_Export(packet) end

function CGameObject:net_Import(packet) end

function CGameObject:net_Spawn(abstract) end

---@param who_use CGameObject
---@return boolean
function CGameObject:use(who_use) end

---@return boolean
function CGameObject:getVisible() end

---@return boolean
function CGameObject:getEnabled() end

---@class IRender_Visual
IRender_Visual = {}

function IRender_Visual:dcast_PKinematicsAnimated() end

---@class IKinematicsAnimated
IKinematicsAnimated = {}

---@param anim string
function IKinematicsAnimated:PlayCycle(anim) end

---@class CBlend
CBlend = {}
