// Bracing is one of those things I do feel strongly about. I have fixed actual logic bugs
// due to poor bracing on more than one occasion. There are three styles I’ve run into
// in the past. The first is lining up all the braces:
void FindObject (unsigned int id, std::list& found)
{
    for (int i = 0; i < m_max; ++i)
    {
        if (m_map[i].id == id)
        {
            found.push_back(m_map[i]);
            GCC_LOG(“Objects”, “Found”);
        }
        else
        {
            GCC_LOG(“Objects”, “Not Found”);
        }
    }
    GCC_LOG(“Objects”, “Next”);
}

// The second is called K&R bracing:
void FindObject (unsigned int id, std::list& found) {
    for (int i = 0; i < m_max; ++i) {
        if (m_map[i].id == id) {
            found.push_back(m_map[i]);
            GCC_LOG(“Objects”, “Found”);
        }
        else {
            GCC_LOG(“Objects”, “Not Found”);
        }
    }
    GCC_LOG(“Objects”, “Next”);
}

// The third is just arbitrarily placing braces where they make sense at the time:
void FindObject (unsigned int id, std::list& found)
{
    for (int i = 0; i < m_max; ++i)
        {
        if (m_map[i].id == id)
        {
        found.push_back(m_map[i]);
        GCC_LOG(“Objects”, “Found”);
        }
            else { GCC_LOG(“Objects”, “Not Found”);
        }
    }
    GCC_LOG(“Objects”, “Next”);
}
// Which one is the most readable? In my opinion, the first style is much more readable
// than the other two. The second style is preferred by some programmers I know
// because it saves space and creates more compact code, and they feel that K&R brac-
// ing is just as readable. I strongly disagree with this and have fixed a couple of bugs
// due to braces getting out of alignment in K&R bracing. By contrast, I have never
// fixed a bug due to bad bracing using the first method. Still, it’s considered to be a
// valid style at some companies. The most important thing here is that you never,
// ever use the third method. Arbitrarily placing braces and tabs is a sure-fire ticket to
// creating incredibly hard-to-read code.