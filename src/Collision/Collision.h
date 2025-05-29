#pragma once
#include "Objects/World.h"

void CreateContacts(const bodies_t& bodies, contacts_t& contacts);

void SeparateContacts(contacts_t& contacts);