// gason
#include <gason.h>


void amVK_Instance::ExportJSON(void) {
    JsonAllocator allocator;
    JsonValue root = json_object();
    JsonValue vkEnumeratePhysicalDevices = json_object();

    for (int i = 0, lim = amVK_GPU_List.n; i < lim; i++) {
        std::string gpuKey = toSTR(&amVK_GPU_List[i]);
        JsonValue GPU = json_object();

        for (int j = 0, lim = amVK_2D_GPUs_QFAMs[i].n; j < lim; j++) {
            std::string key = "QueueFamily" + std::to_string(j) + "_Properties";
            JsonValue QFam = json_object();

            json_object_set(QFam, "queueFlags", json_integer(amVK_2D_GPUs_QFAMs[i][j].queueFlags));
            json_object_set(QFam, "queueCount", json_integer(amVK_2D_GPUs_QFAMs[i][j].queueCount));
            json_object_set(QFam, "timestampValidBits", json_integer(amVK_2D_GPUs_QFAMs[i][j].timestampValidBits));

            JsonValue minImageTransferGranularity = json_object();
            json_object_set(minImageTransferGranularity, "width", json_integer(amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.width));
            json_object_set(minImageTransferGranularity, "height", json_integer(amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.height));
            json_object_set(minImageTransferGranularity, "depth", json_integer(amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.depth));

            json_object_set(QFam, "minImageTransferGranularity", minImageTransferGranularity);
            json_object_set(GPU, key.c_str(), QFam);
        }

        json_object_set(vkEnumeratePhysicalDevices, gpuKey.c_str(), GPU);
    }

    json_object_set(root, "vkEnumeratePhysicalDevices", vkEnumeratePhysicalDevices);

    // Write to file
    std::ofstream file("data.json");
    char *s = json_serialize(root);
    file << s;
    std::free(s);
}