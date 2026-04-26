---@meta

-- Exported in src\xrGame\ui_export_script.cpp

---@class CGameFont
CGameFont = {}

---@enum CGameFont.EAligment
CGameFont.EAligment = {
    alLeft = 0,
    alRight = 1,
    alCenter = 2
}

---@class Patch_Dawnload_Progress
Patch_Dawnload_Progress = {}

function Patch_Dawnload_Progress:GetInProgress() end
function Patch_Dawnload_Progress:GetStatus() end
function Patch_Dawnload_Progress:GetFlieName() end
function Patch_Dawnload_Progress:GetProgress() end

---@class CMainMenu
CMainMenu = {}

function CMainMenu:GetPatchProgress() end
function CMainMenu:CancelDownload() end
function CMainMenu:ValidateCDKey() end
function CMainMenu:GetGSVer() end
function CMainMenu:GetCDKey() end
function CMainMenu:GetPlayerName() end
function CMainMenu:GetDemoInfo() end
function CMainMenu:GetLoginMngr() end
function CMainMenu:GetAccountMngr() end
function CMainMenu:GetProfileStore() end

main_menu = {}

function main_menu.get_main_menu() end

-- Exported in src\xrGame\UIGameCustom_script.cpp

---@class StaticDrawableWrapper
---@field m_endTime any
StaticDrawableWrapper = {}

function StaticDrawableWrapper:wnd() end

---@class CUIGameCustom
CUIGameCustom = {}

function CUIGameCustom:AddDialogToRender() end
function CUIGameCustom:RemoveDialogToRender() end
function CUIGameCustom:AddCustomStatic() end
function CUIGameCustom:RemoveCustomStatic() end
function CUIGameCustom:HideActorMenu() end
function CUIGameCustom:UpdateActorMenu() end
function CUIGameCustom:CurrentItemAtCell() end
function CUIGameCustom:GetWindow() end
function CUIGameCustom:HidePdaMenu() end
function CUIGameCustom:show_messages() end
function CUIGameCustom:hide_messages() end
function CUIGameCustom:GetCustomStatic() end
function CUIGameCustom:update_fake_indicators() end
function CUIGameCustom:enable_fake_indicators() end

function get_hud() end

-- Exported in src\xrGame\ui\UIActorMenu_script.cpp

---@class EDDListType
EDDListType = {}

---@enum EDDListType.EDDListType
EDDListType.EDDListType = {
}

---@class CUIActorMenu
CUIActorMenu = {}

function CUIActorMenu:get_drag_item() end
function CUIActorMenu:highlight_section_in_slot() end
function CUIActorMenu:highlight_for_each_in_slot() end
function CUIActorMenu:refresh_current_cell_item() end
function CUIActorMenu:IsShown() end
function CUIActorMenu:ShowDialog() end
function CUIActorMenu:HideDialog() end
function CUIActorMenu:ToSlot() end
function CUIActorMenu:ToBelt() end

---@class CUIPdaWnd
CUIPdaWnd = {}

function CUIPdaWnd:IsShown() end
function CUIPdaWnd:ShowDialog() end
function CUIPdaWnd:HideDialog() end
function CUIPdaWnd:SetActiveSubdialog() end
function CUIPdaWnd:SetActiveDialog() end
function CUIPdaWnd:GetActiveDialog() end
function CUIPdaWnd:GetActiveSection() end
function CUIPdaWnd:SetPdaXml() end
function CUIPdaWnd:GetPdaXml() end
function CUIPdaWnd:GetTabControl() end

---@class CUIMainIngameWnd
---@field UIStaticDiskIO any readonly
---@field UIStaticQuickHelp any readonly
---@field UIMotionIcon any readonly
---@field UIZoneMap any readonly
---@field m_ui_hud_states any readonly
---@field m_ind_bleeding any readonly
---@field m_ind_radiation any readonly
---@field m_ind_starvation any readonly
---@field m_ind_weapon_broken any readonly
---@field m_ind_helmet_broken any readonly
---@field m_ind_outfit_broken any readonly
---@field m_ind_overweight any readonly
---@field m_ind_boost_psy any readonly
---@field m_ind_boost_radia any readonly
---@field m_ind_boost_chem any readonly
---@field m_ind_boost_wound any readonly
---@field m_ind_boost_weight any readonly
---@field m_ind_boost_health any readonly
---@field m_ind_boost_power any readonly
---@field m_ind_boost_rad any readonly
---@field m_QuickSlotText1 any readonly
---@field m_QuickSlotText2 any readonly
---@field m_QuickSlotText3 any readonly
---@field m_QuickSlotText4 any readonly
CUIMainIngameWnd = {}

