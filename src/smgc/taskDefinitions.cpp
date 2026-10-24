#include <smgc/taskDefinitions.h>

task_SmgcSwapObjects::task_SmgcSwapObjects(): BaseTask(0) {}
bool taskIs_SmgcSwapObjects(uint32_t taskIdx) {
    return taskIdx == 0;
}

task_SmgcClearObjects::task_SmgcClearObjects(): BaseTask(1) {}
bool taskIs_SmgcClearObjects(uint32_t taskIdx) {
    return taskIdx == 1;
}

task_SmgcPushObject::task_SmgcPushObject(std::unique_ptr<Object> t_obj): BaseTask(2) {
    obj = std::move(t_obj);
}
bool taskIs_SmgcPushObject(uint32_t taskIdx) {
    return taskIdx == 2;
}