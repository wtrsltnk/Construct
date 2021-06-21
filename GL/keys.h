#ifndef KEYS_H_
#define KEYS_H_

#define MAX_KEYS 128

typedef enum eKeyState
{
	eUnpressed,
	ePressed,
	eDisabled
} eKeyState;

typedef enum eKeys
{
	// NUMBERS
	KEY_0 = 0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	
	// LETTERS
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	
	// SPECIAL LETTERS
	KEY_SEMICOLON,		// ;:
	KEY_COMMA,			// ,<
	KEY_DOT,			// .>
	KEY_QUOTE,			// '"
	KEY_DASH,			// -_
	KEY_BACKSLASH,		// \|
	KEY_TILDE,			// `~
	KEY_SLASH,			// /?
	KEY_ASSIGN,			// =+
	KEY_LBRACKET,		// [{
	KEY_RBRACKET,		// ]}
	
	// SPECIAL KEYS
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_RETURN,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LALT,
	KEY_RALT,
	KEY_CAPS,
	KEY_ESCAPE,
	KEY_SPACE,
	KEY_PGUP,
	KEY_PGDOWN,
	KEY_HOME,
	KEY_END,
	KEY_INSERT,
	KEY_DELETE,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_PAUSE,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APPS,
	KEY_PRTSC,
	KEY_PRINT,
	
	// FUNCTION KEYS
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_F13,
	KEY_F14,
	KEY_F15,
	KEY_F16,
	KEY_F17,
	KEY_F18,
	KEY_F19,
	KEY_F20,
	KEY_F21,
	KEY_F22,
	KEY_F23,
	KEY_F24,
	
	// KEYPAD KEYS
	KEY_KP_0,
	KEY_KP_1,
	KEY_KP_2,
	KEY_KP_3,
	KEY_KP_4,
	KEY_KP_5,
	KEY_KP_6,
	KEY_KP_7,
	KEY_KP_8,
	KEY_KP_9,
	KEY_KP_MULTIPLY,
	KEY_KP_ADD,
	KEY_KP_SEPERATOR,
	KEY_KP_SUBSTRACT,
	KEY_KP_DECIMAL,
	KEY_KP_DIVIDE,
	KEY_KP_ENTER,
	
	// MOUSE BUTTONS
	KEY_MOUSE_L,
	KEY_MOUSE_R,
	KEY_MOUSE_M,
	KEY_MOUSE_WHEELUP,
	KEY_MOUSE_WHEELDOWN,
	KEY_MOUSE_4,
	KEY_MOUSE_5,
	KEY_MOUSE_6,
	KEY_MOUSE_7,
	
	//ALWAYS US THIS AS LAST KEY
	KEY_NOT_MAPPED
} eKeys;

typedef struct tKeyMap
{
	unsigned int mapsize;
	eKeys* map;
	
} tKeyMap;

#endif /*KEYS_H_*/