Search and delete this:

SET_OVER_TIME(this, OT_NONE);

Search and delete this:

if (g_bChinaIntoxicationCheck)
{
    if (IsOverTime(OT_NONE))
    {
        dev_log(LOG_DEB0, "<EXP_LOG> %s = NONE", GetName());
    }
    else if (IsOverTime(OT_3HOUR))
    {
        amount = (amount / 2);
        dev_log(LOG_DEB0, "<EXP_LOG> %s = 3HOUR", GetName());
    }
    else if (IsOverTime(OT_5HOUR))
    {
        amount = 0;
        dev_log(LOG_DEB0, "<EXP_LOG> %s = 5HOUR", GetName());
    }
}

Search and delete this:

if (g_bChinaIntoxicationCheck && amount > 0)
{
    if (IsOverTime(OT_NONE))
    {
        dev_log(LOG_DEB0, "<GOLD_LOG> %s = NONE", GetName());
    }
    else if (IsOverTime(OT_3HOUR))
    {
        amount = (amount / 2);
        dev_log(LOG_DEB0, "<GOLD_LOG> %s = 3HOUR", GetName());
    }
    else if (IsOverTime(OT_5HOUR))
    {
        amount = 0;
        dev_log(LOG_DEB0, "<GOLD_LOG> %s = 5HOUR", GetName());
    }
}

Search and delete this:

if (g_bChinaIntoxicationCheck)
{
    if (pkChrCauser->IsOverTime(OT_3HOUR))
    {
        sys_log(0, "Teen OverTime : name = %s, hour = %d)", pkChrCauser->GetName(), 3);
        return;
    }
    else if (pkChrCauser->IsOverTime(OT_5HOUR))
    {
        sys_log(0, "Teen OverTime : name = %s, hour = %d)", pkChrCauser->GetName(), 5);
        return;
    }
}