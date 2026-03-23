---@meta

-- ini_file class interface defined in src/xrServerEntities/script_ini_file_script.cpp
-- which is a LUA export from object CInifile defined in src/xrCore/xr_ini.h

---@class ini_file
ini_file = {}

---Object constructor
---@param path string
---@return ini_file
function ini_file:constructor(path) end

---Write a boolean in section.key
---@param section string
---@param key string
---@param value boolean
---@param comment? string
function ini_file:w_bool(section, key, value, comment) end

---Write a color type in section.key
---@param section string
---@param key string
---@param value number u32
---@param comment? string
function ini_file:w_color(section, key, value, comment) end

---Write a float in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file:w_float(section, key, value, comment) end

---Write a fcolor type in section.key
---@param section string
---@param key string
---@param value fcolor
---@param comment? string
function ini_file:w_fcolor(section, key, value, comment) end

---Write a fvector2 type in section.key
---@param section string
---@param key string
---@param value vector2
---@param comment? string
function ini_file:w_fvector2(section, key, value, comment) end

---Write a vector3 type in section.key
---@param section string
---@param key string
---@param value vector
---@param comment? string
function ini_file:w_fvector3(section, key, value, comment) end

---Write a fvector4 type in section.key
---@param section string
---@param key string
---@param value vector4
---@param comment? string
function ini_file:w_fvector4(section, key, value, comment) end

---Write a s16 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file:w_s16(section, key, value, comment) end

---Write a s32 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file:w_s32(section, key, value, comment) end

---Write a s64 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file:w_s64(section, key, value, comment) end

---Write a s8 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file:w_s8(section, key, value, comment) end

---Write a string type in section.key
---@param section string
---@param key string
---@param value string
---@param comment? string
function ini_file:w_string(section, key, value, comment) end

---Write a u16 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file:w_u16(section, key, value, comment) end

---Write a u32 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file:w_u32(section, key, value, comment) end

---Write a u64 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file:w_u64(section, key, value, comment) end

---Write a u8 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file:w_u8(section, key, value, comment) end

---Save ini file
---@param path string
function ini_file:save_as(path) end

---Save file on class destruction
---@param value boolean
function ini_file:save_at_end(value) end

---Remove a section.key
---@param section string
---@param key string
function ini_file:remove_line(section, key) end

---Disable key override if set to true
---@param value boolean
function ini_file:set_override_names(value) end

---Get the number of section in the INI File
---@return number
function ini_file:section_count() end

---Section iterator (ran until the end or if callback return true)
---@param callback fun(section: string): boolean
function ini_file:section_for_each(callback) end

---Set read only
---@param state boolean
function ini_file:set_readonly(state) end

---Check if section exist
---@param section string
---@return boolean
function ini_file:section_exist(section) end

---Check if section.key exists
---@param section string
---@param key string
---@return boolean
function ini_file:line_exist(section, key) end

---Read section.key as clsid
---@param section string
---@param key string
function ini_file:r_clsid(section, key) end
-- TODO: Add return type once CLSID type is defined (see src/xrCore/clsid.h)

---Read section.key as boolean
---@param section string
---@param key string
---@return boolean
function ini_file:r_bool(section, key) end

---Read section.key and return the ID matching the pair {name, id} defined in token_list or 0
---@param section string
---@param key string
---@param token_list {name: string, id: number}[]
---@return number
function ini_file:r_token(section, key, token_list) end

---Read section.key as string without the ""
---@param section string
---@param key string
---@return string
function ini_file:r_string_wq(section, key) end

---Get the number of keys in the section
---@param section string
---@return number
function ini_file:line_count(section) end

---Read section.key as string
---@param section string
---@param key string
---@return string
function ini_file:r_string(section, key) end

---Read section.key as unsigned number
---@param section string
---@param key string
---@return number
function ini_file:r_u32(section, key) end

---Read section.key as number
---@param section string
---@param key string
---@return number
function ini_file:r_s32(section, key) end

---Read section.key as number
---@param section string
---@param key string
---@return number
function ini_file:r_float(section, key) end

---Read section.key as vector
---@param section string
---@param key string
---@return vector
function ini_file:r_float(section, key) end

---Call xr_delete() on CInifile object to delete it (resulting on a possible use-after-free)
function ini_file.close() end

---Read line
---@param section string
---@param line number
---@param key string Variable passed by reference to store the key result
---@param value string Variable passed by reference to store the value result
function ini_file:r_line(section, line, key, value) end

---Get filename
---@return string
function ini_file:get_filename() end

---Print DLTX override info
---@param section string
---@param key string
function ini_file:dltx_print(section, key) end

---Get filename of section.key
---@param section string
---@param key string
---@return string
function ini_file:dltx_get_filename_of_line(section, key) end

---Return an table containing an object for each key ({name, value, filename, data})
---@param section string
---@return {name: string, value: string, filename: string, data:string}
function ini_file:dltx_get_section(section) end
-- TODO: Confirm return type

---Return true if file associated to section.key begin with "mod_"
---@param section string
---@param key string
---@return boolean
function ini_file:dltx_is_override(section, key) end

---Get internal handler of CScriptIniFile representing system.ltx
---@return ini_file
function system_ini() end

---Reload system ini class
---@return ini_file
function reload_system_ini() end

---Get internal handler of CScriptIniFile representing game.ltx
---@return ini_file
function game_ini() end

---Create a ini_class from path
---@return ini_file
function create_ini_file(path) end

---Get the version with the format YYYYMMDD
---@return number
function get_modded_exes_version() end

---Get the string "Modded Exes"
---@return string
function get_modded_exes_name() end

--Return an object which contain String Table of CStringTable::pData (Why it's in there !?)
--@return object
function get_string_table() end
--TODO Investigate this once StringTable are documented.
