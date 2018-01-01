// Monospace 8x8 Font Definition
static const char monospaceFont[102][8] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x20 ' '
	{0x02, 0x07, 0x07, 0x02, 0x02, 0x00, 0x02, 0x00},	// 0x21 '!'
	{0x1B, 0x1B, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x22 '"'
	{0x00, 0x0A, 0x1F, 0x0A, 0x0A, 0x1F, 0x0A, 0x00},	// 0x23 '#'
	{0x02, 0x0E, 0x01, 0x06, 0x08, 0x07, 0x04, 0x00},	// 0x24 '$'
	{0x13, 0x13, 0x08, 0x04, 0x02, 0x19, 0x19, 0x00},	// 0x25 '%'
	{0x02, 0x05, 0x05, 0x02, 0x15, 0x09, 0x16, 0x00},	// 0x26 '&'
	{0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x27 '''
	{0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00},	// 0x28 '('
	{0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00},	// 0x29 ')'
	{0x00, 0x0A, 0x0E, 0x1F, 0x0E, 0x0A, 0x00, 0x00},	// 0x2A '*'
	{0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00, 0x00},	// 0x2B '+'
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x01},	// 0x2C ','
	{0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00},	// 0x2D '-'
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00},	// 0x2E '.'
	{0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00},	// 0x2F '/'
	{0x0E, 0x11, 0x19, 0x15, 0x13, 0x11, 0x0E, 0x00},	// 0x30 '0'
	{0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x07, 0x00},	// 0x31 '1'
	{0x0E, 0x11, 0x10, 0x0C, 0x02, 0x01, 0x1F, 0x00},	// 0x32 '2'
	{0x0E, 0x11, 0x10, 0x0E, 0x10, 0x11, 0x0E, 0x00},	// 0x33 '3'
	{0x08, 0x0C, 0x0A, 0x09, 0x1F, 0x08, 0x08, 0x00},	// 0x34 '4'
	{0x1F, 0x01, 0x01, 0x0F, 0x10, 0x11, 0x0E, 0x00},	// 0x35 '5'
	{0x0C, 0x02, 0x01, 0x0F, 0x11, 0x11, 0x0E, 0x00},	// 0x36 '6'
	{0x1F, 0x10, 0x08, 0x04, 0x02, 0x02, 0x02, 0x00},	// 0x37 '7'
	{0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E, 0x00},	// 0x38 '8'
	{0x0E, 0x11, 0x11, 0x1E, 0x10, 0x08, 0x06, 0x00},	// 0x39 '9'
	{0x00, 0x00, 0x03, 0x03, 0x00, 0x03, 0x03, 0x00},	// 0x3A ':'
	{0x00, 0x00, 0x03, 0x03, 0x00, 0x03, 0x03, 0x01},	// 0x3B ';'
	{0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x00},	// 0x3C '<'
	{0x00, 0x00, 0x1F, 0x00, 0x00, 0x1F, 0x00, 0x00},	// 0x3D '='
	{0x01, 0x02, 0x04, 0x08, 0x04, 0x02, 0x01, 0x00},	// 0x3E '>'
	{0x0E, 0x11, 0x10, 0x0C, 0x04, 0x00, 0x04, 0x00},	// 0x3F '?'
	{0x0E, 0x11, 0x1D, 0x15, 0x1D, 0x01, 0x0E, 0x00},	// 0x40 '@'
	{0x0E, 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x00},	// 0x41 'A'
	{0x0F, 0x11, 0x11, 0x0F, 0x11, 0x11, 0x0F, 0x00},	// 0x42 'B'
	{0x0E, 0x11, 0x01, 0x01, 0x01, 0x11, 0x0E, 0x00},	// 0x43 'C'
	{0x0F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0F, 0x00},	// 0x44 'D'
	{0x1F, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x1F, 0x00},	// 0x45 'E'
	{0x1F, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x01, 0x00},	// 0x46 'F'
	{0x0E, 0x11, 0x01, 0x1D, 0x11, 0x11, 0x1E, 0x00},	// 0x47 'G'
	{0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00},	// 0x48 'H'
	{0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x07, 0x00},	// 0x49 'I'
	{0x10, 0x10, 0x10, 0x10, 0x11, 0x11, 0x0E, 0x00},	// 0x4A 'J'
	{0x11, 0x09, 0x05, 0x03, 0x05, 0x09, 0x11, 0x00},	// 0x4B 'K'
	{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1F, 0x00},	// 0x4C 'L'
	{0x11, 0x1B, 0x15, 0x11, 0x11, 0x11, 0x11, 0x00},	// 0x4D 'M'
	{0x11, 0x13, 0x15, 0x19, 0x11, 0x11, 0x11, 0x00},	// 0x4E 'N'
	{0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00},	// 0x4F 'O'
	{0x0F, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x01, 0x00},	// 0x50 'P'
	{0x0E, 0x11, 0x11, 0x11, 0x15, 0x09, 0x16, 0x00},	// 0x51 'Q'
	{0x0F, 0x11, 0x11, 0x0F, 0x09, 0x11, 0x11, 0x00},	// 0x52 'R'
	{0x0E, 0x11, 0x01, 0x0E, 0x10, 0x11, 0x0E, 0x00},	// 0x53 'S'
	{0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00},	// 0x54 'T'
	{0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00},	// 0x55 'U'
	{0x11, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x00},	// 0x56 'V'
	{0x11, 0x11, 0x15, 0x15, 0x15, 0x15, 0x0A, 0x00},	// 0x57 'W'
	{0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11, 0x00},	// 0x58 'X'
	{0x11, 0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x00},	// 0x59 'Y'
	{0x0F, 0x08, 0x04, 0x02, 0x01, 0x01, 0x0F, 0x00},	// 0x5A 'Z'
	{0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x07, 0x00},	// 0x5B '['
	{0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00},	// 0x5C '\'
	{0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x00},	// 0x5D ']'
	{0x04, 0x0A, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x5E '^'
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F},	// 0x5F '_'
	{0x03, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x60 '`'
	{0x00, 0x00, 0x0E, 0x10, 0x1E, 0x11, 0x1E, 0x00},	// 0x61 'a'
	{0x01, 0x01, 0x0F, 0x11, 0x11, 0x11, 0x0F, 0x00},	// 0x62 'b'
	{0x00, 0x00, 0x0E, 0x11, 0x01, 0x11, 0x0E, 0x00},	// 0x63 'c'
	{0x10, 0x10, 0x1E, 0x11, 0x11, 0x11, 0x1E, 0x00},	// 0x64 'd'
	{0x00, 0x00, 0x0E, 0x11, 0x0F, 0x01, 0x0E, 0x00},	// 0x65 'e'
	{0x0C, 0x02, 0x02, 0x0F, 0x02, 0x02, 0x02, 0x00},	// 0x66 'f'
	{0x00, 0x00, 0x1E, 0x11, 0x11, 0x1E, 0x10, 0x0E},	// 0x67 'g'
	{0x01, 0x01, 0x07, 0x09, 0x09, 0x09, 0x09, 0x00},	// 0x68 'h'
	{0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00},	// 0x69 'i'
	{0x08, 0x00, 0x0C, 0x08, 0x08, 0x08, 0x09, 0x06},	// 0x6A 'j'
	{0x01, 0x01, 0x09, 0x05, 0x03, 0x05, 0x09, 0x00},	// 0x6B 'k'
	{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00},	// 0x6C 'l'
	{0x00, 0x00, 0x0B, 0x15, 0x15, 0x11, 0x11, 0x00},	// 0x6D 'm'
	{0x00, 0x00, 0x07, 0x09, 0x09, 0x09, 0x09, 0x00},	// 0x6E 'n'
	{0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00},	// 0x6F 'o'
	{0x00, 0x00, 0x0F, 0x11, 0x11, 0x11, 0x0F, 0x01},	// 0x70 'p'
	{0x00, 0x00, 0x1E, 0x11, 0x11, 0x11, 0x1E, 0x10},	// 0x71 'q'
	{0x00, 0x00, 0x0D, 0x12, 0x02, 0x02, 0x07, 0x00},	// 0x72 'r'
	{0x00, 0x00, 0x0E, 0x01, 0x0E, 0x10, 0x0E, 0x00},	// 0x73 's'
	{0x00, 0x02, 0x0F, 0x02, 0x02, 0x0A, 0x04, 0x00},	// 0x74 't'
	{0x00, 0x00, 0x11, 0x11, 0x11, 0x19, 0x16, 0x00},	// 0x75 'u'
	{0x00, 0x00, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x00},	// 0x76 'v'
	{0x00, 0x00, 0x11, 0x11, 0x15, 0x1F, 0x0A, 0x00},	// 0x77 'w'
	{0x00, 0x00, 0x09, 0x09, 0x06, 0x09, 0x09, 0x00},	// 0x78 'x'
	{0x00, 0x00, 0x09, 0x09, 0x09, 0x0E, 0x04, 0x03},	// 0x79 'y'
	{0x00, 0x00, 0x0F, 0x08, 0x06, 0x01, 0x0F, 0x00},	// 0x7A 'z'
	{0x0C, 0x02, 0x02, 0x03, 0x02, 0x02, 0x0C, 0x00},	// 0x7B '{'
	{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00},	// 0x7C '|'
	{0x03, 0x04, 0x04, 0x0C, 0x04, 0x04, 0x03, 0x00},	// 0x7D '}'
	{0x0A, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x7E '~'
	/* the following are special characters needed */
	{0x0A, 0x00, 0x0E, 0x11, 0x1F, 0x11, 0x11, 0x00},	// 0xC4 'Ä'
	{0x0A, 0x00, 0x0E, 0x10, 0x1E, 0x11, 0x1E, 0x00},	// 0xE4 'ä'
	{0x0A, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00},	// 0xD6 'Ö'
	{0x0A, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00},	// 0xF6 'ö'
	{0x0A, 0x00, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00},	// 0xDC 'Ü'
	{0x0A, 0x00, 0x11, 0x11, 0x11, 0x19, 0x16, 0x00},	// 0xFC 'ü'
	{0x06, 0x09, 0x09, 0x05, 0x09, 0x11, 0x0D, 0x00}	// 0xDF 'ß'
};
static const uint8_t monospaceFontWidth[102] = {
	4,	// 0x20 ' '
	4,	// 0x21 '!'
	6,	// 0x22 '"'
	6,	// 0x23 '#'
	5,	// 0x24 '$'
	6,	// 0x25 '%'
	6,	// 0x26 '&'
	3,	// 0x27 '''
	3,	// 0x28 '('
	3,	// 0x29 ')'
	6,	// 0x2A '*'
	6,	// 0x2B '+'
	3,	// 0x2C ','
	6,	// 0x2D '-'
	3,	// 0x2E '.'
	6,	// 0x2F '/'
	6,	// 0x30 '0'
	4,	// 0x31 '1'
	6,	// 0x32 '2'
	6,	// 0x33 '3'
	6,	// 0x34 '4'
	6,	// 0x35 '5'
	6,	// 0x36 '6'
	6,	// 0x37 '7'
	6,	// 0x38 '8'
	6,	// 0x39 '9'
	3,	// 0x3A ':'
	3,	// 0x3B ';'
	5,	// 0x3C '<'
	6,	// 0x3D '='
	5,	// 0x3E '>'
	6,	// 0x3F '?'
	6,	// 0x40 '@'
	6,	// 0x41 'A'
	6,	// 0x42 'B'
	6,	// 0x43 'C'
	6,	// 0x44 'D'
	6,	// 0x45 'E'
	6,	// 0x46 'F'
	6,	// 0x47 'G'
	6,	// 0x48 'H'
	4,	// 0x49 'I'
	6,	// 0x4A 'J'
	6,	// 0x4B 'K'
	6,	// 0x4C 'L'
	6,	// 0x4D 'M'
	6,	// 0x4E 'N'
	6,	// 0x4F 'O'
	6,	// 0x50 'P'
	6,	// 0x51 'Q'
	6,	// 0x52 'R'
	6,	// 0x53 'S'
	6,	// 0x54 'T'
	6,	// 0x55 'U'
	6,	// 0x56 'V'
	6,	// 0x57 'W'
	6,	// 0x58 'X'
	6,	// 0x59 'Y'
	5,	// 0x5A 'Z'
	4,	// 0x5B '['
	6,	// 0x5C '\'
	4,	// 0x5D ']'
	6,	// 0x5E '^'
	6,	// 0x5F '_'
	3,	// 0x60 '`'
	6,	// 0x61 'a'
	6,	// 0x62 'b'
	6,	// 0x63 'c'
	6,	// 0x64 'd'
	6,	// 0x65 'e'
	5,	// 0x66 'f'
	6,	// 0x67 'g'
	5,	// 0x68 'h'
	3,	// 0x69 'i'
	5,	// 0x6A 'j'
	5,	// 0x6B 'k'
	3,	// 0x6C 'l'
	6,	// 0x6D 'm'
	5,	// 0x6E 'n'
	6,	// 0x6F 'o'
	6,	// 0x70 'p'
	6,	// 0x71 'q'
	6,	// 0x72 'r'
	6,	// 0x73 's'
	5,	// 0x74 't'
	6,	// 0x75 'u'
	6,	// 0x76 'v'
	6,	// 0x77 'w'
	5,	// 0x78 'x'
	5,	// 0x79 'y'
	5,	// 0x7A 'z'
	5,	// 0x7B '{'
	2,	// 0x7C '|'
	5,	// 0x7D '}'
	5,	// 0x7E '~'
	/* special characters */
	6,	// 0xC4 'Ä'
	6,	// 0xE4 'ä'
	6,	// 0xD6 'Ö'
	6,	// 0xF6 'ö'
	6,	// 0xDC 'Ü'
	6,	// 0xFC 'ü'
	6	// 0xDF 'ß'
};


/*
// EVjo.in UG logo definition
#define imageWidth 120
#define imageHeight 39
static const uint8_t imageBits[] = {
	0x00, 0x28, 0x00, 0x04, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x80, 0xFF, 0x03, 0x0F, 0xF8, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x07, 0x0F, 0xFC, 0x03, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x0F, 
	0x0F, 0xFC, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0xF0, 0x83, 0x0F, 0x0F, 0x9C, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xFE, 0x00, 0x00, 0xF8, 0x00, 0x0F, 0x0F, 0x8E, 0xC7, 0x00, 0x00, 0x00, 
	0x60, 0x00, 0x00, 0xFF, 0x81, 0x00, 0xF8, 0x00, 0x9F, 0x0F, 0x8E, 0xE7, 
	0x01, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xC7, 0xFB, 0x03, 0x78, 0x00, 0x8F, 
	0x0F, 0x8E, 0xF7, 0x03, 0x00, 0x00, 0xF8, 0x00, 0x80, 0x83, 0xFF, 0x07, 
	0x78, 0x00, 0x8F, 0x07, 0x9E, 0xF7, 0x01, 0x00, 0x00, 0xF8, 0x00, 0x80, 
	0x01, 0xFF, 0x1F, 0xF8, 0x00, 0x87, 0x0F, 0x9C, 0xE3, 0x00, 0x00, 0x00, 
	0x70, 0x00, 0x80, 0x03, 0xFE, 0x1F, 0xF0, 0x01, 0x80, 0x07, 0xDC, 0x03, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xFF, 0x1F, 0xE0, 0x1F, 0x80, 
	0x07, 0xFC, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xFF, 0x1F, 
	0xE0, 0x1F, 0x80, 0x07, 0xF8, 0xE3, 0xC0, 0x0F, 0x00, 0x38, 0x1C, 0x1E, 
	0x07, 0xFF, 0x3F, 0xF0, 0x1F, 0x80, 0x0F, 0xF0, 0xFF, 0xE1, 0x1F, 0x00, 
	0x38, 0x3C, 0x1F, 0x0E, 0xFF, 0x3F, 0xFC, 0x01, 0x80, 0x07, 0xE0, 0xFF, 
	0xF0, 0x3F, 0x00, 0x3C, 0x9C, 0x1F, 0x0E, 0xFE, 0xF3, 0x3E, 0x00, 0x80, 
	0x0F, 0xF0, 0xFF, 0xF8, 0x3E, 0x00, 0x3C, 0xDE, 0x1F, 0x1C, 0xFE, 0xE1, 
	0x1E, 0x00, 0x80, 0x07, 0xF0, 0xF0, 0x78, 0x3E, 0x02, 0x3C, 0xDE, 0x1F, 
	0x1C, 0xFC, 0x41, 0x1F, 0x00, 0x00, 0x0F, 0x78, 0xF0, 0x78, 0xFE, 0x07, 
	0x3C, 0xFE, 0x0E, 0x0C, 0xF8, 0x03, 0x0F, 0x00, 0x80, 0x0F, 0x7C, 0xF0, 
	0x3C, 0xFC, 0x07, 0x1C, 0x7E, 0x0E, 0x0E, 0x30, 0x0F, 0x1F, 0x00, 0x00, 
	0x0F, 0x3C, 0xF0, 0x78, 0xF8, 0x03, 0x1E, 0x3E, 0x0F, 0x0F, 0x00, 0x0E, 
	0x1F, 0x00, 0x60, 0x1F, 0x1E, 0x70, 0x3E, 0x38, 0x38, 0x1E, 0x3F, 0x8E, 
	0x07, 0x00, 0x08, 0x7E, 0x00, 0x7E, 0xBF, 0x0F, 0x78, 0x7F, 0x3C, 0x7C, 
	0x1C, 0x3F, 0xCF, 0x03, 0x00, 0x00, 0xFE, 0xFF, 0x7F, 0xFE, 0x0F, 0xF0, 
	0xFF, 0x3E, 0x7E, 0xFE, 0x1F, 0xFF, 0x01, 0x00, 0x00, 0xFC, 0xFF, 0x3F, 
	0xFE, 0x03, 0xF8, 0xF3, 0x1F, 0x7C, 0xFC, 0x1F, 0xFF, 0x00, 0x00, 0x00, 
	0xF0, 0xFF, 0x0F, 0xFC, 0x01, 0xF8, 0xE1, 0x0F, 0x7C, 0xFC, 0x1E, 0x7E, 
	0x00, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x30, 0x00, 0x78, 0x80, 0x03, 0x38, 
	0x30, 0x08, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x3F, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x1D, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xE0, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x70, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x0E, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0E, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x38, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xF8, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
*/


// Large sized font definition for numbers and 'A'
// Width can be reduced to 3 bytes, if letter A is modified so that it is more narrow. currently the only wide character beyond 3 bytes (24 pixels)
static const uint8_t latoFontBits[12][112] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	// 0x20 ' '
	{ 0x00, 0x3F, 0x00, 0x00, 0xC0, 0xFF, 0x00, 0x00, 0xE0, 0xFF, 0x01, 0x00, 0xF0, 0xC0, 0x03, 0x00, 0x78, 0x80, 0x07, 0x00, 0x38, 0x00, 0x07, 0x00, 0x3C, 0x00, 0x0F, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x3C, 0x00, 0x0F, 0x00, 0x38, 0x00, 0x07, 0x00, 0x78, 0x80, 0x07, 0x00, 0xF0, 0xC0, 0x03, 0x00, 0xE0, 0xFF, 0x01, 0x00, 0xC0, 0xFF, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00 },	// 0x30 '0'
	{ 0x00, 0x78, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0xC0, 0x7B, 0x00, 0x00, 0xE0, 0x79, 0x00, 0x00, 0xF0, 0x78, 0x00, 0x00, 0x60, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0xE0, 0xFF, 0x0F, 0x00, 0xE0, 0xFF, 0x0F, 0x00, 0xE0, 0xFF, 0x0F, 0x00 },	// 0x31 '1'
	{ 0x00, 0x7F, 0x00, 0x00, 0xC0, 0xFF, 0x00, 0x00, 0xE0, 0xFF, 0x03, 0x00, 0xF0, 0xC0, 0x03, 0x00, 0x78, 0x80, 0x07, 0x00, 0x78, 0x00, 0x07, 0x00, 0x38, 0x00, 0x07, 0x00, 0x38, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x80, 0x0F, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xF0, 0x01, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x0F, 0x00, 0xFC, 0xFF, 0x0F, 0x00, 0xFC, 0xFF, 0x0F, 0x00 },	// 0x32 '2'
	{ 0x00, 0x7F, 0x00, 0x00, 0xC0, 0xFF, 0x01, 0x00, 0xE0, 0xFF, 0x03, 0x00, 0xF0, 0x81, 0x07, 0x00, 0x70, 0x00, 0x07, 0x00, 0x78, 0x00, 0x0F, 0x00, 0x38, 0x00, 0x0F, 0x00, 0x30, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0xFC, 0x03, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x18, 0x00, 0x0E, 0x00, 0x3C, 0x00, 0x0E, 0x00, 0x38, 0x00, 0x0F, 0x00, 0x78, 0x00, 0x07, 0x00, 0xF0, 0xC0, 0x07, 0x00, 0xF0, 0xFF, 0x03, 0x00, 0xC0, 0xFF, 0x01, 0x00, 0x00, 0x3F, 0x00, 0x00 },	// 0x33 '3'
	{ 0x00, 0xC0, 0x01, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0xF0, 0x01, 0x00, 0x00, 0xF8, 0x01, 0x00, 0x00, 0xF8, 0x01, 0x00, 0x00, 0xDC, 0x01, 0x00, 0x00, 0xDE, 0x01, 0x00, 0x00, 0xCE, 0x01, 0x00, 0x00, 0xC7, 0x01, 0x00, 0x80, 0xC7, 0x01, 0x00, 0xC0, 0xC3, 0x01, 0x00, 0xC0, 0xC1, 0x01, 0x00, 0xE0, 0xC0, 0x01, 0x00, 0xF0, 0xC0, 0x01, 0x00, 0x78, 0xC0, 0x01, 0x00, 0x38, 0xC0, 0x01, 0x00, 0x3C, 0xC0, 0x01, 0x00, 0x1E, 0xC0, 0x01, 0x00, 0xFE, 0xFF, 0x1F, 0x00, 0xFE, 0xFF, 0x1F, 0x00, 0xFC, 0xFF, 0x1F, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00 },	// 0x34 '4'
	{ 0xC0, 0xFF, 0x07, 0x00, 0xE0, 0xFF, 0x07, 0x00, 0xE0, 0xFF, 0x01, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0xF0, 0xFF, 0x00, 0x00, 0xE0, 0xFF, 0x01, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x80, 0x07, 0x00, 0x08, 0xC0, 0x03, 0x00, 0x3C, 0xE0, 0x01, 0x00, 0xFC, 0xFF, 0x00, 0x00, 0xF0, 0x7F, 0x00, 0x00, 0xC0, 0x1F, 0x00, 0x00 },	// 0x35 '5'
	{ 0x00, 0xE0, 0x01, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xE0, 0x39, 0x00, 0x00, 0xE0, 0xFF, 0x01, 0x00, 0xF0, 0xFF, 0x03, 0x00, 0xF8, 0xC1, 0x07, 0x00, 0x78, 0x80, 0x07, 0x00, 0x38, 0x00, 0x0F, 0x00, 0x3C, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x3C, 0x00, 0x0E, 0x00, 0x38, 0x00, 0x0F, 0x00, 0x78, 0x80, 0x07, 0x00, 0xF0, 0xC0, 0x07, 0x00, 0xE0, 0xFF, 0x03, 0x00, 0xC0, 0xFF, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00 },	// 0x36 '6'
	{ 0xFC, 0xFF, 0x1F, 0x00, 0xFC, 0xFF, 0x1F, 0x00, 0xFC, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00 },	// 0x37 '7'
	{ 0x00, 0x3F, 0x00, 0x00, 0xC0, 0xFF, 0x00, 0x00, 0xE0, 0xFF, 0x01, 0x00, 0xF0, 0xC0, 0x03, 0x00, 0x78, 0x80, 0x07, 0x00, 0x38, 0x00, 0x07, 0x00, 0x38, 0x00, 0x07, 0x00, 0x38, 0x00, 0x07, 0x00, 0x38, 0x00, 0x07, 0x00, 0x78, 0x80, 0x07, 0x00, 0x70, 0x80, 0x03, 0x00, 0xF0, 0xE1, 0x03, 0x00, 0xC0, 0xFF, 0x00, 0x00, 0xC0, 0xFF, 0x00, 0x00, 0xF0, 0xFF, 0x01, 0x00, 0xF8, 0xC0, 0x07, 0x00, 0x78, 0x80, 0x07, 0x00, 0x3C, 0x00, 0x0F, 0x00, 0x1C, 0x00, 0x0F, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x0F, 0x00, 0x3C, 0x00, 0x0F, 0x00, 0x38, 0x80, 0x07, 0x00, 0xF8, 0xC0, 0x07, 0x00, 0xF0, 0xFF, 0x03, 0x00, 0xE0, 0xFF, 0x01, 0x00, 0x80, 0x7F, 0x00, 0x00 },	// 0x38 '8'
	{ 0x00, 0x7E, 0x00, 0x00, 0x80, 0xFF, 0x01, 0x00, 0xE0, 0xFF, 0x03, 0x00, 0xF0, 0x81, 0x07, 0x00, 0xF0, 0x00, 0x07, 0x00, 0x78, 0x00, 0x0E, 0x00, 0x38, 0x00, 0x0E, 0x00, 0x38, 0x00, 0x0E, 0x00, 0x38, 0x00, 0x0E, 0x00, 0x38, 0x00, 0x0E, 0x00, 0x38, 0x00, 0x0E, 0x00, 0x78, 0x00, 0x0F, 0x00, 0xF0, 0x00, 0x0F, 0x00, 0xF0, 0xC1, 0x0F, 0x00, 0xE0, 0xFF, 0x07, 0x00, 0xC0, 0xFF, 0x07, 0x00, 0x00, 0xCE, 0x03, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00 },	// 0x39 '9'
	{ 0x00, 0x78, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0xFE, 0x01, 0x00, 0x00, 0xEE, 0x01, 0x00, 0x00, 0xCE, 0x01, 0x00, 0x00, 0xCF, 0x03, 0x00, 0x00, 0xC7, 0x03, 0x00, 0x80, 0x87, 0x07, 0x00, 0x80, 0x87, 0x07, 0x00, 0x80, 0x03, 0x07, 0x00, 0xC0, 0x03, 0x0F, 0x00, 0xC0, 0x03, 0x0F, 0x00, 0xE0, 0x01, 0x0E, 0x00, 0xE0, 0x01, 0x1E, 0x00, 0xE0, 0x00, 0x1E, 0x00, 0xF0, 0x00, 0x3C, 0x00, 0xF0, 0xFF, 0x3F, 0x00, 0xF8, 0xFF, 0x3F, 0x00, 0xF8, 0xFF, 0x7F, 0x00, 0x78, 0x00, 0x78, 0x00, 0x3C, 0x00, 0xF0, 0x00, 0x3C, 0x00, 0xF0, 0x00, 0x1C, 0x00, 0xE0, 0x00, 0x1E, 0x00, 0xE0, 0x01, 0x1E, 0x00, 0xE0, 0x01, 0x0F, 0x00, 0xC0, 0x03 }	// 0x41 'A'
};
static const uint8_t latoGlyphWidth[12] = {
	16,	// 0x20 ' '
	23,	// 0x30 '0'
	22,	// 0x31 '1'
	22,	// 0x32 '2'
	22,	// 0x33 '3'
	23,	// 0x34 '4'
	21,	// 0x35 '5'
	22,	// 0x36 '6'
	23,	// 0x37 '7'
	22,	// 0x38 '8'
	22,	// 0x39 '9'
	28	// 0x41 'A'
};
static const int8_t latoGlyphOffset[12] = {
	0,	// 0x20 ' '
	-1,	// 0x30 '0'
	-4,	// 0x31 '1'
	-2,	// 0x32 '2'
	-2,	// 0x33 '3'
	-1,	// 0x34 '4'
	-2,	// 0x35 '5'
	-2,	// 0x36 '6'
	-2,	// 0x37 '7'
	-2,	// 0x38 '8'
	-3,	// 0x39 '9'
	0	// 0x41 'A'
};
static const uint8_t latoFontHeight = 28;
static const uint8_t latoFontWidth = 30;