function CUIMainIngameWnd:GetQuickSlotIcons() end

---@class CUIZoneMap
---@field disabled any
---@field visible any readonly
CUIZoneMap = {}

function CUIZoneMap:MapFrame() end
function CUIZoneMap:Background() end

---@class CUIMotionIcon
---@class CUIMessagesWindow

---@class CUIHudStatesWnd
---@field m_back any readonly
---@field m_ui_weapon_ammo_color_active any readonly
---@field m_ui_weapon_ammo_color_inactive any readonly
---@field m_ui_weapon_cur_ammo any readonly
---@field m_ui_weapon_fmj_ammo any readonly
---@field m_ui_weapon_ap_ammo any readonly
---@field m_ui_weapon_third_ammo any readonly
---@field m_fire_mode any readonly
---@field m_ui_grenade any readonly
---@field m_ui_weapon_icon any readonly
---@field m_ui_health_bar any readonly
---@field m_ui_stamina_bar any readonly
---@field m_ui_psy_bar any readonly
---@field m_radia_damage any readonly
---@field m_ui_health_bar_show any
---@field m_ui_stamina_bar_show any
---@field m_ui_psy_bar_show any

ActorMenu = {}

function ActorMenu.get_pda_menu() end
function ActorMenu.get_actor_menu() end
function ActorMenu.get_menu_mode() end
function ActorMenu.get_maingame() end
function ActorMenu.get_messages_menu() end

-- Exported in src\xrGame\ui\UIButton_script.cpp

---@class CUIButton
---@class CUI3tButton

---@class CUICheckButton
CUICheckButton = {}

function CUICheckButton:GetCheck() end
function CUICheckButton:SetCheck() end
function CUICheckButton:SetDependControl() end

---@class CUICustomSpin
CUICustomSpin = {}

function CUICustomSpin:GetText() end

---@class CUISpinNum
---@class CUISpinFlt
---@class CUISpinText

---@class CUITrackBar
CUITrackBar = {}

function CUITrackBar:GetCheck() end
function CUITrackBar:SetCheck() end
function CUITrackBar:GetIValue() end
function CUITrackBar:GetFValue() end
function CUITrackBar:SetIValue() end
function CUITrackBar:SetFValue() end
function CUITrackBar:SetStep() end
function CUITrackBar:GetInvert() end
function CUITrackBar:SetInvert() end
function CUITrackBar:SetOptIBounds() end
function CUITrackBar:SetOptFBounds() end
function CUITrackBar:SetCurrentValue() end

-- Exported in src\xrGame\ui\UIComboBox_script.cpp

---@class CUIComboBox
CUIComboBox = {}

function CUIComboBox:SetVertScroll() end
function CUIComboBox:SetListLength() end
function CUIComboBox:CurrentID() end
function CUIComboBox:disable_id() end
function CUIComboBox:enable_id() end
function CUIComboBox:AddItem() end
function CUIComboBox:GetText() end
function CUIComboBox:GetTextOf() end
function CUIComboBox:SetText() end
function CUIComboBox:ClearList() end
function CUIComboBox:SetCurrentOptValue() end
function CUIComboBox:SetCurrentIdx() end
function CUIComboBox:GetCurrentIdx() end

-- Exported in src\xrGame\ui\UIEditBox_script.cpp

---@class CUICustomEdit
CUICustomEdit = {}

function CUICustomEdit:SetText() end
function CUICustomEdit:GetText() end
function CUICustomEdit:CaptureFocus() end
function CUICustomEdit:SetNextFocusCapturer() end

