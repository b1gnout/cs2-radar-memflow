#include <stdio.h>
#include "memflow-ffi/memflow.h"
#include "memflow-ffi/memflow.hpp"
#pragma once

struct Memory{
    char process_name[32];

    OsInstance os_instance;
    ProcessInstance process_instance;
    const ProcessInfo* process_info;

    ModuleInfo *get_module_info(const char* module_name);
    bool read_process_mem(void *buffer, uintptr_t addr, uintptr_t length);
    bool get_process_info();
};

bool get_os_instance(OsInstance* os_instance);

bool get_process_instance(OsInstance os_instance, ProcessInstance* process_instance, char process_name[32]);