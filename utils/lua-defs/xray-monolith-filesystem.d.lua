---@meta

-- Exported classes from src\xrGame\fs_registrator_script.cpp

---@class FS_item
FS_item = {}

---Return name
---@return string
function FS_item:NameFull() end

---Return name (same as NameFull())
---@return string
function FS_item:NameShort() end

---Return item size
---@return number
function FS_item:Size() end

---Return last modif time (format: DD/MM/YYYY HH:MM)
---@return string
function FS_item:ModifDigitOnly() end

---Return last modified time (asctime() format)
---@return string
function FS_item:Modif() end

---@class FS_file_list_ex
FS_file_list_ex = {}

---@return number
function FS_file_list_ex:Size() end

---Get FS_item at index
---@param idx number
---@return FS_item
function FS_file_list_ex:GetAt(idx) end

---Sort File List
---@param flags FS.FS_sort_mode
function FS_file_list_ex:Sort(flags) end

---@class FS_file_list
FS_file_list = {}

---@return number
function FS_file_list:Size() end

---Get path at idx
---@param idx number
---@return string
function FS_file_list:GetAt(idx) end

---Close file list
function FS_file_list:Free() end

--[[
--Commented in code src/xrGame/fs_registrator_script.cpp:219
---@class FS_Path
---@field m_Path string readonly
---@field m_Root string readonly
---@field m_Add string readonly
---@field m_DefExt string readonly
---@field m_FilterCaption string readonly
FS_Path = {}
]]--

---@class fs_file
---@field name string readonly
---@field vfs number readonly
---@field ptr number readonly
---@field size_real number readonly
---@field size_compressed number readonly
---@field compressed number readonly
fs_file = {}

---@class FS
FS = {}

---@enum FS.FS_sort_mode
FS.FS_sort_mode = {
    FS_sort_by_name_up = 0,
    FS_sort_by_name_down = 1,
    FS_sort_by_size_up = 2,
    FS_sort_by_size_down = 3,
    FS_sort_by_modif_up = 4,
    FS_sort_by_modif_down = 5
}

---@enum FS.FS_list
FS.FS_List = {
    FS_ListFiles = 0,
    FS_ListFolders = 1,
    FS_ClampExt = 2,
    FS_RootOnly = 3
}

---@param path string
---@return boolean
function FS:path_exist(path) end

---Concatenate initial & src (can use fsgame path type)
---@param initial string
---@param src string
---@return string
function FS:update_path(initial, src) end

---WARNING: Don't use, return a FS_path which is not exported
---@param path string
function FS:get_path(path) end

---WARNING: Don't use, return a FS_path which is not exported
---@param path_alias string
---@param root string
---@param add string
---@param recursive boolean
function FS:append_path(path_alias, root, add, recursive) end

---@param initial string
function FS:rescan_path(initial) end

function FS:rescan_pathes() end

---@param full_path string
function FS:file_delete(full_path) end

---@param path string
---@param nm string
function FS:file_delete(path, nm) end

---@param full_path string
---@param remove_files number
function FS:dir_delete(full_path, remove_files) end

---@param path string
---@param nm string
---@param remove_files number
function FS:dir_delete(path, nm, remove_files) end

---@param src string
---@param dest string
---@param overwrite? boolean true by default
function FS:file_rename(src, dest, overwrite) end

---@param src string
---@return number
function FS:file_length(src) end

---@param src string
---@param dest string
function FS:file_copy(src, dest) end

---@param N string
function FS:exist(N) end

---@param path string
---@param name string
function FS:exist(path, name) end

---@param nm string
---@return number
function FS:get_file_age(nm) end

---@param nm string
---@return string
function FS:get_file_age_str(nm) end

---@param initial string
---@param N string
function FS:r_open(initial, N) end
--TODO: Return IReader object

---@param N string
function FS:r_open(N) end
--TODO: Return IReader object

---@param S any
function FS:r_close(S) end
--TODO: IReader type for S

---@param initial string
---@param N string
function FS:w_open(initial, N) end
--TODO: Return IWriter object

---@param N string
function FS:w_open(N) end
--TODO: Return IWriter object

---@param S any
function FS:w_close(S) end
--TODO: IWriter type for S

---@param initial string
---@param flags number
---@return FS_file_list
function FS:file_list_open(initial, flags) end

---@param initial string
---@param folder string
---@param flags number
---@return FS_file_list
function FS:file_list_open(initial, folder, flags) end

---@param path string
---@param flags number
---@param mask string
---@return FS_file_list_ex
function FS:file_list_open_ex(path, flags, mask) end

---@return FS
function getFS() end
