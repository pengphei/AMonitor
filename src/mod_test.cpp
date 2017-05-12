#include "mod_test.h"

#include "cJSON.h"
#include "cJSON_Utils.h"

static void cjson_test()
{
    cJSON *item = NULL;
    cJSON *found = NULL;

    item = cJSON_Parse("{\"one\":1, \"Two\":2, \"tHree\":3}");

    found = cJSON_GetObjectItem(NULL, "test");

    found = cJSON_GetObjectItem(item, NULL);


    found = cJSON_GetObjectItem(item, "one");


    found = cJSON_GetObjectItem(item, "tWo");


    found = cJSON_GetObjectItem(item, "three");


    found = cJSON_GetObjectItem(item, "four");

    cJSON_Delete(item);
}
