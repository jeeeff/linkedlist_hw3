#include <stdint.h>

typedef struct __list list;
struct __list {
    int data;
    struct __list *addr;
};

#define XOR(a, b) ((list *) ((uintptr_t) (a) ^ (uintptr_t) (b)))

static void print_list(void *head)
{
    list *curr = (list *)head;
    if (!curr) {
        printf("List is empty.\n");
        return ;
    }

    list *prev = NULL;
    list *next = NULL;
    while (curr) {
        printf("%d\n", curr->data);
        next = XOR(prev, curr->addr);
        prev = curr;
        curr = next;
    }
    printf("\n");
}

void insert_node(list **l, int d) {
    list *tmp = malloc(sizeof(list));
    tmp->data = d;

    if (!(*l)) {
        tmp->addr = NULL;
    } else {
        (*l)->addr = XOR(tmp, (*l)->addr);
        tmp->addr = *l;
    }
    *l = tmp;
//    print_list(*l);
}

void delete_list(list *l) {
    while (l) {
        list *next = l->addr;
        if (next)
            next->addr = XOR(next->addr, l);
        free(l);
        l = next;
    }
}

list *sort(list *start)
{
    if (!start || !start->addr)
        return start;

    list *left = start, *right = start->addr;
    left->addr = NULL;
    right->addr = XOR(right->addr, left);

    left = sort(left);
    right = sort(right);

    for (list *merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            list *next = left->addr;
            if (next)
                next->addr = XOR(left, next->addr);

            if (!merge) {
                start = merge = left;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(merge->addr,left);
                left->addr = merge;
                merge = left;
            }
            left = next;
        } else {
            list *next = right->addr;
            if (next)
                next->addr = XOR(right, next->addr);

            if (!merge) {
                start = merge = right;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(merge->addr,right);
                right->addr = merge;
                merge = right;
            }
            right = next;
        }
    }

    return start;
}

list *merge_sort(list *start, int cut)
{
    if (!start || !start->addr)
        return start;

    list *left = start, *right = start->addr, *left_end = start;

    int mid = cut / 2;
    for (int i = 0; i < mid - 1; i++) {
        list *tmp;
        tmp = right;
        right = XOR(right->addr, left_end);
        left_end = tmp;
    }
    left_end->addr = XOR(right, left_end->addr);
    right->addr = XOR(right->addr, left_end);
    left = merge_sort(left, mid);
    right = merge_sort(right, cut - mid);

    left = merge_sort(left, mid);
    right = merge_sort(right, cut - mid);

    for (list *merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            list *next = left->addr;
            if (next)
                next->addr = XOR(left, next->addr);

            if (!merge) {
                start = merge = left;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(merge->addr,left);
                left->addr = merge;
                merge = left;
            }
            left = next;
        } else {
            list *next = right->addr;
            if (next)
                next->addr = XOR(right, next->addr);

            if (!merge) {
                start = merge = right;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(merge->addr,right);
                right->addr = merge;
                merge = right;
            }
            right = next;
        }
    }

    return start;
}
