---@meta

-- Exported in src/xrServerEntities/xrServer_Objects_script.cpp

---@class ipure_alife_load_object
ipure_alife_load_object = {}

---@class ipure_alife_save_object
ipure_alife_save_object = {}

---@class ipure_alife_load_save_object
ipure_alife_load_save_object = {}

---@class ipure_server_object
ipure_server_object = {}

---@class cpure_server_object
cpure_server_object = {}

---@class cse_abstract
---@field id number readonly
---@field parent_id number readonly
---@field script_version number readonly
---@field position vector
---@field angle vector
cse_abstract = {}

function cse_abstract:section_name() end
function cse_abstract:name() end
function cse_abstract:clsid() end
function cse_abstract:spawn_ini() end
function cse_abstract:STATE_Read() end
function cse_abstract:STATE_Write() end
function cse_abstract:UPDATE_Read() end
function cse_abstract:UPDATE_Write() end

---@class cse_shape
cse_shape = {}

---@class cse_visual
cse_visual = {}

---@class cse_motion
cse_motion = {}

---@class cse_spectator
cse_spectator = {}

---@class cse_temporary
cse_temporary = {}

-- Exported in src/xrServerEntities/xrServer_Objects_script2.cpp

---@class cse_ph_skeleton
cse_ph_skeleton = {}

---@class CSE_AbstractVisual
CSE_AbstractVisual = {}

function CSE_AbstractVisual:getStartupAnimation() end
