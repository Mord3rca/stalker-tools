local log_name = "[DLTX Exporter] "

function debug_cmd_list.cmd.export_system_config(_, __, cout)
    cout:SendOutput(log_name .. "Exporting configuration")
    system_ini():save_as("outfile.ini")
    cout:SendOutput(log_name .. "Export finished")
end


function _adding_motion_length(section)
    local anim_key_name = {
        "anm_reload"
    } -- Can be extended for your needs
    -- To get all available anm key exec: grep -Eo 'anm_[^= ]*' outfile.ini | sort -u

    for _, name in pairs(anim_key_name) do
        if system_ini():line_exist(section, name) then
            -- If exist ask the game to calculate anim length and write it down to sys. config
            system_ini():w_float(
                section, name .. "_mlength",
                game.get_motion_length(section, name, 1)
            )
        end
    end

    return false  -- Continue iteration
end

function debug_cmd_list.cmd.export_system_config_extended(_, __, cout)
    cout:SendOutput(log_name .. "Adding add. info in system configuration")
    system_ini():set_readonly(false)
    system_ini():section_for_each(_adding_motion_length)
    system_ini():set_readonly(true)

    -- Use previous func to dump system config
    debug_cmd_list.cmd.export_system_config(_, __, cout)
end

-- Register dumping functions in DBG mode menu
ui_debug_launcher.inject("action", {name = "Export System Config", cmd = "export_system_config", hide_ui = 0})
ui_debug_launcher.inject("action", {name = "Export Sys. Config Ext.", cmd = "export_system_config_extended", hide_ui = 0})
