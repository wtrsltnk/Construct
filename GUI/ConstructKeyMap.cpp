#include "Construct.h"

tKeyMap* Construct::GetWindowsKeyMap()
{
	static tKeyMap keymap;

	keymap.mapsize = VK_OEM_CLEAR;
	keymap.map = new eKeys[keymap.mapsize];
	
	for (unsigned int i = 0; i < keymap.mapsize; i++)
		keymap.map[i] = KEY_NOT_MAPPED;

	// VK_LBUTTON (01) - Left mouse button
	keymap.map[VK_LBUTTON] = KEY_NOT_MAPPED;

	// VK_RBUTTON (02) - Right mouse button
	keymap.map[VK_RBUTTON] = KEY_NOT_MAPPED;

	// VK_CANCEL (03) - Control-break processing
	keymap.map[VK_CANCEL] = KEY_NOT_MAPPED;

	// VK_MBUTTON (04) - Middle mouse button (three-button mouse)
	keymap.map[VK_MBUTTON] = KEY_NOT_MAPPED;

	// VK_XBUTTON1 (05) - Windows 2000/XP: X1 mouse button
	keymap.map[0x05] = KEY_NOT_MAPPED;

	// VK_XBUTTON2 (06) - Windows 2000/XP: X2 mouse button
	keymap.map[0x06] = KEY_NOT_MAPPED;

	// VK_BACK (08) - BACKSPACE key
	keymap.map[VK_BACK] = KEY_BACKSPACE;
	
	// VK_TAB (09) - TAB key
	keymap.map[VK_TAB] = KEY_TAB;
	
	// VK_CLEAR (0C) - CLEAR key
	keymap.map[VK_CLEAR] = KEY_NOT_MAPPED;
	
	// VK_RETURN (0D) - ENTER key
	keymap.map[VK_RETURN] = KEY_RETURN;
	
	// VK_SHIFT (10) - SHIFT key
	keymap.map[VK_SHIFT] = KEY_LSHIFT;
	
	// VK_CONTROL (11) - CTRL key
	keymap.map[VK_CONTROL] = KEY_LCONTROL;
	
	// VK_MENU (12) - ALT key
	keymap.map[VK_MENU] = KEY_LALT;
	
	// K_PAUSE (13) - PAUSE key
	keymap.map[VK_PAUSE] = KEY_PAUSE;
	
	// VK_CAPITAL (14) - CAPS LOCK key
	keymap.map[VK_CAPITAL] = KEY_CAPS;
	
	// VK_ESCAPE (1B) - ESC key
	keymap.map[VK_ESCAPE] = KEY_ESCAPE;
	
	// VK_SPACE (20) - SPACEBAR
	keymap.map[VK_SPACE] = KEY_SPACE;
	
	// VK_PRIOR (21) - PAGE UP key
	keymap.map[VK_PRIOR] = KEY_PGUP;
	
	// VK_NEXT (22) - PAGE DOWN key
	keymap.map[VK_NEXT] = KEY_PGDOWN;
	
	// VK_END (23) - END key
	keymap.map[VK_END] = KEY_END;
	
	// VK_HOME (24) - HOME key
	keymap.map[VK_HOME] = KEY_HOME;
	
	// VK_LEFT (25) - LEFT ARROW key
	keymap.map[VK_LEFT] = KEY_LEFT;
	
	// VK_UP (26) - UP ARROW key
	keymap.map[VK_UP] = KEY_UP;
	
	// VK_RIGHT (27) - RIGHT ARROW key
	keymap.map[VK_RIGHT] = KEY_RIGHT;
	
	// VK_DOWN (28) - DOWN ARROW key
	keymap.map[VK_DOWN] = KEY_DOWN;
	
	// VK_SELECT (29) - SELECT key
	keymap.map[VK_SELECT] = KEY_NOT_MAPPED;
	
	// VK_PRINT (2A) - PRINT key
	keymap.map[VK_PRINT] = KEY_PRINT;
	
	// VK_EXECUTE (2B) - EXECUTE key
	keymap.map[VK_EXECUTE] = KEY_NOT_MAPPED;
	
	// VK_SNAPSHOT (2C) - PRINT SCREEN key
	keymap.map[VK_SNAPSHOT] = KEY_PRTSC;
	
	// VK_INSERT (2D) - INS key
	keymap.map[VK_INSERT] = KEY_INSERT;
	
	// VK_DELETE (2E) - DEL key
	keymap.map[VK_INSERT] = KEY_DELETE;
	
	// VK_HELP (2F) - HELP key
	keymap.map[VK_HELP] = KEY_NOT_MAPPED;
	
	// (30) - 0 key
	keymap.map[0x30] = KEY_0;
	
	 // (31) - 1 key
	keymap.map[0x31] = KEY_1;
	
	 // (32) - 2 key
	keymap.map[0x32] = KEY_2;
	
	 // (33) - 3 key
	keymap.map[0x33] = KEY_3;
	
	 // (34) - 4 key
	keymap.map[0x34] = KEY_4;
	
	 // (35) - 5 key
	keymap.map[0x35] = KEY_5;
	
	 // (36) - 6 key
	keymap.map[0x36] = KEY_6;
	
	 // (37) - 7 key
	keymap.map[0x37] = KEY_7;
	
	 // (38) - 8 key
	keymap.map[0x38] = KEY_8;
	
	 // (39) - 9 key
	keymap.map[0x39] = KEY_9;
	
	 // (41) - A key
	keymap.map[0x41] = KEY_A;
	
	 // (42) - B key
	keymap.map[0x42] = KEY_B;
	
	 // (43) - C key
	keymap.map[0x43] = KEY_C;
	
	 // (44) - D key
	keymap.map[0x44] = KEY_D;
	
	 // (45) - E key
	keymap.map[0x45] = KEY_E;
	
	 // (46) - F key
	keymap.map[0x46] = KEY_F;
	
	 // (47) - G key
	keymap.map[0x47] = KEY_G;
	
	 // (48) - H key
	keymap.map[0x48] = KEY_H;
	
	 // (49) - I key
	keymap.map[0x49] = KEY_I;
	
	 // (4A) - J key
	keymap.map[0x4A] = KEY_J;
	
	 // (4B) - K key
	keymap.map[0x4B] = KEY_K;
	
	 // (4C) - L key
	keymap.map[0x4C] = KEY_L;
	
	 // (4D) - M key
	keymap.map[0x4D] = KEY_M;
	
	 // (4E) - N key
	keymap.map[0x4E] = KEY_N;
	
	 //  (4F) - O key
	keymap.map[0x4F] = KEY_O;
	
	 // (50) - P key
	keymap.map[0x50] = KEY_P;
	
	 //  (51) - Q key
	keymap.map[0x51] = KEY_Q;
	
	 //  (52) - R key
	keymap.map[0x52] = KEY_R;
	
	 // (53) - S key
	keymap.map[0x53] = KEY_S;
	
	 //  (54) - T key
	keymap.map[0x54] = KEY_T;
	
	 //  (55) - U key
	keymap.map[0x55] = KEY_U;
	
	 //  (56) - V key
	keymap.map[0x56] = KEY_V;
	
	 //  (57) - W key
	keymap.map[0x57] = KEY_W;
	
	 //  (58) - X key
	keymap.map[0x58] = KEY_X;
	
	 //  (59) - Y key
	keymap.map[0x59] = KEY_Y;
	
	 //  (5A) - Z key
	keymap.map[0x5A] = KEY_Z;
	
	 // VK_LWIN (5B) - Left Windows key (Microsoft Natural keyboard) 
	keymap.map[VK_LWIN] = KEY_LWIN;
	
	// VK_RWIN (5C) - Right Windows key (Natural keyboard)
	keymap.map[VK_RWIN] = KEY_RWIN;
	
	// VK_APPS (5D) - Applications key (Natural keyboard)
	keymap.map[VK_APPS] = KEY_APPS;
	
	// VK_SLEEP (5F) - Computer Sleep key
	keymap.map[VK_SLEEP] = KEY_NOT_MAPPED;
	
	// VK_NUMPAD0 (60) - Numeric keypad 0 key
	keymap.map[VK_NUMPAD0] = KEY_KP_0;
	
	// VK_NUMPAD1 (61) - Numeric keypad 1 key
	keymap.map[VK_NUMPAD1] = KEY_KP_1;
	
	// VK_NUMPAD2 (62) - Numeric keypad 2 key
	keymap.map[VK_NUMPAD2] = KEY_KP_2;
	
	// VK_NUMPAD3 (63) - Numeric keypad 3 key
	keymap.map[VK_NUMPAD3] = KEY_KP_3;
	
	// VK_NUMPAD4 (64) - Numeric keypad 4 key
	keymap.map[VK_NUMPAD4] = KEY_KP_4;
	
	// VK_NUMPAD5 (65) - Numeric keypad 5 key
	keymap.map[VK_NUMPAD5] = KEY_KP_5;
	
	// VK_NUMPAD6 (66) - Numeric keypad 6 key
	keymap.map[VK_NUMPAD6] = KEY_KP_6;
	
	// VK_NUMPAD7 (67) - Numeric keypad 7 key
	keymap.map[VK_NUMPAD7] = KEY_KP_7;
	
	// VK_NUMPAD8 (68) - Numeric keypad 8 key
	keymap.map[VK_NUMPAD8] = KEY_KP_8;
	
	// VK_NUMPAD9 (69) - Numeric keypad 9 key
	keymap.map[VK_NUMPAD9] = KEY_KP_9;
	
	// VK_MULTIPLY (6A) - Multiply key
	keymap.map[VK_MULTIPLY] = KEY_KP_MULTIPLY;
	
	// VK_ADD (6B) - Add key
	keymap.map[VK_ADD] = KEY_KP_ADD;
	
	// VK_SEPARATOR (6C) - Separator key
	keymap.map[VK_SEPARATOR] = KEY_KP_SEPERATOR;
	
	// VK_SUBTRACT (6D) - Subtract key
	keymap.map[VK_SUBTRACT] = KEY_KP_SUBSTRACT;
	
	// VK_DECIMAL (6E) - Decimal key
	keymap.map[VK_DECIMAL] = KEY_KP_DECIMAL;
	
	// VK_DIVIDE (6F) - Divide key
	keymap.map[VK_DIVIDE] = KEY_KP_DIVIDE;
	
	// VK_F1 (70) - F1 key
	keymap.map[VK_F1] = KEY_F1;
	
	// VK_F2 (71) - F2 key
	keymap.map[VK_F2] = KEY_F2;
	
	// VK_F3 (72) - F3 key
	keymap.map[VK_F3] = KEY_F3;
	
	// VK_F4 (73) - F4 key
	keymap.map[VK_F4] = KEY_F4;
	
	// VK_F5 (74) - F5 key
	keymap.map[VK_F5] = KEY_F5;
	
	// VK_F6 (75) - F6 key
	keymap.map[VK_F6] = KEY_F6;
	
	// VK_F7 (76) - F7 key
	keymap.map[VK_F7] = KEY_F7;
	
	// VK_F8 (77) - F8 key
	keymap.map[VK_F8] = KEY_F8;
	
	// VK_F9 (78) - F9 key
	keymap.map[VK_F9] = KEY_F9;
	
	// VK_F10 (79) - F10 key
	keymap.map[VK_F10] = KEY_F10;
	
	// VK_F11 (7A) - F11 key
	keymap.map[VK_F11] = KEY_F11;
	
	// VK_F12 (7B) - F12 key
	keymap.map[VK_F12] = KEY_F12;
	
	// VK_F13 (7C) - F13 key
	keymap.map[VK_F13] = KEY_F13;
	
	// VK_F14 (7D) - F14 key
	keymap.map[VK_F14] = KEY_F14;
	
	// VK_F15 (7E) - F15 key
	keymap.map[VK_F15] = KEY_F15;
	
	// K_F16 (7F) - F16 key
	keymap.map[VK_F16] = KEY_F16;
	
	// VK_F17 (80H) - F17 key
	keymap.map[VK_F17] = KEY_F17;
	
	// VK_F18 (81H) - F18 key
	keymap.map[VK_F18] = KEY_F18;
	
	// VK_F19 (82H) - F19 key
	keymap.map[VK_F19] = KEY_F19;
	
	// VK_F20 (83H) - F20 key
	keymap.map[VK_F20] = KEY_F20;
	
	// VK_F21 (84H) - F21 key
	keymap.map[VK_F21] = KEY_F21;
	
	// VK_F22 (85H) - F22 key
	keymap.map[VK_F22] = KEY_F22;
	
	// VK_F23 (86H) - F23 key
	keymap.map[VK_F23] = KEY_F23;
	
	// VK_F24 (87H) - F24 key
	keymap.map[VK_F24] = KEY_F24;
	
	// VK_NUMLOCK (90) - NUM LOCK key
	keymap.map[VK_NUMLOCK] = KEY_NOT_MAPPED;
	
	// VK_SCROLL (91) - SCROLL LOCK key
	keymap.map[VK_SCROLL] = KEY_NOT_MAPPED;
	
	// VK_LSHIFT (A0) - Left SHIFT key
	keymap.map[VK_LSHIFT] = KEY_LSHIFT;
	
	// VK_RSHIFT (A1) - Right SHIFT key
	keymap.map[VK_RSHIFT] = KEY_RSHIFT;
	
	// VK_LCONTROL (A2) - Left CONTROL key
	keymap.map[VK_LCONTROL] = KEY_LCONTROL;
	
	// VK_RCONTROL (A3) - Right CONTROL key
	keymap.map[VK_RCONTROL] = KEY_RCONTROL;
	
	// VK_LMENU (A4) - Left MENU key
	keymap.map[VK_LMENU] = KEY_LALT;
	
	// VK_RMENU (A5) - Right MENU key
	keymap.map[VK_RMENU] = KEY_RALT;
	
	// VK_OEM_1 (BA) - Used for miscellaneous characters; it can vary by keyboard.
	// Windows 2000/XP: For the US standard keyboard, the ';:' key 
	keymap.map[0xBA] = KEY_SEMICOLON;
	
	// VK_OEM_PLUS (BB) - Windows 2000/XP: For any country/region, the '+' key
	keymap.map[0xBB] = KEY_ASSIGN;
	
	// VK_OEM_COMMA (BC) - Windows 2000/XP: For any country/region, the ',' key
	keymap.map[0xBC] = KEY_COMMA;
	
	// VK_OEM_MINUS (BD) - Windows 2000/XP: For any country/region, the '-' key
	keymap.map[0xBD] = KEY_DASH;
	
	// VK_OEM_PERIOD (BE) - Windows 2000/XP: For any country/region, the '.' key
	keymap.map[0xBE] = KEY_DOT;
	
	// VK_OEM_2 (BF) - Used for miscellaneous characters; it can vary by keyboard.
	// Windows 2000/XP: For the US standard keyboard, the '/?' key 
	keymap.map[VK_OEM_2] = KEY_SLASH;
	
	// VK_OEM_3 (C0) - Used for miscellaneous characters; it can vary by keyboard. 
	// Windows 2000/XP: For the US standard keyboard, the '`~' key 
	keymap.map[VK_OEM_3] = KEY_TILDE;
	
	// VK_OEM_4 (DB) - Used for miscellaneous characters; it can vary by keyboard. 
	// Windows 2000/XP: For the US standard keyboard, the '[{' key
	keymap.map[VK_OEM_4] = KEY_LBRACKET;
	
	// VK_OEM_5 (DC) - Used for miscellaneous characters; it can vary by keyboard. 
	// Windows 2000/XP: For the US standard keyboard, the '\|' key
	keymap.map[VK_OEM_5] = KEY_BACKSLASH;
	
	// VK_OEM_6 (DD) - Used for miscellaneous characters; it can vary by keyboard. 
	// Windows 2000/XP: For the US standard keyboard, the ']}' key
	keymap.map[VK_OEM_6] = KEY_RBRACKET;
	
	// VK_OEM_7 (DE) - Used for miscellaneous characters; it can vary by keyboard. 
	// Windows 2000/XP: For the US standard keyboard, the 'single-quote/double-quote' key
	keymap.map[VK_OEM_7] = KEY_QUOTE;
	
	// VK_OEM_8 (DF) - Used for miscellaneous characters; it can vary by keyboard.
	keymap.map[VK_OEM_8] = KEY_NOT_MAPPED;
	
	// VK_OEM_102 (E2) - Windows 2000/XP: Either the angle bracket key or the backslash key on the RT 102-key keyboard
	keymap.map[0xE2] = KEY_NOT_MAPPED;
	
	// VK_PACKET (E7) - Windows 2000/XP: Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP
	keymap.map[0xE7] = KEY_NOT_MAPPED;
	
	// VK_ATTN (F6) - Attn key
	keymap.map[VK_ATTN] = KEY_NOT_MAPPED;
	
	// VK_CRSEL (F7) - CrSel key
	keymap.map[VK_CRSEL] = KEY_NOT_MAPPED;
	
	// VK_EXSEL (F8) - ExSel key
	keymap.map[VK_EXSEL] = KEY_NOT_MAPPED;
	
	// VK_EREOF (F9) - Erase EOF key
	keymap.map[VK_EREOF] = KEY_NOT_MAPPED;


	return &keymap;
}
