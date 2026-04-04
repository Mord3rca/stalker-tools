---@meta

-- Definition from src\xrServerEntities\script_net_packet_script.cpp

---@return number
function script_server_object_version() end

---@class ClientID
ClientID = {}

---@return number
function ClientID:value() end

---@param v number
function ClientID:set(v) end

---@class net_packet
net_packet = {}

function net_packet:w_begin(type) end

---@return number
function net_packet:w_tell() end

function net_packet:w_vec3(a) end

function net_packet:w_float(a) end

function net_packet:w_u64(a) end

function net_packet:w_s64(a) end

function net_packet:w_u32(a) end

function net_packet:w_s32(a) end

function net_packet:w_u16(a) end

function net_packet:w_s16(a) end

function net_packet:w_u8(a) end

function net_packet:w_bool(a) end

function net_packet:w_float_q16(a) end

function net_packet:w_float_q8(a) end

function net_packet:w_angle16(a) end

function net_packet:w_angle8(a) end

function net_packet:w_dir(d) end

function net_packet:w_sdir(d) end

function net_packet:w_stringZ(s) end

function net_packet:w_matrix(m) end

function net_packet:w_clientID(c) end

function net_packet:w_chunk_open8(position) end

function net_packet:w_chunk_close8(position) end

function net_packet:w_chunk_open16(position) end

function net_packet:w_chunk_close16(position) end

function net_packet:r_begin(type) end

function net_packet:r_seek(pos) end

function net_packet:r_tell() end

function net_packet:r_vec3() end

function net_packet:r_float() end

function net_packet:r_u64() end

function net_packet:r_s64() end

function net_packet:r_u32() end

function net_packet:r_s32() end

function net_packet:r_u16() end

function net_packet:r_s16() end

function net_packet:r_u8() end

function net_packet:r_s8() end

function net_packet:r_bool() end

function net_packet:r_float() end

function net_packet:r_u64() end

function net_packet:r_s64() end

function net_packet:r_u32() end

function net_packet:r_s32() end

function net_packet:r_u16() end

function net_packet:r_s16() end

function net_packet:r_u8() end

function net_packet:r_s8() end

function net_packet:r_float_q16(min, max) end

function net_packet:r_float_q8(min, max) end

function net_packet:r_angle16() end

function net_packet:r_angle8() end

function net_packet:r_dir() end

function net_packet:r_sdir() end

function net_packet:r_stringZ() end

function net_packet:r_matrix() end

function net_packet:r_clientID() end

function net_packet:r_elapsed() end

function net_packet:r_advance() end

function net_packet:r_eof() end