---@class CUIEditBox
CUIEditBox = {}

function CUIEditBox:InitTexture() end

-- Exported in src\xrGame\ui\UIListBox_script.cpp

---@class CUIListBox
CUIListBox = {}

function CUIListBox:ShowSelectedItem() end
function CUIListBox:RemoveAll() end
function CUIListBox:GetSize() end
function CUIListBox:GetSelectedItem() end
function CUIListBox:GetSelectedIndex() end
function CUIListBox:SetSelectedIndex() end
function CUIListBox:SetItemHeight() end
function CUIListBox:GetItemHeight() end
function CUIListBox:GetItemByIndex() end
function CUIListBox:GetItem() end
function CUIListBox:RemoveItem() end
function CUIListBox:AddTextItem() end
function CUIListBox:AddExistingItem() end

---@class CUIListBoxItemCUIListBoxItem
CUIListBoxItem = {}

function CUIListBoxItem:GetTextItem() end
function CUIListBoxItem:AddTextField() end
function CUIListBoxItem:AddIconField() end
function CUIListBoxItem:SetTextColor() end

---@class CUIListBoxItemMsgChain

---@class SServerFilters
---@field empty any
---@field full any
---@field with_pass any
---@field without_pass any
---@field with_ff any
---@field listen_servers any

---@class connect_error_cb
connect_error_cb = {}

function connect_error_cb:bind() end
function connect_error_cb:clear() end

---@class CServerList
CServerList = {}

---@enum CServerList.enum_connect_errcode
CServerList.enum_connect_errcode = {
    ece_unique_nick_not_registred = 0,
    ece_unique_nick_expired = 1
}

function CServerList:SetConnectionErrCb() end
function CServerList:ConnectToSelected() end
function CServerList:SetFilters() end
function CServerList:SetPlayerName() end
function CServerList:RefreshList() end
function CServerList:RefreshQuick() end
function CServerList:ShowServerInfo() end
function CServerList:NetRadioChanged() end
function CServerList:SetSortFunc() end

---@class CUIMapList
CUIMapList = {}

function CUIMapList:SetWeatherSelector() end
function CUIMapList:SetModeSelector() end
function CUIMapList:OnModeChange() end
function CUIMapList:LoadMapList() end
function CUIMapList:SaveMapList() end
function CUIMapList:GetCommandLine() end
function CUIMapList:SetServerParams() end
function CUIMapList:GetCurGameType() end
function CUIMapList:StartDedicatedServer() end
function CUIMapList:SetMapPic() end
function CUIMapList:SetMapInfo() end
function CUIMapList:ClearList() end
function CUIMapList:IsEmpty() end

---@class GAME_TYPE
GAME_TYPE = {}

---@enum GAME_TYPE.gametype
GAME_TYPE.gametype = {
    GAME_UNKNOWN = -1,
    eGameIDDeathmatch = 0,
    eGameIDTeamDeathmatch = 1,
    eGameIDArtefactHunt = 2,
    eGameIDCaptureTheArtefact = 3
}

-- Exported in src\xrGame\ui\UIMapInfo_script.cpp

---@class CUIMapInfo
CUIMapInfo = {}

function CUIMapInfo:Init() end
function CUIMapInfo:InitMap() end

-- Exported in src\xrGame\ui\UIMessageBox_script.cpp

---@class CUIMessageBox
CUIMessageBox = {}

function CUIMessageBox:InitMessageBox() end
function CUIMessageBox:SetText() end
function CUIMessageBox:GetHost() end
function CUIMessageBox:GetPassword() end

---@class CUIMessageBoxEx
CUIMessageBoxEx = {}

function CUIMessageBoxEx:InitMessageBox() end
function CUIMessageBoxEx:SetText() end
function CUIMessageBoxEx:GetHost() end
function CUIMessageBoxEx:GetPassword() end

-- Exported in src\xrGame\ui\UIOptionsManagerScript.cpp

---@class COptionsManager
COptionsManager = {}

