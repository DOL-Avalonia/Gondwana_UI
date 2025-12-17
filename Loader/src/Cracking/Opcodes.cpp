#include "Opcodes.h"

namespace Gondwana::Loader {

const std::vector<Instruction> Instructions = {
	{ "CALL"    , { 0xFF, 0x15 } },
	{ "JMP"     , { 0xFF, 0x25 } },
	{ "PUSH"    , { 0xFF, 0x35 } },
	{ "MOV ECX" , { 0x8B, 0x0D } },
	{ "MOV EDX" , { 0x8B, 0x15 } },
	{ "MOV ESP" , { 0x8B, 0x25 } },
	{ "MOV EBP" , { 0x8B, 0x2D } },
	{ "MOV ESI" , { 0x8B, 0x35 } },
	{ "MOV EDI" , { 0x8B, 0x3D } },
	{ "MOV EAX" , { 0xA1 } },
	{ "CMP EAX" , { 0x3B, 0x05 } },
	{ "CMP EBX" , { 0x3B, 0x1D } },
	{ "CMP ECX" , { 0x3B, 0x0D } },
	{ "CMP EDX" , { 0x3B, 0x15 } },
	{ "CMP ESP" , { 0x3B, 0x25 } },
	{ "CMP ESI" , { 0x3B, 0x35 } },
	{ "CMP EDI" , { 0x3B, 0x3D } }
};

}

