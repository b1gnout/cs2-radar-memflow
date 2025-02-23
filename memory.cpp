#include "memory.h"

ModuleInfo *Memory::get_module_info(const char *module_name)
{
    ModuleInfo *target_module;
    COLLECT_CB(ModuleInfo, module_info);
    mf_processinstance_module_list_callback(&process_instance, 0, module_info);

    for (int i = 0; i < module_info_base.size; i++)
    {
        ModuleInfo *module_info = &((ModuleInfo *)module_info_base.buf)[i];
        if (!strcmp(module_info->name, module_name))
        {
            target_module = module_info;
        }
    }

    return target_module;
}

bool Memory::read_process_mem(void *buffer, uintptr_t addr, uintptr_t length)
{
    CSliceMut_u8 out;
    out.data = (uint8_t *)buffer;
    out.len = length;

    mf_processinstance_read_raw_into(&process_instance, addr, out);

    return true;
}

uint64_t Memory::find_byte_pattern(ModuleInfo *module_info, std::vector<uint8_t> pattern)
{
    void *module_buffer = malloc(module_info->size);
    read_process_mem(module_buffer, module_info->base, module_info->size);

    uint64_t current_byte = 0;
    for (uint64_t i = 0; i < module_info->size - pattern.size(); i++)
    {
        current_byte = (uint64_t)module_buffer + i;
        for (uint64_t j = 0; j < pattern.size(); j++)
        {
            if (pattern[j] == 0x00)
                continue;

            //printf("checking if %#0llx byte: %#0x is %#0x\n", current_byte, *(uint8_t *)(current_byte + j), pattern[j]);

            if (*(uint8_t *)(current_byte + j) != pattern[j])
                break;

            if (j == pattern.size() - 1)
            {
                free(module_buffer);
                return module_info->base + i;
            }
        }
    }

    free(module_buffer);

    return 0;
}

bool get_os_instance(OsInstance *os_instance)
{
    Inventory *inventory = mf_inventory_scan_path("libs");
    if (!inventory)
    {
        mf_inventory_free(inventory);
        return false;
    }

    ConnectorInstance connector;
    if (mf_inventory_create_connector(inventory, "qemu", "", &connector))
    {
        mf_inventory_free(inventory);
        return false;
    }

    if (mf_inventory_create_os(inventory, "win32", "", &connector, os_instance))
    {
        mf_inventory_free(inventory);
        return false;
    }

    return true;
}

bool get_process_instance(OsInstance os_instance, ProcessInstance *process_instance, char process_name[32])
{
    return !mf_osinstance_process_by_name(&os_instance, STR(process_name), process_instance);
}