function COptionsManager:SaveBackupValues() end
function COptionsManager:SetCurrentValues() end
function COptionsManager:SaveValues() end
function COptionsManager:UndoGroup() end
function COptionsManager:OptionsPostAccept() end
function COptionsManager:SendMessage2Group() end
function COptionsManager:NeedSystemRestart() end
function COptionsManager:NeedVidRestart() end
function COptionsManager:GetRendererName() end

-- Exported in src\xrGame\ui\UIProgressBar_script.cpp

---@class CUIProgressBar
CUIProgressBar = {}

function CUIProgressBar:SetProgressPos() end
function CUIProgressBar:GetProgressPos() end
function CUIProgressBar:GetRange_min() end
function CUIProgressBar:GetRange_max() end
function CUIProgressBar:SetRange() end
function CUIProgressBar:ShowBackground() end
function CUIProgressBar:SetColor() end
function CUIProgressBar:UseColor() end
function CUIProgressBar:SetMinColor() end
function CUIProgressBar:SetMiddleColor() end
function CUIProgressBar:SetMaxColor() end
function CUIProgressBar:GetProgressStatic() end

-- Exported in src\xrGame\ui\UIPropertiesBox_script.cpp

---@class CUIPropertiesBox
CUIPropertiesBox = {}

function CUIPropertiesBox:RemoveItem() end
function CUIPropertiesBox:RemoveAll() end
function CUIPropertiesBox:Show() end
function CUIPropertiesBox:Hide() end
function CUIPropertiesBox:GetSelectedItem() end
function CUIPropertiesBox:AutoUpdateSize() end
function CUIPropertiesBox:AddItem() end
function CUIPropertiesBox:InitPropertiesBox() end

-- Exported in src\xrGame\ui\UIScriptWnd_script.cpp
-- & src\xrGame\ui\uiscriptwnd_script2.cpp

