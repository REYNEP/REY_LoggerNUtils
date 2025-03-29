// nlohmann - Handles String Stuffs automatically
#include <nlohmann/json.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
std::string toSTR(void* ptr) {
    std::stringstream ss;
    ss << ptr;
    return ss.str();
}

void amVK_Instance::ExportJSON(void) {
    nlohmann::ordered_json root; 
    nlohmann::ordered_json vkEnumeratePhysicalDevices  = nlohmann::ordered_json::object();
                    
    for (int k = 0, lim = amVK_GPU_List.n; k < lim; k++) {
        nlohmann::ordered_json GPU_k = nlohmann::ordered_json::object();
        nlohmann::ordered_json QFAM_Array = nlohmann::ordered_json::object(); 

        for (int i = 0, lim = amVK_2D_GPUs_QFAMs[k].n; i < lim; i++) {
            nlohmann::ordered_json QFAM_i = nlohmann::ordered_json::object();

            QFAM_i["queueFlags"] = amVK_2D_GPUs_QFAMs[k][i].queueFlags;
            QFAM_i["queueCount"] = amVK_2D_GPUs_QFAMs[k][i].queueCount;
            QFAM_i["timestampValidBits"] = amVK_2D_GPUs_QFAMs[k][i].timestampValidBits;

            nlohmann::ordered_json minImageTransferGranularity = nlohmann::json::object();
            minImageTransferGranularity["width"] = amVK_2D_GPUs_QFAMs[k][i].minImageTransferGranularity.width;
            minImageTransferGranularity["height"] = amVK_2D_GPUs_QFAMs[k][i].minImageTransferGranularity.height;
            minImageTransferGranularity["depth"] = amVK_2D_GPUs_QFAMs[k][i].minImageTransferGranularity.depth;

            QFAM_i["minImageTransferGranularity"] = minImageTransferGranularity;

            std::string index_id  = "QueueFamily" + std::to_string(i) + "_Properties";
             QFAM_Array[index_id] = QFAM_i;
                    // Each Iteration, we are setting   QFAM_i   into   QFAM_Array
        }

            GPU_k["Memory Address"] = toSTR(amVK_GPU_List[k]);
            GPU_k["vkGetPhysicalDeviceQueueFamilyProperties()"] = QFAM_Array;
                // First, we are setting   QFam_Props   into   GPU_k
        vkEnumeratePhysicalDevices["[GPU " + std::to_string(k) + "]"] = GPU_k;
            // Then,      we are setting        GPU_k   into   this
    }
    root["vkEnumeratePhysicalDevices"] = vkEnumeratePhysicalDevices;
        // then we are finally setting everything into root
    
    // Write to file
    std::ofstream file("data.json");
    file << root.dump(4); // Indent with 4 spaces
}
