#pragma once
#include "global.h"

struct Administrator{
    char id[19];
    char password[9];
    int authority;
};

Administrator * createEmptyAdministrator();

Administrator * createNewAdministrator(char *id, char *password);

Administrator * createAdministratorWithAuth(char *id, char *password,int auth);

int verifyPassword(Administrator* a, Administrator* b);

int idEquals(Administrator *a, Administrator* b);
