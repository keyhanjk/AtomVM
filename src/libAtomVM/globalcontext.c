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

#include "globalcontext.h"

#include "context.h"

struct RegisteredProcess
{
    struct ListHead registered_processes_list_head;

    int atom_index;
    int local_process_id;
};

GlobalContext *globalcontext_new()
{
    GlobalContext *glb = malloc(sizeof(GlobalContext));
    glb->ready_processes = NULL;
    glb->waiting_processes = NULL;
    glb->listeners = NULL;
    glb->processes_table = NULL;
    glb->registered_processes = NULL;

    glb->last_process_id = 0;

    return glb;
}

void globalcontext_destroy(GlobalContext *glb)
{
    free(glb);
}

Context *globalcontext_get_process(GlobalContext *glb, int32_t process_id)
{
    Context *processes = GET_LIST_ENTRY(glb->processes_table, Context, processes_table_head);

    Context *p = processes;
    do {
        if (p->process_id == process_id) {
            return p;
        }

        p = GET_LIST_ENTRY(p->processes_table_head.next, Context, processes_table_head);
    } while (processes != p);

    return NULL;
}

int32_t globalcontext_get_new_process_id(GlobalContext *glb)
{
    glb->last_process_id++;

    return glb->last_process_id;
}

void globalcontext_register_process(GlobalContext *glb, int atom_index, int local_process_id)
{
    struct RegisteredProcess *registered_process = malloc(sizeof(struct RegisteredProcess));
    registered_process->atom_index = atom_index;
    registered_process->local_process_id = local_process_id;

    linkedlist_append(&glb->registered_processes, &registered_process->registered_processes_list_head);
}

int globalcontext_get_registered_process(GlobalContext *glb, int atom_index)
{
    const struct RegisteredProcess *registered_processes = GET_LIST_ENTRY(glb->registered_processes, struct RegisteredProcess, registered_processes_list_head);

    const struct RegisteredProcess *p = registered_processes;
    do {
        if (p->atom_index == atom_index) {
            return p->local_process_id;
        }

        p = GET_LIST_ENTRY(p->registered_processes_list_head.next, struct RegisteredProcess, registered_processes_list_head);
    } while (p != registered_processes);

    return 0;
}
