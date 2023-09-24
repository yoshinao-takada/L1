#include "SLC/DLink.h"
#include <stdlib.h>

SLC_PDLink_t SLC_DLink_InitArray(void* node_array, SLCsize_t n, SLCsize_t additional_bytes)
{
    SLCsize_t unitbytes = (additional_bytes + sizeof(SLC_DLink_t));
    SLCu8_t* head = (SLCu8_t*)node_array;
    ((SLC_PDLink_t)head)->next = ((SLC_PDLink_t)head)->prev = (SLC_PDLink_t)head;
    for (SLCsize_t i = 1; i < n; i++)
    {
        SLC_DLink_AddPrev((SLC_PDLink_t)head, (SLC_PDLink_t)(head + unitbytes * i));
    }
    return (SLC_PDLink_t)head;
}

SLC_PDLink_t SLC_DLink_Alloc(SLCsize_t n, SLCsize_t additional_bytes)
{
    SLCsize_t unitbytes = (additional_bytes + sizeof(SLC_DLink_t));
    SLCsize_t allocsize = unitbytes * n;
    SLCu8_t*  head = (SLCu8_t*)malloc(allocsize);
    ((SLC_PDLink_t)head)->next = ((SLC_PDLink_t)head)->prev = (SLC_PDLink_t)head;
    for (SLCsize_t i = 1; i < n; i++)
    {
        SLC_DLink_AddPrev((SLC_PDLink_t)head, (SLC_PDLink_t)(head + unitbytes * i));
    }
    return (SLC_PDLink_t)head;
}

void SLC_DLink_AddPrev(SLC_PDLink_t at, SLC_PDLink_t new_node)
{
    SLC_PDLink_t prev_node = at->prev;
    prev_node->next = new_node;
    new_node->prev = prev_node;
    new_node->next = at;
    at->prev = new_node;
}

void SLC_DLink_AddNext(SLC_PDLink_t at, SLC_PDLink_t new_node)
{
    SLC_PDLink_t next_node = at->next;
    next_node->prev = new_node;
    new_node->next = next_node;
    new_node->prev = at;
    at->next = new_node;
}

SLCsize_t SLC_DLink_Count(SLC_PDLink_t at)
{
    SLCsize_t count = 0;
    SLC_PDLink_t node = at->next;
    while (node != at)
    {
        count++;
        node = node->next;
    }
    return count;
}

SLC_PDLink_t SLC_DLink_Peek(SLC_PDLink_t anchor, SLCi32_t offset)
{
    SLC_PDLink_t target = anchor;
    do {
        target = target->next;
    } while (--offset);
    return target;
}

SLC_PDLink_t SLC_DLink_Remove(SLC_PDLink_t anchor, SLCi32_t offset)
{
    SLC_PDLink_t target = anchor;
    do {
        target = target->next;
    } while (--offset);
    return SLC_DLink_RemoveThis(anchor, target);
}

SLC_PDLink_t SLC_DLink_RemoveThis(SLC_PDLink_t anchor, SLC_PDLink_t toRemove)
{
    if (toRemove == anchor)
    {
        return NULL;
    }
    toRemove->next->prev = toRemove->prev;
    toRemove->prev->next = toRemove->next;
    toRemove->prev = toRemove->next = toRemove;
    return toRemove;
}
