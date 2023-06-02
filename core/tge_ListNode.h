#pragma once


struct ListNode {
    void* value_ptr;
    struct ListNode* next;
    struct ListNode* prev;
};


struct ListNode*
ListNode_Create(
    void* value_ptr)
{
    struct ListNode* new_listnode = calloc(1, sizeof(struct ListNode));
    new_listnode->value_ptr = value_ptr;
    return new_listnode;
}