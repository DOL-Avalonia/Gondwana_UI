#ifndef GONDWANA_GAMEDATA_CRAFTING_H
#define GONDWANA_GAMEDATA_CRAFTING_H

namespace Gondwana::GameData::Crafting
{

struct Crafting
{
	unsigned int StringId;
	unsigned short CraftId;
	unsigned short IconId;
	unsigned char CraftingData[400];
};

extern Crafting Cooking;
extern Crafting Alchemy;

}

#endif // GONDWANA_GAMEDATA_CRAFTING_H

