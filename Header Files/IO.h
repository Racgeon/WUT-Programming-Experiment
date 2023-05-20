#include "CardList.h"
#include "administratorList.h"

CardList loadCard(CardList L, const char* fileName);

status storeCard(CardList L, const char *fileName);

AdministratorList loadAdmin(AdministratorList L, const char *fileName);

status storeAdmin(AdministratorList L, const char *fileName);