---@enum EUIMessages
EUIMessages = {
	WINDOW_LBUTTON_DOWN = 0,
	WINDOW_RBUTTON_DOWN = 1,
	WINDOW_CBUTTON_DOWN = 2,

	WINDOW_LBUTTON_UP = 3,
	WINDOW_RBUTTON_UP = 4,
	WINDOW_CBUTTON_UP = 5,

	WINDOW_MOUSE_MOVE = 6,
	WINDOW_MOUSE_WHEEL_UP = 7,
	WINDOW_MOUSE_WHEEL_DOWN = 8,
	WINDOW_LBUTTON_DB_CLICK = 9,
	WINDOW_KEY_PRESSED = 10,
	WINDOW_KEY_RELEASED = 11,
	WINDOW_KEY_HOLD = 12,
	WINDOW_MOUSE_CAPTURE_LOST = 13,
	WINDOW_KEYBOARD_CAPTURE_LOST = 14,

	WINDOW_FOCUS_RECEIVED = 15,
	WINDOW_FOCUS_LOST = 16,

	BUTTON_CLICKED = 17,
	BUTTON_DOWN = 18,

	TAB_CHANGED = 19,

	CHECK_BUTTON_SET = 20,
	CHECK_BUTTON_RESET = 21,

	RADIOBUTTON_SET = 22,

	DRAG_DROP_ITEM_DRAG = 23,
	DRAG_DROP_ITEM_DROP = 24,
	DRAG_DROP_ITEM_DB_CLICK = 25,
	DRAG_DROP_ITEM_LBUTTON_CLICK = 26,
	DRAG_DROP_ITEM_RBUTTON_CLICK = 27,
	DRAG_DROP_ITEM_SELECTED = 28,
	DRAG_DROP_ITEM_FOCUSED_UPDATE = 29,

	SCROLLBOX_MOVE = 30,

	SCROLLBAR_VSCROLL = 31,
	SCROLLBAR_HSCROLL = 32,
	SCROLLBAR_NEEDUPDATE = 33,

	CHILD_CHANGED_SIZE = 34,

	LIST_ITEM_CLICKED = 35,
	LIST_ITEM_SELECT = 36,
	LIST_ITEM_FOCUS_RECEIVED = 37,

	PROPERTY_CLICKED = 38,

	MESSAGE_BOX_OK_CLICKED = 39,
	MESSAGE_BOX_YES_CLICKED = 40,
	MESSAGE_BOX_QUIT_WIN_CLICKED = 41,
	MESSAGE_BOX_QUIT_GAME_CLICKED = 42,
	MESSAGE_BOX_NO_CLICKED = 43,
	MESSAGE_BOX_CANCEL_CLICKED = 44,
	MESSAGE_BOX_COPY_CLICKED = 45,

	TALK_DIALOG_TRADE_BUTTON_CLICKED = 46,
	TALK_DIALOG_UPGRADE_BUTTON_CLICKED = 47,
	TALK_DIALOG_QUESTION_CLICKED = 48,

	PDA_TASK_SET_TARGET_MAP = 49,
	PDA_TASK_SHOW_MAP_SPOT = 50,
	PDA_TASK_HIDE_MAP_SPOT = 51,
	PDA_TASK_SHOW_HINT = 52,
	PDA_TASK_HIDE_HINT = 53,

	INVENTORY_DROP_ACTION = 54,
	INVENTORY_EAT_ACTION = 55,
	INVENTORY_EAT2_ACTION = 56,
	INVENTORY_EAT3_ACTION = 57,
	INVENTORY_EAT4_ACTION = 58,
	INVENTORY_EAT5_ACTION = 59,
	INVENTORY_EAT6_ACTION = 60,
	INVENTORY_EAT7_ACTION = 61,
	INVENTORY_EAT8_ACTION = 62,
	INVENTORY_EAT9_ACTION = 63,
	INVENTORY_EAT10_ACTION = 64,
	INVENTORY_EAT11_ACTION = 65,
	INVENTORY_DONATE_ACTION = 66,
	INVENTORY_PLAY_ACTION = 67,
	INVENTORY_TO_BELT_ACTION = 68,
	INVENTORY_TO_SLOT_ACTION = 69,
	INVENTORY_TO_BAG_ACTION = 70,
	INVENTORY_ATTACH_ADDON = 71,
	INVENTORY_REPAIR = 72,

	INVENTORY_ATTACH_SCOPE_ADDON = 73,
	INVENTORY_DETACH_SCOPE_ADDON = 74,

	INVENTORY_ATTACH_SILENCER_ADDON = 75,
	INVENTORY_DETACH_SILENCER_ADDON = 76,

	INVENTORY_ATTACH_GRENADE_LAUNCHER_ADDON = 77,
	INVENTORY_DETACH_GRENADE_LAUNCHER_ADDON = 78,

	INVENTORY_RELOAD_MAGAZINE = 79,
	INVENTORY_UNLOAD_MAGAZINE = 80,
	INVENTORY_SELL_ITEM = 81,

	EDIT_TEXT_COMMIT = 82,
	EDIT_TEXT_CANCEL = 83,
	MAP_SHOW_HINT = 84,
	MAP_HIDE_HINT = 85,
	MAP_SELECT_SPOT = 86,

	MAIN_MENU_RELOADED = 87,
	MAP_SELECT_SPOT2 = 88

}

---@Class CUIScriptWnd
CUIScriptWnd = {}

---OnKeyboard Callback
---@param dik number
---@param keyboard_action EUIMessages
---@return boolean
function CUIScriptWnd:OnKeyboard(dik, keyboard_action) end

---Update Window
function CUIScriptWnd:Update() end

---Dispatch
---@param cmd number
---@param param number
---@return boolean
function CUIScriptWnd:Dispatch(cmd, param) end

---Load
---@param xml_name string
---@return boolean
function CUIScriptWnd:Load(xml_name) end

---Adding a callback
---@param control_id string
---@param evt number
---@param functor fun(arg: any)
---@param object any
function CUIScriptWnd:AddCallback(control_id, evt, functor, object) end

---Register
---@param name string
function CUIScriptWnd:Register(name) end

-- Exported in src\xrGame\ui\UIStatic_script.cpp

---@class CUILines
CUILines = {}

function CUILines:SetFont() end
function CUILines:SetText() end
function CUILines:SetTextST() end
function CUILines:GetText() end
function CUILines:SetElipsis() end
function CUILines:SetTextColor() end

