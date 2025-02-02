#include "memory.h"

ModuleInfo *Memory::get_module_info(const char* module_name)
{
    ModuleInfo *target_module;
    COLLECT_CB(ModuleInfo, module_info);
    //fails here
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

bool Memory::get_process_info()
{
    return false;
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

bool get_process_instance(OsInstance os_instance, ProcessInstance* process_instance, char process_name[32])
{
    return !mf_osinstance_process_by_name(&os_instance, STR(process_name), process_instance);
}
