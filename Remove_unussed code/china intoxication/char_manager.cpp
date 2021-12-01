Search and delete this:

//PREVENT_TOXICATION_FOR_CHINA
if (g_bChinaIntoxicationCheck)
{
    if (ch->IsOverTime(OT_3HOUR))
    {
        if (ch && ch->GetPremiumRemainSeconds(PREMIUM_ITEM) > 0)
            return m_iMobItemRatePremium / 2;
        return m_iMobItemRate / 2;
    }
    else if (ch->IsOverTime(OT_5HOUR))
    {
        return 0;
    }
}
//END_PREVENT_TOXICATION_FOR_CHINA

Search and delete this:

//PREVENT_TOXICATION_FOR_CHINA
if (g_bChinaIntoxicationCheck)
{
    if (ch->IsOverTime(OT_3HOUR))
    {
        if (ch && ch->GetPremiumRemainSeconds(PREMIUM_GOLD) > 0)
            return m_iMobGoldAmountRatePremium / 2;
        return m_iMobGoldAmountRate / 2;
    }
    else if (ch->IsOverTime(OT_5HOUR))
    {
        return 0;
    }
}
//END_PREVENT_TOXICATION_FOR_CHINA

Search and delete this:

//PREVENT_TOXICATION_FOR_CHINA
if (g_bChinaIntoxicationCheck)
{
    if (ch->IsOverTime(OT_3HOUR))
    {
        if (ch && ch->GetPremiumRemainSeconds(PREMIUM_GOLD) > 0)
            return m_iMobGoldDropRatePremium / 2;
        return m_iMobGoldDropRate / 2;
    }
    else if (ch->IsOverTime(OT_5HOUR))
    {
        return 0;
    }
}
//END_PREVENT_TOXICATION_FOR_CHINA

Search and delete this:

//PREVENT_TOXICATION_FOR_CHINA
if (g_bChinaIntoxicationCheck)
{
    if (ch->IsOverTime(OT_3HOUR))
    {
        if (ch && ch->GetPremiumRemainSeconds(PREMIUM_EXP) > 0)
            return m_iMobExpRatePremium / 2;
        return m_iMobExpRate / 2;
    }
    else if (ch->IsOverTime(OT_5HOUR))
    {
        return 0;
    }
}
//END_PREVENT_TOXICATION_FOR_CHINA