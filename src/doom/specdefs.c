//
// Copyright(C) 2025 Vladislav Putintsev (Ear1h)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include "specdefs.h"

#include "stdio.h"
#include "stdlib.h"

#include "m_array.h"
#include "m_json.h"
#include "m_misc.h"

#include "p_local.h"
#include "r_local.h"
#include "p_spec.h"
#include "w_wad.h"

static boolean ParseSpecials(json_t *json, macros_t *macro)
{
    macro_special_t spec = {0};

    json_t *macro_action = JS_GetObject(json, "action");
    if (!JS_IsNumber(macro_action))
        return false;

    spec.action = (short) JS_GetInteger(macro_action);

    json_t *tag = JS_GetObject(json, "tag");
    if (!JS_IsNumber(tag))
        return false;

    spec.tag = (short) JS_GetInteger(tag);

    array_push(macro->specials, spec);

    return true;
}

static boolean ParseMacro(json_t *json, macros_t *macro)
{
    json_t *id = JS_GetObject(json, "id");
    if (!JS_IsNumber(id))
        return false;

    macro->macroid = JS_GetInteger(id);

    json_t *js_specs = JS_GetObject(json, "specials");
    if (!JS_IsNull(js_specs))
    {
        json_t *js_spec = NULL;
        JS_ArrayForEach(js_spec, js_specs)
        {
            ParseSpecials(js_spec, macro);
        }
    }

    return true;
}

static boolean ParseMessage(json_t *json, spec_message_t *message)
{
    json_t *id = JS_GetObject(json, "id");
    if (!JS_IsNumber(id))
        return false;

    message->messageid = JS_GetInteger(id);

    const char *text = JS_GetStringValue(json, "text");
    if (!text)
        return false;
        
    message->messages = M_StringDuplicate(text);
    return true;
}

specdefs_t *ParseSpecdefs(void)
{
    json_t *json = JS_Open("SPECDEFS", "specdefs", (version_t) {1, 0, 0});
    if (json == NULL)
    {
        return NULL;
    }

    json_t *data = JS_GetObject(json, "data");
    if (JS_IsNull(data) || !JS_IsObject(data))
    {
        I_Error("SKYDEFS: no data");
        JS_Close("SPECDEFS");
        return NULL;
    }

    specdefs_t *out = calloc(1, sizeof(*out));

    json_t *js_macros = JS_GetObject(data, "macro");
    json_t *js_macro = NULL;

    JS_ArrayForEach(js_macro, js_macros)
    {
        macros_t macro = {0};
        if (ParseMacro(js_macro, &macro))
        {
            array_push(out->spec_macro, macro);
        }
    }

    json_t *js_messages = JS_GetObject(data, "message");
    json_t *js_message = NULL;

    JS_ArrayForEach(js_message, js_messages)
    {
        spec_message_t message = {0};
        if (ParseMessage(js_message, &message))
        {
            array_push(out->spec_message, message);
        }
    }
      
    JS_Close("SPECDEFS");
    return out;
}