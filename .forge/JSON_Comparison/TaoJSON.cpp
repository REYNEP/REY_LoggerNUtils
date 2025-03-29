// TaoJSON.cpp
#include <tao/json.hpp>


void amVK_Instance::ExportJSON(void) {
    tao::json::value root = tao::json::empty_object;



    for (int i = 0, lim = amVK_GPU_List.n; i < lim; i++) {
        std::string gpuKey = toSTR(&amVK_GPU_List[i]);
        tao::json::value GPU = tao::json::empty_object;

        for (int j = 0, lim = amVK_2D_GPUs_QFAMs[i].n; j < lim; j++) {
            std::string key = "QueueFamily" + std::to_string(j) + "_Properties";
            tao::json::value QFam = tao::json::empty_object;

            QFam["queueFlags"] = amVK_2D_GPUs_QFAMs[i][j].queueFlags;
            QFam["queueCount"] = amVK_2D_GPUs_QFAMs[i][j].queueCount;
            QFam["timestampValidBits"] = amVK_2D_GPUs_QFAMs[i][j].timestampValidBits;

            tao::json::value minImageTransferGranularity = tao::json::empty_object;
            minImageTransferGranularity["width"] = amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.width;
            minImageTransferGranularity["height"] = amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.height;
            minImageTransferGranularity["depth"] = amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.depth;

            QFam["minImageTransferGranularity"] = minImageTransferGranularity;
            GPU[key] = QFam;
        }

        root["vkEnumeratePhysicalDevices"][gpuKey] = GPU;
    }

    // Write to file
    std::ofstream file("data.json");
    file << tao::json::to_string(root, 4); // Indent with 4 spaces
}