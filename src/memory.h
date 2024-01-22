#include "structs.h"

void freeTokens(Token *token);
void freeCommandPart(CommandPart part);
void freeCommandList(CommandList list);
void freeIORedirect(IORedirect io);
void freeCommands(Command *commands, int size);
void freeInput(Input *input);
