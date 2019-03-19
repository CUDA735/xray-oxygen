#include "stdafx.h"
#include "key_binding_registrator.h"
#include "..\xrEngine\xr_level_controller.h"
#include "..\xrEngine\xr_input.h"

#include "luabind/luabind.hpp"
using namespace luabind;

u8 DIK_to_bind(u8 dik){
	return get_binded_action(dik);
}

#pragma optimize("gyts",on)
void key_binding_registrator::script_register(lua_State *L)
{
	module(L)
	[
		def("dik_to_bind",		&DIK_to_bind),

		class_<enum_exporter<EGameActions> >("key_bindings")
			.enum_("commands")
			[
				value("kFWD",						int(kFWD)),
				value("kBACK",						int(kBACK)),
				value("kL_STRAFE",					int(kL_STRAFE)),
				value("kR_STRAFE",					int(kR_STRAFE)),
				value("kL_LOOKOUT",					int(kL_LOOKOUT)),
				value("kR_LOOKOUT",					int(kR_LOOKOUT)),
				value("kLEFT",						int(kLEFT)),
				value("kRIGHT",						int(kRIGHT)),
				value("kUP",						int(kUP)),
				value("kDOWN",						int(kDOWN)),
				value("kJUMP",						int(kJUMP)),
				value("kCROUCH",					int(kCROUCH)),
				value("kACCEL",						int(kACCEL)),
				value("kCAM_1",						int(kCAM_1)),
				value("kCAM_2",						int(kCAM_2)),
				value("kCAM_3",						int(kCAM_3)),
				value("kCAM_ZOOM_IN",				int(kCAM_ZOOM_IN)),
				value("kCAM_ZOOM_OUT",				int(kCAM_ZOOM_OUT)),
				value("kTORCH",						int(kTORCH)),
				value("kNIGHT_VISION",				int(kNIGHT_VISION)),
				value("kWPN_1",						int(kWPN_1)),
				value("kWPN_2",						int(kWPN_2)),
				value("kWPN_3",						int(kWPN_3)),
				value("kWPN_4",						int(kWPN_4)),
				value("kWPN_5",						int(kWPN_5)),
				value("kWPN_6",						int(kWPN_6)),
				value("kWPN_NEXT",					int(kWPN_NEXT)),
				value("kWPN_FIRE",					int(kWPN_FIRE)),
				value("kWPN_RELOAD",				int(kWPN_RELOAD)),
				value("kWPN_ZOOM",					int(kWPN_ZOOM)),
				value("kWPN_FUNC",					int(kWPN_FUNC)),
				value("kUSE",						int(kUSE)),
				value("kDROP",						int(kDROP)),
				value("kSCORES",					int(kSCORES)),
				value("kSCREENSHOT",				int(kSCREENSHOT)),
				value("kQUIT",						int(kQUIT)),
				value("kDEV_NOCLIP",				int(kDEV_NOCLIP)),
				value("kDEV_ACTION1",				int(kDEV_ACTION1)),
				value("kDEV_ACTION2",				int(kDEV_ACTION2)),
				value("kDEV_ACTION3",				int(kDEV_ACTION3)),
				value("kDEV_ACTION4",				int(kDEV_ACTION4)),
				value("kCONSOLE",					int(kCONSOLE)),
				value("kQUICK_USE_1",				int(kQUICK_USE_1)),
				value("kQUICK_USE_2",				int(kQUICK_USE_2)),
				value("kQUICK_USE_3",				int(kQUICK_USE_3)),
				value("kQUICK_USE_4",				int(kQUICK_USE_4)),
				value("kINVENTORY",					int(kINVENTORY))
			],
		class_<key_binding_registrator >("DIK_keys")
			.enum_("DIK_keys")
			[
				value("DIK_0",							int(VK_0			)),
				value("DIK_1",							int(VK_1			)),
				value("DIK_2",							int(VK_2			)),
				value("DIK_3",							int(VK_3			)),
				value("DIK_4",							int(VK_4			)),
				value("DIK_5",							int(VK_5			)),
				value("DIK_6",							int(VK_6			)),
				value("DIK_7",							int(VK_7			)),
				value("DIK_8",							int(VK_8			)),
				value("DIK_9",							int(VK_9			)),
				
				value("DIK_F1",							int(VK_F1			)),
				value("DIK_F2",							int(VK_F2			)),
				value("DIK_F3",							int(VK_F3			)),
				value("DIK_F4",							int(VK_F4			)),
				value("DIK_F5",							int(VK_F5			)),
				value("DIK_F6",							int(VK_F6			)),
				value("DIK_F7",							int(VK_F7			)),
				value("DIK_F8",							int(VK_F8			)),
				value("DIK_F9",							int(VK_F9			)),
				value("DIK_F10",						int(VK_F10			)),
				value("DIK_F11",						int(VK_F11			)),
				value("DIK_F12",						int(VK_F12			)),
				value("DIK_F13",						int(VK_F13			)),
				value("DIK_F14",						int(VK_F14			)),
				value("DIK_F15",						int(VK_F15			)),
				
				value("DIK_NUMLOCK",					int(VK_NUMLOCK		)),
				value("DIK_NUMPADENTER",				int(VK_RETURN	)),
				value("DIK_NUMPAD0",					int(VK_NUMPAD0		)),
				value("DIK_NUMPAD1",					int(VK_NUMPAD1		)),
				value("DIK_NUMPAD2",					int(VK_NUMPAD2		)),
				value("DIK_NUMPAD3",					int(VK_NUMPAD3		)),
				value("DIK_NUMPAD4",					int(VK_NUMPAD4		)),
				value("DIK_NUMPAD5",					int(VK_NUMPAD5		)),
				value("DIK_NUMPAD6",					int(VK_NUMPAD6		)),
				value("DIK_NUMPAD7",					int(VK_NUMPAD7		)),
				value("DIK_NUMPAD8",					int(VK_NUMPAD8		)),
				value("DIK_NUMPAD9",					int(VK_NUMPAD9		)),
				
				value("VK_LBUTTON",						int(VK_LBUTTON			)),
				value("VK_RBUTTON",						int(VK_RBUTTON			)),
				value("VK_MBUTTON",						int(VK_MBUTTON			)),
				value("MOUSE_4",						int(VK_XBUTTON1			)), // New
				value("MOUSE_5",						int(VK_XBUTTON2			)), // New
				
				value("DIK_DECIMAL",					int(VK_DECIMAL		)),
				value("DIK_KANA",						int(VK_KANA			)),
				value("DIK_NOCONVERT",					int(VK_NONCONVERT	)),
				value("DIK_RCONTROL",					int(VK_RCONTROL		)),
				value("DIK_DIVIDE",						int(VK_DIVIDE		)),
				value("DIK_RMENU",						int(VK_RMENU		)),
				value("DIK_UP",							int(VK_UP			)),
				value("DIK_LEFT",						int(VK_LEFT			)),
				value("DIK_END",						int(VK_END			)),
				value("DIK_NEXT",						int(VK_NEXT			)),
				value("DIK_DELETE",						int(VK_DELETE		)),
				value("DIK_RWIN",						int(VK_RWIN			)),
				value("DIK_PAUSE",						int(VK_PAUSE		)),
				value("DIK_MINUS",						int(VK_OEM_MINUS	)),
				value("DIK_BACK",						int(VK_BACK			)),
				value("DIK_RETURN",						int(VK_RETURN		)),
				
				value("DIK_A",							int(VK_A			)),
				value("DIK_D",							int(VK_D			)),
				value("DIK_G",							int(VK_G			)),
				value("DIK_J",							int(VK_J			)),
				value("DIK_L",							int(VK_L			)),
				value("DIK_W",							int(VK_W			)),
				value("DIK_R",							int(VK_R			)),
				value("DIK_Y",							int(VK_Y			)),
				value("DIK_I",							int(VK_I			)),
				value("DIK_P",							int(VK_P			)),
				value("DIK_S",							int(VK_S			)),
				value("DIK_F",							int(VK_F			)),
				value("DIK_H",							int(VK_H			)),
				value("DIK_K",							int(VK_K			)),
				value("DIK_X",							int(VK_X			)),
				value("DIK_V",							int(VK_V			)),
				value("DIK_N",							int(VK_N			)),
				value("DIK_Q",							int(VK_Q			)),
				value("DIK_E",							int(VK_E			)),
				value("DIK_T",							int(VK_T			)),
				value("DIK_U",							int(VK_U			)),
				value("DIK_O",							int(VK_O			)),
				value("DIK_Z",							int(VK_Z			)),
				value("DIK_C",							int(VK_C			)),
				value("DIK_B",							int(VK_B			)),
				value("DIK_M",							int(VK_M			)),
				
				value("DIK_ESCAPE",						int(VK_ESCAPE		)),
				value("DIK_EQUALS",						int(VK_OEM_PLUS		)),
				value("DIK_TAB",						int(VK_TAB 		)),
				value("DIK_LBRACKET",					int(VK_OEM_4)),
				value("DIK_RBRACKET",					int(VK_OEM_6)),
				value("DIK_LCONTROL",					int(VK_LCONTROL	)),
				value("DIK_GRAVE",						int(VK_OEM_3		)),
				value("DIK_BACKSLASH",					int(VK_OEM_7		)),
				value("DIK_COMMA",						int(VK_OEM_COMMA	)),
				value("DIK_SLASH",						int(VK_OEM_2		)),
				value("DIK_MULTIPLY",					int(VK_MULTIPLY		)),
				value("DIK_SPACE",						int(VK_SPACE		)),
				value("DIK_APOSTROPHE",					int(VK_OEM_3		)),
				value("DIK_LSHIFT",						int(VK_SHIFT		)),
				value("DIK_RSHIFT",						int(VK_RSHIFT		)),
				value("DIK_LMENU",						int(VK_LMENU		)),
				value("DIK_CAPITAL",					int(VK_CAPITAL		)),
				value("DIK_SCROLL",						int(VK_SCROLL		)),
				value("DIK_SUBTRACT",					int(VK_SUBTRACT	)),
				value("DIK_ADD",						int(VK_ADD			)),
				value("DIK_CONVERT",					int(VK_CONVERT		)),
				value("DIK_KANJI",						int(VK_KANJI		)),
				value("DIK_NUMPADENTER",				int(VK_RETURN		)),
				value("DIK_NUMPADCOMMA",				int(VK_OEM_COMMA	)),
				value("DIK_HOME",						int(VK_HOME		)),
				value("DIK_PRIOR",						int(VK_PRIOR		)),
				value("DIK_RIGHT",						int(VK_RIGHT		)),
				value("DIK_DOWN",						int(VK_DOWN		)),
				value("DIK_INSERT",						int(VK_INSERT		)),
				value("DIK_LWIN",						int(VK_LWIN		)),
				value("DIK_APPS",						int(VK_APPS		)),
				value("DIK_RETURN",						int(VK_RETURN		))
				
			]
	];
}