---@class CUIStatic
CUIStatic = {}

function CUIStatic:SetTextureColor() end
function CUIStatic:GetTextureColor() end
function CUIStatic:AdjustHeightToText() end
function CUIStatic:AdjustWidthToText() end
function CUIStatic:GetStretchTexture() end
function CUIStatic:TextControl() end
function CUIStatic:InitTexture() end
function CUIStatic:InitTextureEx() end
function CUIStatic:SetTextureRect() end
function CUIStatic:SetStretchTexture() end
function CUIStatic:GetTextureRect() end
function CUIStatic:EnableHeading() end
function CUIStatic:GetHeading() end
function CUIStatic:SetHeading() end
function CUIStatic:SetConstHeading() end
function CUIStatic:GetConstHeading() end
function CUIStatic:SetColorAnimation() end
function CUIStatic:ResetColorAnimation() end
function CUIStatic:RemoveColorAnimation() end

---@class CUITextWnd
CUITextWnd = {}

function CUITextWnd:AdjustHeightToText() end
function CUITextWnd:AdjustWidthToText() end
function CUITextWnd:SetText() end
function CUITextWnd:SetTextST() end
function CUITextWnd:GetText() end
function CUITextWnd:SetFont() end
function CUITextWnd:GetFont() end
function CUITextWnd:SetTextColor() end
function CUITextWnd:GetTextColor() end
function CUITextWnd:SetTextComplexMode() end
function CUITextWnd:SetTextAlignment() end
function CUITextWnd:SetVTextAlignment() end
function CUITextWnd:SetEllipsis() end
function CUITextWnd:SetTextOffset() end

---@class CUISleepStatic

-- Exported in src\xrGame\ui\UITabControl_script.cpp

---@class CUITabControl
CUITabControl = {}

function CUITabControl:AddItem() end
function CUITabControl:AddItem() end
function CUITabControl:RemoveAll() end
function CUITabControl:GetActiveId() end
function CUITabControl:GetTabsCount() end
function CUITabControl:SetActiveTab() end
function CUITabControl:GetButtonById() end
function CUITabControl:GetEnabled() end
function CUITabControl:SetEnabled() end

---@class CUITabButton

-- Exported in src\xrGame\ui\UIWindow_script.cpp

function GetARGB() end
function ClrGetA() end
function ClrGetR() end
function ClrGetG() end
function ClrGetB() end
function ClrSetA() end
function ClrSetR() end
function ClrSetG() end
function ClrSetB() end
function GetFontSmall() end
function GetFontMedium() end
function GetFontDI() end
function GetFontGraffiti19Russian() end
function GetFontGraffiti22Russian() end
function GetFontLetterica16Russian() end
function GetFontLetterica18Russian() end
function GetFontGraffiti32Russian() end
function GetFontGraffiti50Russian() end
function GetFontLetterica25() end
function GetCursorPosition() end
function SetCursorPosition() end
function FitInRect() end

---@class CUIWindow
CUIWindow = {}

function CUIWindow:AttachChild() end
function CUIWindow:DetachChild() end
function CUIWindow:SetAutoDelete() end
function CUIWindow:IsAutoDelete() end
function CUIWindow:IsCursorOverWindow() end
function CUIWindow:FocusReceiveTime() end
function CUIWindow:GetAbsoluteRect() end
--[[
function CUIWindow:DisableHint() end
function CUIWindow:EnableHint() end
function CUIWindow:SetHintDelay() end
function CUIWindow:GetHintDelay() end
function CUIWindow:RemoveHint() end
function CUIWindow:SetHintWnd() end
function CUIWindow:GetHintWnd() end
function CUIWindow:SetHintText() end
function CUIWindow:GetHintText() end
]]--
function CUIWindow:SetWndRect() end
function CUIWindow:SetWndPos() end
function CUIWindow:SetWndSize() end
function CUIWindow:GetWndPos() end
function CUIWindow:GetWidth() end
function CUIWindow:GetHeight() end
function CUIWindow:Enable() end
function CUIWindow:IsEnabled() end
function CUIWindow:Show() end
function CUIWindow:IsShown() end
function CUIWindow:WindowName() end
function CUIWindow:SetWindowName() end
function CUIWindow:SetPPMode() end
function CUIWindow:ResetPPMode() end

