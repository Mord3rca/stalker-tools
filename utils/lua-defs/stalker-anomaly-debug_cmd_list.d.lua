---@meta

--[[
Definition of debug_cmd_list.script defined in db\configs\script.db0:scripts\debug_cmd_list.script
]]--

---@class cmd
local cmd = {}

---@return cmd
function command_get_list() end

---@return number
function command_get_count() end

---@param name string
---@return boolean
function command_exists(name) end

---@param txt string
---@return string[]
function split(txt) end
-- Extra: Not a local function so technicaly speaking ... It's part of the API

function check_and_set_help(caller, txt, owner, msg) end

function get_position_offset(npc, o) end

function cmd.help(me, txt, owner, p) end

function cmd.excho(me, txt, owner, p) end

function cmd.char_desc(me, txt, owner, p) end

function cmd.print(me, txt, owner, p) end

function cmd.reload_system_ini(me, txt, owner, p) end

function cmd.relations(me, txt, owner, p) end

function cmd.lua_countall(me, txt, owner, p) end

function cmd.community(me, txt, owner, p) end

function cmd.spawn(me, txt, owner, p) end

function cmd.collectgarbage(me, txt, owner, p) end

function cmd.attach(me, txt, owner, p) end

function cmd.detach(me, txt, owner, p) end

function cmd.waypoint(me, txt, owner, p) end

function cmd.surge(me, txt, owner, p) end

function cmd.psi_storm(me, txt, owner, p) end

function cmd.fallout(me, txt, owner, p) end

function cmd.find(me, txt, owner, p) end

function cmd.execute(me, txt, owner, p) end

function cmd.alife(me, txt, owner, p) end

function cmd.clear(me, txt, owner, p) end

function cmd.squad(me, txt, owner, p) end

function cmd.console(me, txt, owner, p) end

function cmd.teleport(me, txt, owner, p) end

function cmd.wound(me, txt, owner, p) end

function cmd.var(me, txt, owner, p) end

function cmd.vector(me, txt, owner, p) end

function cmd.offset(me, txt, owner, p) end

function cmd.object(me, txt, owner, p) end

function match_or_var(txt, token, pat, var) end

function cmd.hud(me, txt, owner, p) end

function cmd.god(me, txt, owner, p) end

function cmd.invisible(me, txt, owner, p) end

function cmd.crow(me, txt, owner, p) end

function cmd.heli(me, txt, owner, p) end

function cmd.weather(me, txt, owner, p) end

function cmd.time(me, txt, owner, p) end

function cmd.money(me, txt, owner, p) end

-- WARN: Not working
function cmd.luabind(me, txt, owner, p) end

function cmd.level(me, txt, owner, p) end

function cmd.warpall(me, txt, owner, p) end

function cmd.dev_debug(me, txt, owner, p) end

function cmd.game_graph(me, txt, owner, p) end

function cmd.item(me, txt, owner, p) end

function cmd.info(me, txt, owner, p) end

function cmd.inventory_owner(me, txt, owner, p) end

function antifreeze_switch(id) end

function cmd.antifreeze(me, txt, owner, p) end

function cmd.pstor_test(me, txt, owner, p) end

function cmd.debug_visuals(me, txt, owner, p) end

function cmd.gulag(me, txt, owner, p) end

function cmd.alife_release(_, txt, x) end

function cmd.alife_print_npc(_, txt, x) end

function cmd.alife_print_squad(_, txt, x) end

function cmd.alife_report(_, txt, x) end

function cmd.get_nearest_object(_, txt, x) end

function cmd.get_npc_visual(_, __, x) end

function cmd.surge(_, txt, x) end

function cmd.psi_storm(_, txt, x) end

function cmd.ppe_effect(_, txt, x) end

function cmd.set_rank(_, txt, x) end

function cmd.set_rep(_, txt, x) end

function cmd.get_nearby_companion(_, txt, x) end

function cmd.map_marker(_, txt, x) end

function cmd.scan_item_configs(_, txt, x) end

function cmd.scan_unused_weapons(_, txt, x) end

function cmd.scan_unused_icons(_, txt, x) end

function cmd.scan_unused_level_logic(_, txt, x) end

function cmd.print_outfits_props(_, txt, x) end

function cmd.release_target() end

function cmd.release_id(_, txt, x) end

function cmd.calc_containers_weight(_, txt, x) end

function cmd.validate_wpn_upgrades(_, txt, x) end

function cmd.validate_outfit_upgrades(_, txt, x) end

function cmd.dump_system_ini() end

function cmd.dump_section(_, txt) end

function cmd.test_squad(_, txt, o) end

function cmd.toggle_all_talk(_, __, o) end
