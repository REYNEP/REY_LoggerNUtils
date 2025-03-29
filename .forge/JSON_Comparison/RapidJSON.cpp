// rapidjson - THE WORST (but perf is nice enough)
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
void amVK_Instance::ExportJSON(void) {
    rapidjson::Document root; root.SetObject();
    rapidjson::Document::AllocatorType& allocator = root.GetAllocator();
    rapidjson::Value vkEnumeratePhysicalDevices(rapidjson::kObjectType);

    for (int i = 0, lim = amVK_GPU_List.n; i < lim; i++) {
        std::string gpuKey = toSTR(&amVK_GPU_List[i]);
        rapidjson::Value GPU(rapidjson::kObjectType);

        for (int j = 0, lim = amVK_2D_GPUs_QFAMs[i].n; j < lim; j++) {
            std::string key = "QueueFamily" + std::to_string(j) + "_Properties";
            rapidjson::Value QFam(rapidjson::kObjectType);

            QFam.AddMember("queueFlags", amVK_2D_GPUs_QFAMs[i][j].queueFlags, allocator);
            QFam.AddMember("queueCount", amVK_2D_GPUs_QFAMs[i][j].queueCount, allocator);
            QFam.AddMember("timestampValidBits", amVK_2D_GPUs_QFAMs[i][j].timestampValidBits, allocator);

            rapidjson::Value minImageTransferGranularity(rapidjson::kObjectType);
            minImageTransferGranularity.AddMember("width", amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.width, allocator);
            minImageTransferGranularity.AddMember("height", amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.height, allocator);
            minImageTransferGranularity.AddMember("depth", amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.depth, allocator);

            QFam.AddMember("minImageTransferGranularity", minImageTransferGranularity, allocator);
            GPU.AddMember(rapidjson::Value(key.c_str(), allocator), QFam, allocator);
        }

        vkEnumeratePhysicalDevices.AddMember(rapidjson::Value(gpuKey.c_str(), allocator), GPU, allocator);
    }

    root.AddMember("vkEnumeratePhysicalDevices", vkEnumeratePhysicalDevices, allocator);

    // Write to file
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    root.Accept(writer);

    std::ofstream file("data.json");
    file << buffer.GetString();
}