// UltraJSON - ujson
#include <ultrajson.h>


void amVK_Instance::ExportJSON(void) {
    UJObject root = UJObject::NewObject();
    UJObject vkEnumeratePhysicalDevices = UJObject::NewObject();


    for (int i = 0, lim = amVK_GPU_List.n; i < lim; i++) {
        std::string gpuKey = toSTR(&amVK_GPU_List[i]);
        UJObject GPU = UJObject::NewObject();

        for (int j = 0, lim = amVK_2D_QFAM_PROPs[i].n; j < lim; j++) {
            std::string key = "QueueFamily" + std::to_string(j) + "_Properties";
            UJObject QFam = UJObject::NewObject();

            QFam.Set("queueFlags", amVK_2D_QFAM_PROPs[i][j].queueFlags);
            QFam.Set("queueCount", amVK_2D_QFAM_PROPs[i][j].queueCount);
            QFam.Set("timestampValidBits", amVK_2D_QFAM_PROPs[i][j].timestampValidBits);

            UJObject minImageTransferGranularity = UJObject::NewObject();
            minImageTransferGranularity.Set("width", amVK_2D_QFAM_PROPs[i][j].minImageTransferGranularity.width);
            minImageTransferGranularity.Set("height", amVK_2D_QFAM_PROPs[i][j].minImageTransferGranularity.height);
            minImageTransferGranularity.Set("depth", amVK_2D_QFAM_PROPs[i][j].minImageTransferGranularity.depth);

            QFam.Set("minImageTransferGranularity", minImageTransferGranularity);
            GPU.Set(key.c_str(), QFam);
        }

        vkEnumeratePhysicalDevices.Set(gpuKey.c_str(), GPU);
    }

    root.Set("vkEnumeratePhysicalDevices", vkEnumeratePhysicalDevices);

    // Write to file
    std::ofstream file("data.json");
    file << root.ToString();
}