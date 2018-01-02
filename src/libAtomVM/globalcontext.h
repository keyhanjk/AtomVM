/***************************************************************************
 *   Copyright 2017 by Davide Bettio <davide@uninstall.it>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#ifndef _GLOBALCONTEXT_H_
#define _GLOBALCONTEXT_H_

#include <stdint.h>

#include "linkedlist.h"

struct Context;

#ifndef TYPEDEF_CONTEXT
#define TYPEDEF_CONTEXT
typedef struct Context Context;
#endif

struct GlobalContext;

typedef struct
{
    struct ListHead *ready_processes;
    struct ListHead *waiting_processes;
    struct ListHead *listeners;
    struct ListHead *processes_table;
    struct ListHead *registered_processes;

    int32_t last_process_id;
} GlobalContext;

extern GlobalContext *globalcontext_new();
extern void globalcontext_destroy(GlobalContext *glb);

Context *globalcontext_get_process(GlobalContext *glb, int32_t process_id);
int32_t globalcontext_get_new_process_id(GlobalContext *glb);

void globalcontext_register_process(GlobalContext *glb, int atom_index, int local_process_id);
int globalcontext_get_registered_process(GlobalContext *glb, int atom_index);

#endif
