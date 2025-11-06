#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdbool.h>

typedef struct objectTest {
    struct objectTest* parent;
    int layer;
    char* title;
    bool active;
} objectTest;

bool objectTest_is_active(objectTest* obj);
char* objectTest_get_title(objectTest* obj);

#endif