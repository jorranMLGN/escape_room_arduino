#include "utils/combination.h"

combination::combination()
    : id_index(0), correct_ids({30, 158, 206, 77, 221, 29}), current_ids({0, 0, 0, 0, 0, 0})
{
}

void combination::add(int id)
{
    if (id_index >= 6)
    {
        id_index = 0;
        return;
    }
    current_ids[id_index] = id;
    id_index++;
}

bool combination::is_correct()
{
    for (int i = 0; i < 6; i++)
    {
        if (current_ids[i] != correct_ids[i])
        {
            return false;
        }
        else if (i == 5)
        {
            id_index = 0;
            return true;
        }
    }
}

void combination::reset()
{
    for (int i = 0; i < 6; i++)
    {
        current_ids[i] = 0;
    }
    id_index = 0;
}

int combination::get_id_index()
{
    return id_index;
}