---@class CDialogHolder
CDialogHolder = {}

function CDialogHolder:AddDialogToRender() end
function CDialogHolder:RemoveDialogToRender() end

---@class CUIDialogWnd
CUIDialogWnd = {}

function CUIDialogWnd:ShowDialog() end
function CUIDialogWnd:HideDialog() end
function CUIDialogWnd:GetHolder() end
function CUIDialogWnd:AllowMovement() end
function CUIDialogWnd:AllowCursor() end
function CUIDialogWnd:AllowCenterCursor() end
function CUIDialogWnd:AllowWorkInPause() end

---@class CUIFrameWindow
CUIFrameWindow = {}

function CUIFrameWindow:SetWidth() end
function CUIFrameWindow:SetHeight() end
function CUIFrameWindow:SetColor() end

---@class CUIFrameLineWnd
CUIFrameLineWnd = {}

function CUIFrameLineWnd:SetWidth() end
function CUIFrameLineWnd:SetHeight() end
function CUIFrameLineWnd:SetColor() end

---@class UIHint
UIHint = {}

function UIHint:SetWidth() end
function UIHint:SetHeight() end
function UIHint:SetHintText() end
function UIHint:GetHintText() end

---@class CUIMMShniaga
CUIMMShniaga = {}

function CUIMMShniaga:SetVisibleMagnifier() end
function CUIMMShniaga:SetPage() end
function CUIMMShniaga:ShowPage() end

---@enum CUIMMShniaga.enum_page_id
CUIMMShniaga.enum_page_id = {
    epi_main = 0,
    epi_new_game = 1,
    epi_new_network_game = 2
}

---@class CUIScrollView
CUIScrollView = {}

function CUIScrollView:AddWindow() end
function CUIScrollView:RemoveWindow() end
function CUIScrollView:Clear() end
function CUIScrollView:ScrollToBegin() end
function CUIScrollView:ScrollToEnd() end
function CUIScrollView:GetMinScrollPos() end
function CUIScrollView:GetMaxScrollPos() end
function CUIScrollView:GetCurrentScrollPos() end
function CUIScrollView:SetFixedScrollBar() end
function CUIScrollView:SetScrollPos() end

---@class ui_events
ui_events = {}

---@enum ui_events.events
ui_events.events = {
    WINDOW_LBUTTON_DOWN = 0,
    WINDOW_RBUTTON_DOWN = 1,
    WINDOW_LBUTTON_UP = 2,
    WINDOW_RBUTTON_UP = 3,
    WINDOW_MOUSE_MOVE = 4,
    WINDOW_LBUTTON_DB_CLICK = 5,
    WINDOW_KEY_PRESSED = 6,
    WINDOW_KEY_RELEASED = 7,
    WINDOW_KEYBOARD_CAPTURE_LOST = 8,
    BUTTON_CLICKED = 9,
    BUTTON_DOWN = 10,
    TAB_CHANGED = 11,
    CHECK_BUTTON_SET = 12,
    CHECK_BUTTON_RESET = 13,
    RADIOBUTTON_SET = 14,
    SCROLLBOX_MOVE = 15,
    SCROLLBAR_VSCROLL = 16,
    SCROLLBAR_HSCROLL = 17,
    LIST_ITEM_CLICKED = 18,
    LIST_ITEM_SELECT = 19,
    PROPERTY_CLICKED = 20,
    MESSAGE_BOX_OK_CLICKED = 21,
    MESSAGE_BOX_YES_CLICKED = 22,
    MESSAGE_BOX_NO_CLICKED = 23,
    MESSAGE_BOX_CANCEL_CLICKED = 24,
    MESSAGE_BOX_COPY_CLICKED = 25,
    MESSAGE_BOX_QUIT_GAME_CLICKED = 26,
    MESSAGE_BOX_QUIT_WIN_CLICKED = 27,
    EDIT_TEXT_COMMIT = 28,
    MAIN_MENU_RELOADED = 29
}
