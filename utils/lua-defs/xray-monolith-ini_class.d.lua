---@meta

-- ini_file class interface defined in src/xrServerEntities/script_ini_file_script.cpp
-- which is a LUA export from object CInifile defined in src/xrCore/xr_ini.h

---@class ini_file
ini_file = {}

---Object constructor
---@param path string
---@return ini_file
function ini_file.constructor(path) end

---Write a boolean in section.key
---@param section string
---@param key string
---@param value boolean
---@param comment? string
function ini_file.w_bool(section, key, value, comment) end

---Write a color type in section.key
---@param section string
---@param key string
---@param value color
---@param comment? string
function ini_file.w_color(section, key, value, comment) end
--TODO: Color object definition

---Write a float in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file.w_float(section, key, value, comment) end

---Write a fcolor type in section.key
---@param section string
---@param key string
---@param value vector
---@param comment? string
function ini_file.w_fcolor(section, key, value, comment) end
--TODO: vector object definition

---Write a fvector2 type in section.key
---@param section string
---@param key string
---@param value vector2
---@param comment? string
function ini_file.w_fvector2(section, key, value, comment) end
--TODO: vector2 object definition

---Write a vector3 type in section.key
---@param section string
---@param key string
---@param value vector
---@param comment? string
function ini_file.w_fvector3(section, key, value, comment) end

---Write a fvector4 type in section.key
---@param section string
---@param key string
---@param value vector4
---@param comment? string
function ini_file.w_fvector4(section, key, value, comment) end
--TODO: vector4 object definition

---Write a s16 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file.w_s16(section, key, value, comment) end

---Write a s32 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file.w_s32(section, key, value, comment) end

---Write a s64 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file.w_s64(section, key, value, comment) end

---Write a s8 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file.w_s8(section, key, value, comment) end

---Write a string type in section.key
---@param section string
---@param key string
---@param value string
---@param comment? string
function ini_file.w_string(section, key, value, comment) end

---Write a u16 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file.w_u16(section, key, value, comment) end

---Write a u32 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file.w_u32(section, key, value, comment) end

---Write a u64 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file.w_u64(section, key, value, comment) end

---Write a u8 type in section.key
---@param section string
---@param key string
---@param value number
---@param comment? string
function ini_file.w_u8(section, key, value, comment) end

---Save ini file
---@param path string
function ini_file.save_as(path) end

---Save file on class destruction
---@param value boolean
function ini_file.save_at_end(value) end

---Remove a section.key
---@param section string
---@param key string
function ini_file.remove_line(section, key) end

---Disable key override if set to true
---@param value boolean
function ini_file.set_override_names(value) end

---Get the number of section in the INI File
---@return number
function ini_file.section_count() end

---Section iterator (ran until the end or if callback return true)
---@param callback function(string) -> boolean
function ini_file.section_for_each(callback) end

---Set read only
---@param state boolean
function ini_file.set_readonly(state) end

---Check if section exist
---@param section string
---@return boolean
function ini_class.section_exist(section) end

---Check if section.key exists
---@param section string
---@param key string
---@return boolean
function ini_file.line_exist(section, key) end

--[[
                TODO: Add. following defs
                .def("r_clsid", &CScriptIniFile::r_clsid)
                .def("r_bool", &CScriptIniFile::r_bool)
                .def("r_token", &CScriptIniFile::r_token)
                .def("r_string_wq", &CScriptIniFile::r_string_wb)
                .def("line_count", &CScriptIniFile::line_count)
                .def("r_string", &CScriptIniFile::r_string)
                .def("r_u32", &CScriptIniFile::r_u32)
                .def("r_s32", &CScriptIniFile::r_s32)
                .def("r_float", &CScriptIniFile::r_float)
                .def("r_vector", &CScriptIniFile::r_fvector3)
]]--

---Call xr_delete() on CInifile object to delete it (resulting on a possible use-after-free)
function ini_file.close() end

---Read line
---@param section string
---@param line number
---@param key string Variable passed by reference to store the key result
---@param value string Variable passed by reference to store the value result
function ini_class.r_line(section, line, key, value) end

---Get filename
---@return string
function ini_class.get_filename() end

---Print DLTX override info
---@param section string
---@param key string
function ini_class.dltx_print(section, line) end

---Get filename of section.key
---@param section string
---@param key string
---@return string
function ini_class.dltx_get_filename_of_line(section, key) end

---Return an table containing an object for each key ({name, value, filename, data})
---@param section string
---@return object
function ini_class.dltx_get_section(section) end

---Return true if file associated to section.key begin with "mod_"
---@param section string
---@param key string
---@return boolean
function ini_class.dltx_is_override(section, key) end

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
