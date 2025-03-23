// FastJSON.cpp
#include <fastjson.h>


void amVK_Instance::ExportJSON(void) {
    fjson::Json root = fjson::Json::object();
    fjson::Json vkEnumeratePhysicalDevices = fjson::Json::object();


    for (int i = 0, lim = amVK_GPU_List.n; i < lim; i++) {
        std::string gpuKey = toSTR(&amVK_GPU_List[i]);
        fjson::Json GPU = fjson::Json::object();

        for (int j = 0, lim = amVK_2D_QFAM_PROPs[i].n; j < lim; j++) {
            std::string key = "QueueFamily" + std::to_string(j) + "_Properties";
            fjson::Json QFam = fjson::Json::object();

            QFam["queueFlags"] = amVK_2D_QFAM_PROPs[i][j].queueFlags;
            QFam["queueCount"] = amVK_2D_QFAM_PROPs[i][j].queueCount;
            QFam["timestampValidBits"] = amVK_2D_QFAM_PROPs[i][j].timestampValidBits;

            fjson::Json minImageTransferGranularity = fjson::Json::object();
            minImageTransferGranularity["width"] = amVK_2D_QFAM_PROPs[i][j].minImageTransferGranularity.width;
            minImageTransferGranularity["height"] = amVK_2D_QFAM_PROPs[i][j].minImageTransferGranularity.height;
            minImageTransferGranularity["depth"] = amVK_2D_QFAM_PROPs[i][j].minImageTransferGranularity.depth;

            QFam["minImageTransferGranularity"] = minImageTransferGranularity;
            GPU[key] = QFam;
        }

        vkEnumeratePhysicalDevices[gpuKey] = GPU;
    }

    root["vkEnumeratePhysicalDevices"] = vkEnumeratePhysicalDevices;

    // Write to file
    std::ofstream file("data.json");
    file << root.dump();
}