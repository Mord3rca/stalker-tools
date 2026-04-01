local log_name = "[DLTX Exporter] "

local function _adding_motion_length(section)
    local dltx_sec_table = system_ini():dltx_get_section(section)

    for _, v in pairs(dltx_sec_table) do
        if v["name"]:find("^anm_") ~= nil then
            system_ini():w_float(
                section, v["name"] .. "_mlength",
                game.get_motion_length(section, v["name"], 1)
            )
        end
    end

    return false  -- Continue iteration
end

local function export_system_config(_, __, cout)
        cout:SendOutput(log_name .. "Exporting configuration")
        system_ini():save_as(getFS():update_path("$logs$", string.format("outfile-%d.ini", os.time(os.date("!*t")))))
        cout:SendOutput(log_name .. "Export finished")
end

local function export_system_config_extended(_, __, cout)
        cout:SendOutput(log_name .. "Adding add. info in system configuration")
        system_ini():set_readonly(false)
        system_ini():section_for_each(_adding_motion_length)
        system_ini():set_readonly(true)

        -- Use previous func to dump system config
        export_system_config(_, __, cout)
end

local function on_game_load()
    local cmd = debug_cmd_list.command_get_list()

    -- Register dumping functions in DBG mode menu
    cmd.export_system_config = export_system_config
    ui_debug_launcher.inject("action", {name = "Export System Config", cmd = "export_system_config", hide_ui = 0})

    cmd.export_system_config_extended = export_system_config_extended
    ui_debug_launcher.inject("action", {name = "Export Sys. Config Ext.", cmd = "export_system_config_extended", hide_ui = 0})
end

function on_game_start()
    if not DEV_DEBUG then
        return
    end

    RegisterScriptCallback("on_game_load", on_game_load)
end
