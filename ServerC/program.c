#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "program.h"

bool objectTest_is_active(objectTest* obj)
{
    return obj->active;
}

char* objectTest_get_title(objectTest* obj)
{
    int lengthTitle = strlen(obj->title) + 2;
    char* newTitle;
    if(obj->parent != NULL)
    {
        newTitle = malloc(lengthTitle + strlen(obj->parent->title));
        strcpy(newTitle, obj->parent->title);
        strcat(newTitle, "->");
        strcat(newTitle, obj->title);
    }
    else
    {
        newTitle = malloc(lengthTitle);
        strcpy(newTitle, obj->title);
    }
    return newTitle;
}

bool check_valid_args(int arg)
{
    if(arg == 0)
    {
        printf("Нужно написать строку");
        return false;
    }
    return true;
}

int main(int arg, char* args[])
{
    printf("Привет мир!\n");
    if(check_valid_args(arg))
    {
        printf("%s", args[1]);
    }
    objectTest obj1; 
    objectTest obj2; 

    obj1.active = true;
    obj2.active = true;

    obj1.title = "parent obj1";
    obj2.title = "child obj2";

    obj2.parent = &obj1;

    char* newtitle = objectTest_get_title(&obj2);

    char newText[50] = "Hello";

    void* ptrText = &newText[0];

    printf("\n%s", newText);

    printf("\n%s", (char*)ptrText);
    printf("\n");
    printf("\n");
    return 0;
}
