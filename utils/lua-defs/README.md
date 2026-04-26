## LUA definition files

This is a collection of LUA definition files used for documenting STALKER [XRay Monolith](https://github.com/themrdemonized/xray-monolith) LUA API.

### Installation

This set of definition are designed to be use with [lua-language-server](https://github.com/luals/lua-language-server) a VSCode addon

Add this folder to your `workspace.library` configuration key in addon settings (more info [here](https://luals.github.io/wiki/configuration/))

### TODO

List of files containing a LUA register which need a def file:

* [x] src/xrGame/account_manager_script.cpp
* [x] src/xrGame/action_base_script.cpp
* [x] src/xrGame/action_planner_action_script.cpp
* [x] src/xrGame/action_planner_script.cpp
* [x] src/xrGame/ActorCondition_script.cpp
* [x] src/xrGame/actor_script.cpp
* [x] src/xrGame/ai_crow_script.cpp
* [x] src/xrGame/ai/monsters/bloodsucker/bloodsucker_script.cpp
* [x] src/xrGame/ai/monsters/boar/boar_script.cpp
* [x] src/xrGame/ai/monsters/burer/burer_script.cpp
* [x] src/xrGame/ai/monsters/cat/cat_script.cpp
* [x] src/xrGame/ai/monsters/chimera/chimera_script.cpp
* [x] src/xrGame/ai/monsters/controller/controller_script.cpp
* [x] src/xrGame/ai/monsters/dog/dog_script.cpp
* [x] src/xrGame/ai/monsters/flesh/flesh_script.cpp
* [x] src/xrGame/ai/monsters/fracture/fracture_script.cpp
* [x] src/xrGame/ai/monsters/poltergeist/poltergeist_script.cpp
* [x] src/xrGame/ai/monsters/pseudodog/pseudodog_script.cpp
* [x] src/xrGame/ai/monsters/pseudogigant/pseudogigant_script.cpp
* [x] src/xrGame/ai/monsters/snork/snork_script.cpp
* [x] src/xrGame/ai/monsters/tushkano/tushkano_script.cpp
* [x] src/xrGame/ai/monsters/zombie/zombie_script.cpp
* [x] src/xrGame/ai/stalker/ai_stalker_script.cpp
* [x] src/xrGame/ai/trader/ai_trader_script.cpp
* [x] src/xrGame/alife_human_brain_script.cpp
* [x] src/xrGame/alife_monster_brain_script.cpp
* [x] src/xrGame/alife_monster_detail_path_manager_script.cpp
* [x] src/xrGame/alife_monster_movement_manager_script.cpp
* [x] src/xrGame/alife_monster_patrol_path_manager_script.cpp
* [x] src/xrGame/alife_simulator_script.cpp
* [x] src/xrGame/alife_smart_terrain_task_script.cpp
* [x] src/xrGame/antirad_script.cpp
* [x] src/xrGame/artefact_script.cpp
* [x] src/xrGame/base_client_classes_script.cpp
* [x] src/xrGame/BottleItem_script.cpp
* [x] src/xrGame/CarScript.cpp
* [x] src/xrGame/client_spawn_manager_script.cpp
* [x] src/xrGame/console_registrator_script.cpp
* [x] src/xrGame/cover_point_script.cpp
* [x] src/xrGame/CustomOutfit_script.cpp
* [x] src/xrGame/CustomZone_script.cpp
* [x] src/xrGame/DemoInfo.cpp
* [x] src/xrGame/eatable_item_script.cpp
* [x] src/xrGame/ef_storage_script.cpp
* [x] src/xrGame/ExplosiveScript.cpp
* [x] src/xrGame/F1.cpp
* [x] src/xrGame/FoodItem_script.cpp
* [x] src/xrGame/fs_registrator_script.cpp
* [x] src/xrGame/game_cl_single.cpp
* [x] src/xrGame/game_graph_script.cpp
* [x] src/xrGame/GameTask_script.cpp
* [x] src/xrGame/HairsZone_script.cpp
* [x] src/xrGame/HangingLamp.cpp
* [x] src/xrGame/helicopter_script.cpp
* [x] src/xrGame/holder_custom_script.cpp
* [x] src/xrGame/InventoryBox_script.cpp
* [x] src/xrGame/inventory_item_script.cpp
* [x] src/xrGame/InventoryOwner_script.cpp
* [x] src/xrGame/key_binding_registrator_script.cpp
* [x] src/xrGame/level_script.cpp
* [x] src/xrGame/login_manager_script.cpp
* [x] src/xrGame/medkit_script.cpp
* [x] src/xrGame/memory_space_script.cpp
* [x] src/xrGame/mincer_script.cpp
* [x] src/xrGame/Missile.cpp
* [x] src/xrGame/MosquitoBald_script.cpp
* [x] src/xrGame/particle_params_script.cpp
* [x] src/xrGame/patrol_path_params_script.cpp
* [x] src/xrGame/PhraseDialog_script.cpp
* [x] src/xrGame/PHSimpleCallsScript.cpp
* [x] src/xrGame/PhysicObject_script.cpp
* [x] src/xrGame/physics_element_scripted.cpp
* [x] src/xrGame/physics_joint_scripted.cpp
* [x] src/xrGame/physics_shell_scripted.cpp
* [x] src/xrGame/physics_world_scripted.cpp
* [x] src/xrGame/player_hud_script.cpp
* [x] src/xrGame/profile_data_types_script.cpp
* [x] src/xrGame/profile_store_script.cpp
* [x] src/xrGame/property_evaluator_script.cpp
* [x] src/xrGame/property_storage_script.cpp
* [x] src/xrGame/RGD5.cpp
* [x] src/xrGame/saved_game_wrapper_script.cpp
* [x] src/xrGame/Scope.cpp
* [x] src/xrGame/script_action_condition_script.cpp
* [x] src/xrGame/script_animation_action_script.cpp
* [x] src/xrGame/script_attachment_script.cpp
* [x] src/xrGame/script_binder_object_script.cpp
* [x] src/xrGame/script_effector_script.cpp
* [x] src/xrGame/script_entity_action_script.cpp
* [ ] src/xrGame/script_game_object_script2.cpp
* [ ] src/xrGame/script_game_object_script3.cpp
* [ ] src/xrGame/script_game_object_script.cpp
* [ ] src/xrGame/script_game_object_script_trader.cpp
* [x] src/xrGame/script_hit_script.cpp
* [x] src/xrGame/script_imgui_script.cpp
* [x] src/xrGame/script_lanim.cpp
* [x] src/xrGame/script_light_script.cpp
* [x] src/xrGame/script_monster_action_script.cpp
* [x] src/xrGame/script_monster_hit_info_script.cpp
* [x] src/xrGame/script_movement_action_script.cpp
* [x] src/xrGame/script_object_action_script.cpp
* [x] src/xrGame/script_particle_action_script.cpp
* [x] src/xrGame/script_particles_script.cpp
* [x] src/xrGame/script_render_device_script.cpp
* [x] src/xrGame/script_sound_action_script.cpp
* [x] src/xrGame/script_sound_info_script.cpp
* [x] src/xrGame/script_sound_script.cpp
* [x] src/xrGame/script_wallmarks_script.cpp
* [x] src/xrGame/script_watch_action_script.cpp
* [x] src/xrGame/script_world_property_script.cpp
* [x] src/xrGame/script_world_state_script.cpp
* [x] src/xrGame/ScriptXMLInit.cpp
* [x] src/xrGame/script_zone_script.cpp
* [x] src/xrGame/searchlight_script.cpp
* [x] src/xrGame/smart_cover_object_script.cpp
* [x] src/xrGame/space_restrictor_script.cpp
* [x] src/xrGame/StalkerOutfit.cpp
* [x] src/xrGame/torch_script.cpp
* [x] src/xrGame/ui_export_script.cpp
* [x] src/xrGame/UIGameCustom_script.cpp
* [x] src/xrGame/ui/UIActorMenu_script.cpp
* [x] src/xrGame/ui/UIButton_script.cpp
* [x] src/xrGame/ui/UIComboBox_script.cpp
* [x] src/xrGame/ui/UIEditBox_script.cpp
* [x] src/xrGame/ui/UIListBox_script.cpp
* [x] src/xrGame/ui/UIMapInfo_script.cpp
* [x] src/xrGame/ui/UIMessageBox_script.cpp
* [x] src/xrGame/ui/UIOptionsManagerScript.cpp
* [x] src/xrGame/ui/UIProgressBar_script.cpp
* [x] src/xrGame/ui/UIPropertiesBox_script.cpp
* [x] src/xrGame/ui/uiscriptwnd_script2.cpp
* [x] src/xrGame/ui/UIScriptWnd_script.cpp
* [x] src/xrGame/ui/UIStatic_script.cpp
* [x] src/xrGame/ui/UITabControl_script.cpp
* [x] src/xrGame/ui/UIWindow_script.cpp
* [x] src/xrGame/WeaponAK74.cpp
* [x] src/xrGame/WeaponAmmo_script.cpp
* [x] src/xrGame/WeaponBinoculars_script.cpp
* [x] src/xrGame/weaponBM16_script.cpp
* [x] src/xrGame/WeaponFN2000.cpp
* [x] src/xrGame/WeaponFORT.cpp
* [x] src/xrGame/WeaponGroza.cpp
* [x] src/xrGame/WeaponHPSA_script.cpp
* [x] src/xrGame/WeaponKnife_script.cpp
* [x] src/xrGame/WeaponLR300.cpp
* [x] src/xrGame/WeaponPM.cpp
* [x] src/xrGame/WeaponRG6_script.cpp
* [x] src/xrGame/WeaponRPG7_script.cpp
* [x] src/xrGame/weaponshotgun_script.cpp
* [x] src/xrGame/WeaponSSRS_script.cpp
* [x] src/xrGame/WeaponStatMgunIR.cpp
* [x] src/xrGame/WeaponSVD.cpp
* [x] src/xrGame/WeaponSVU.cpp
* [x] src/xrGame/WeaponUSP45.cpp
* [x] src/xrGame/WeaponVal.cpp
* [x] src/xrGame/WeaponVintorez.cpp
* [x] src/xrGame/WeaponWalther.cpp
* [x] src/xrServerEntities/object_factory_script.cpp
* [x] src/xrServerEntities/script_engine_script.cpp
* [x] src/xrServerEntities/script_fcolor_script.cpp
* [x] src/xrServerEntities/script_flags_script.cpp
* [x] src/xrServerEntities/script_fmatrix_script.cpp
* [x] src/xrServerEntities/script_fvector_script.cpp
* [x] src/xrServerEntities/script_ini_file_script.cpp
* [x] src/xrServerEntities/script_net_packet_script.cpp
* [x] src/xrServerEntities/script_reader_script.cpp
* [x] src/xrServerEntities/script_rtoken_list_script.cpp
* [x] src/xrServerEntities/script_sound_type_script.cpp
* [x] src/xrServerEntities/script_token_list_script.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_Items_script.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_Items_script2.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_Items_script3.cpp
* [x] src/xrServerEntities/xrserver_objects_alife_monsters_script3.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_Monsters_script4.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_Monsters_script2.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_Monsters_script.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_script2.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_script3.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_script.cpp
* [x] src/xrServerEntities/xrServer_Objects_Alife_Smartcovers_script.cpp
* [x] src/xrServerEntities/xrServer_Objects_script2.cpp
* [x] src/xrServerEntities/xrServer_Objects_script.cpp

Command used to gen file list: `grep -lR 'script_register' | sort -u`

Yes ... I may have missed some of them.
