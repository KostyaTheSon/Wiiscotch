#include "data_win.h"

#include <stdio.h>
#include <string.h>

void DataWin_printSummary(DataWin* dw) {
    printf("===== data.win Summary =====\n\n");

    // GEN8
    Gen8* g = &dw->gen8;
    printf("-- GEN8 (General Info) --\n");
    printf("  Game Name:        %s\n", g->name ? g->name : "(null)");
    printf("  Display Name:     %s\n", g->displayName ? g->displayName : "(null)");
    printf("  File Name:        %s\n", g->fileName ? g->fileName : "(null)");
    printf("  Config:           %s\n", g->config ? g->config : "(null)");
    printf("  Bytecode Version: %u\n", g->bytecodeVersion);
    printf("  Game ID:          %u\n", g->gameID);
    printf("  Version:          %u.%u.%u.%u\n", g->major, g->minor, g->release, g->build);
    printf("  Window Size:      %ux%u\n", g->defaultWindowWidth, g->defaultWindowHeight);
    printf("  Steam App ID:     %d\n", g->steamAppID);
    printf("  Room Order:       %u rooms\n", g->roomOrderCount);
    printf("\n");

    // OPTN
    printf("-- OPTN (Options) --\n");
    printf("  Constants:        %u\n", dw->optn.constantCount);
    if (dw->optn.constantCount > 0) {
        uint32_t show = dw->optn.constantCount < 3 ? dw->optn.constantCount : 3;
        for (uint32_t i = 0; i < show; i++) {
            printf("    [%u] %s = %s\n", i, dw->optn.constants[i].name ? dw->optn.constants[i].name : "?", dw->optn.constants[i].value ? dw->optn.constants[i].value : "?");
        }
        if (dw->optn.constantCount > 3) printf("    ... and %u more\n", dw->optn.constantCount - 3);
    }
    printf("\n");

    // LANG
    printf("-- LANG (Languages) --\n");
    printf("  Languages:        %u\n", dw->lang.languageCount);
    printf("  Entries:          %u\n", dw->lang.entryCount);
    printf("\n");

    // EXTN
    printf("-- EXTN (Extensions) --\n");
    printf("  Extensions:       %u\n", dw->extn.count);
    for (uint32_t i = 0; i < dw->extn.count; i++) {
        printf("    [%u] %s (%u files)\n", i, dw->extn.extensions[i].name ? dw->extn.extensions[i].name : "?", dw->extn.extensions[i].fileCount);
    }
    printf("\n");

    // SOND
    printf("-- SOND (Sounds) --\n");
    printf("  Sounds:           %u\n", dw->sond.count);
    if (dw->sond.count > 0) {
        uint32_t show = dw->sond.count < 3 ? dw->sond.count : 3;
        for (uint32_t i = 0; i < show; i++) {
            printf("    [%u] %s (%s)\n", i, dw->sond.sounds[i].name ? dw->sond.sounds[i].name : "?", dw->sond.sounds[i].type ? dw->sond.sounds[i].type : "?");
        }
        if (dw->sond.count > 3) printf("    ... and %u more\n", dw->sond.count - 3);
    }
    printf("\n");

    // AGRP
    printf("-- AGRP (Audio Groups) --\n");
    printf("  Audio Groups:     %u\n", dw->agrp.count);
    for (uint32_t i = 0; i < dw->agrp.count; i++) {
        printf("    [%u] %s\n", i, dw->agrp.audioGroups[i].name ? dw->agrp.audioGroups[i].name : "?");
    }
    printf("\n");

    // SPRT
    printf("-- SPRT (Sprites) --\n");
    printf("  Sprites:          %u\n", dw->sprt.count);
    if (dw->sprt.count > 0) {
        uint32_t show = dw->sprt.count < 3 ? dw->sprt.count : 3;
        for (uint32_t i = 0; i < show; i++) {
            Sprite* spr = &dw->sprt.sprites[i];
            printf("    [%u] %s (%ux%u, %u frames)\n", i, spr->name ? spr->name : "?", spr->width, spr->height, spr->textureCount);
        }
        if (dw->sprt.count > 3) printf("    ... and %u more\n", dw->sprt.count - 3);
    }
    printf("\n");

    // BGND
    printf("-- BGND (Backgrounds) --\n");
    printf("  Backgrounds:      %u\n", dw->bgnd.count);
    if (dw->bgnd.count > 0) {
        uint32_t show = dw->bgnd.count < 3 ? dw->bgnd.count : 3;
        for (uint32_t i = 0; i < show; i++) {
            printf("    [%u] %s\n", i, dw->bgnd.backgrounds[i].name ? dw->bgnd.backgrounds[i].name : "?");
        }
        if (dw->bgnd.count > 3) printf("    ... and %u more\n", dw->bgnd.count - 3);
    }
    printf("\n");

    // PATH
    printf("-- PATH (Paths) --\n");
    printf("  Paths:            %u\n", dw->path.count);
    printf("\n");

    // SCPT
    printf("-- SCPT (Scripts) --\n");
    printf("  Scripts:          %u\n", dw->scpt.count);
    if (dw->scpt.count > 0) {
        uint32_t show = dw->scpt.count < 3 ? dw->scpt.count : 3;
        for (uint32_t i = 0; i < show; i++) {
            printf("    [%u] %s -> code[%d]\n", i, dw->scpt.scripts[i].name ? dw->scpt.scripts[i].name : "?", dw->scpt.scripts[i].codeId);
        }
        if (dw->scpt.count > 3) printf("    ... and %u more\n", dw->scpt.count - 3);
    }
    printf("\n");

    // GLOB
    printf("-- GLOB (Global Init Scripts) --\n");
    printf("  Init Scripts:     %u\n", dw->glob.count);
    printf("\n");

    // SHDR
    printf("-- SHDR (Shaders) --\n");
    printf("  Shaders:          %u\n", dw->shdr.count);
    for (uint32_t i = 0; i < dw->shdr.count; i++) {
        printf("    [%u] %s (version %d)\n", i, dw->shdr.shaders[i].name ? dw->shdr.shaders[i].name : "?", dw->shdr.shaders[i].version);
    }
    printf("\n");

    // FONT
    printf("-- FONT (Fonts) --\n");
    printf("  Fonts:            %u\n", dw->font.count);
    for (uint32_t i = 0; i < dw->font.count; i++) {
        Font* font = &dw->font.fonts[i];
        printf("    [%u] %s (%s, em=%u, %u glyphs)\n", i, font->name ? font->name : "?", font->displayName ? font->displayName : "?", font->emSize, font->glyphCount);
    }
    printf("\n");

    // TMLN
    printf("-- TMLN (Timelines) --\n");
    printf("  Timelines:        %u\n", dw->tmln.count);
    printf("\n");

    // OBJT
    printf("-- OBJT (Game Objects) --\n");
    printf("  Objects:          %u\n", dw->objt.count);
    if (dw->objt.count > 0) {
        uint32_t show = dw->objt.count < 3 ? dw->objt.count : 3;
        for (uint32_t i = 0; i < show; i++) {
            GameObject* obj = &dw->objt.objects[i];
            uint32_t totalEvents = 0;
            for (int e = 0; e < OBJT_EVENT_TYPE_COUNT; e++) {
                totalEvents += obj->eventLists[e].eventCount;
            }
            printf("    [%u] %s (sprite=%d, depth=%d, %u events)\n", i, obj->name ? obj->name : "?", obj->spriteId, obj->depth, totalEvents);
        }
        if (dw->objt.count > 3) printf("    ... and %u more\n", dw->objt.count - 3);
    }
    printf("\n");

    // ROOM
    printf("-- ROOM (Rooms) --\n");
    printf("  Rooms:            %u\n", dw->room.count);
    if (dw->room.count > 0) {
        uint32_t show = dw->room.count < 3 ? dw->room.count : 3;
        for (uint32_t i = 0; i < show; i++) {
            Room* room = &dw->room.rooms[i];
            printf("    [%u] %s (%ux%u, %u objects, %u tiles)\n", i, room->name ? room->name : "?", room->width, room->height, room->gameObjectCount, room->tileCount);
        }
        if (dw->room.count > 3) printf("    ... and %u more\n", dw->room.count - 3);
    }
    printf("\n");

    // TPAG
    printf("-- TPAG (Texture Page Items) --\n");
    printf("  Items:            %u\n", dw->tpag.count);
    printf("\n");

    // CODE
    printf("-- CODE (Code Entries) --\n");
    printf("  Entries:          %u\n", dw->code.count);
    if (dw->code.count > 0) {
        uint32_t show = dw->code.count < 3 ? dw->code.count : 3;
        for (uint32_t i = 0; i < show; i++) {
            CodeEntry* entry = &dw->code.entries[i];
            printf("    [%u] %s (%u bytes, %u locals, %u args)\n", i, entry->name ? entry->name : "?", entry->length, entry->localsCount, entry->argumentsCount);
        }
        if (dw->code.count > 3) printf("    ... and %u more\n", dw->code.count - 3);
    }
    printf("\n");

    // VARI
    printf("-- VARI (Variables) --\n");
    printf("  Variables:        %u\n", dw->vari.variableCount);
    printf("  Max Locals:       %u\n", dw->vari.maxLocalVarCount);
    if (dw->vari.variableCount > 0) {
        uint32_t show = dw->vari.variableCount < 3 ? dw->vari.variableCount : 3;
        for (uint32_t i = 0; i < show; i++) {
            Variable* var = &dw->vari.variables[i];
            printf("    [%u] %s (type=%d, id=%d, %u refs)\n", i, var->name ? var->name : "?", var->instanceType, var->varID, var->occurrences);
        }
        if (dw->vari.variableCount > 3) printf("    ... and %u more\n", dw->vari.variableCount - 3);
    }
    printf("\n");

    // FUNC
    printf("-- FUNC (Functions) --\n");
    printf("  Functions:        %u\n", dw->func.functionCount);
    printf("  Code Locals:      %u\n", dw->func.codeLocalsCount);
    if (dw->func.functionCount > 0) {
        uint32_t show = dw->func.functionCount < 3 ? dw->func.functionCount : 3;
        for (uint32_t i = 0; i < show; i++) {
            printf("    [%u] %s (%u refs)\n", i, dw->func.functions[i].name ? dw->func.functions[i].name : "?", dw->func.functions[i].occurrences);
        }
        if (dw->func.functionCount > 3) printf("    ... and %u more\n", dw->func.functionCount - 3);
    }
    printf("\n");

    // STRG
    printf("-- STRG (Strings) --\n");
    printf("  Strings:          %u\n", dw->strg.count);
    if (dw->strg.count > 0) {
        uint32_t show = dw->strg.count < 5 ? dw->strg.count : 5;
        for (uint32_t i = 0; i < show; i++) {
            const char* str = dw->strg.strings[i];
            // Truncate long strings for display
            if (str) {
                size_t len = strlen(str);
                if (len > 60) {
                    printf("    [%u] \"%.60s...\" (%zu chars)\n", i, str, len);
                } else {
                    printf("    [%u] \"%s\"\n", i, str);
                }
            } else {
                printf("    [%u] (null)\n", i);
            }
        }
        if (dw->strg.count > 5) printf("    ... and %u more\n", dw->strg.count - 5);
    }
    printf("\n");

    // TXTR
    printf("-- TXTR (Textures) --\n");
    printf("  Textures:         %u\n", dw->txtr.count);
    if (dw->txtr.count > 0) {
        for (uint32_t i = 0; i < dw->txtr.count; i++) {
            Texture* tex = &dw->txtr.textures[i];
            printf("    [%u] offset=0x%08X size=%u bytes\n", i, tex->blobOffset, tex->blobSize);
        }
    }
    printf("\n");

    // AUDO
    printf("-- AUDO (Audio) --\n");
    printf("  Audio Entries:    %u\n", dw->audo.count);
    if (dw->audo.count > 0) {
        uint32_t show = dw->audo.count < 3 ? dw->audo.count : 3;
        for (uint32_t i = 0; i < show; i++) {
            printf("    [%u] offset=0x%08X size=%u bytes\n", i, dw->audo.entries[i].dataOffset, dw->audo.entries[i].dataSize);
        }
        if (dw->audo.count > 3) printf("    ... and %u more\n", dw->audo.count - 3);
    }
    printf("\n");

    // Overall summary
    printf("===== File: %.2f MB =====\n", dw->fileSize / (1024.0 * 1024.0));
}
