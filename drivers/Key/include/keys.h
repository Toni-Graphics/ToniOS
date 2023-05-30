#ifndef _KEYBOARD_KEYS
#define _KEYBOARD_KEYS

char* normal_codes[256] = {
  "ERROR", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", 
  "-", "=", "BACKSPACE", "\t", "q", "w", "e", "r", "t", "y", "u", 
  "i", "o", "p", "[", "]", "ENTER", "CTRL", "a", "s", "d", "f", 
  "g", "h", "j", "k", "l", ";", "'", "`", "LEFT_SHIFT", "\\", "z", "x", 
  "c", "v", "b", "n", "m", ",", ".", "/", "RIGHT_SHIFT", "*", "LEFT_ALT", 
  " ", "CAPS_LOCK", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", 
  "F9", "F10", "NUM_LOCK", "SCROLL_LOCK", "7", "8", "9", "-", "4", "5", 
  "6", "+", "1", "2", "3", "0", ".", "ERROR", "ERROR", "F11", "F12", 
  "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", 
  "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "CTRL", 
  "/", "PRT_SCR", "RIGHT_ALT", "ERROR", "HOME", "UP_ARROW", "PAGE_UP", 
  "LEFT_ARROW", "RIGHT_ARROW", "END", "DOWN_ARROW", "PAGE_DOWN", "INSERT", 
  "DELETE", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", 
  "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", 
  "ERROR", "PAUSE"
};

char* shiftcodes[256] = {
  "ERROR", "ESC", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", 
  "BACKSPACE", "\t", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}",
   "ENTER", "CTRL", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", 
   "~", "LEFT_SHIFT", "|", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", 
   "RIGHT_SHIFT", "*", "LEFT_ALT", " ", "CAPS_LOCK", "F1", "F2", "F3", "F4", 
   "F5", "F6", "F7", "F8", "F9", "F10", "NUM_LOCK", "SCROLL_LOCK", "7", "8", "9", 
   "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "ERROR", "ERROR", "F11", 
   "F12", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", 
   "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "CTRL", "/", "PRT_SCR", 
   "RIGHT_ALT", "ERROR", "HOME", "UP_ARROW", "PAGE_UP", "LEFT_ARROW", "RIGHT_ARROW", 
   "END", "DOWN_ARROW", "PAGE_DOWN", "INSERT", "DELETE", "ERROR", "ERROR", "ERROR", 
   "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", 
   "ERROR", "ERROR", "ERROR", "ERROR", "PAUSE"
};

#endif