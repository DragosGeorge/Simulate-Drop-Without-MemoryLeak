ACMD(do_drop)
{
    char arg1[256], arg2[256];

    two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

    if (!*arg1 || !*arg2)
    {
        ch->ChatPacket(CHAT_TYPE_INFO, "Syntax: drop_simul <mob vnum> <count>");
        return;
    }

    DWORD vnum = 0, loopCount = 0;
    str_to_number(vnum, arg1);
    str_to_number(loopCount, arg2);

    std::unordered_map<DWORD, long long> givenItems;

    LPCHARACTER pkAttacker = CHARACTER_MANAGER::instance().SpawnMobRandomPosition(vnum, ch->GetMapIndex());
    if (!pkAttacker)
        return;

    for (DWORD count = 0; count < loopCount; ++count)
    {
        std::vector<LPITEM> vecItems;
        if (ITEM_MANAGER::instance().CreateDropItem(pkAttacker, ch, vecItems))
        {
            for (LPITEM item : vecItems)
            {
                if (!item)
                {
                    sys_err("item null in vector");
                    continue;
                }

                givenItems[item->GetVnum()] += item->GetCount();
                sys_log(0, "DROP_ITEM_SIMULATE: %s by %s", item->GetName(), ch->GetName());
            }
        }
    }

    ch->ChatPacket(CHAT_TYPE_PARTY, "############### |cFF6d8cf2|H|h%dx %s|h|r DROP SIMULATION ###############", loopCount, pkAttacker->GetName());

    for (const auto& info : givenItems)
    {
        DWORD dwItemVnum = info.first;
        long long itemCount = info.second;
        LPITEM pItem = ITEM_MANAGER::instance().CreateItem(dwItemVnum, itemCount, 0, true);

        if (pItem)
        {
            const char* color = (pItem->GetVnum() == quest::CQuestManager::instance().GetEventFlag("high_item")) ? "|cFFf77f77" : "|cFFf5ef78";
            ch->ChatPacket(CHAT_TYPE_PARTY, "Simulated item %s|H|h%s|h|r, %d pieces", color, pItem->GetName(), itemCount);
            M2_DESTROY_ITEM(pItem);
        }
    }

    M2_DESTROY_CHARACTER(pkAttacker);
}