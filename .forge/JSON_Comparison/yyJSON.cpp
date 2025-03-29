// yyJSON [new] -> Kinda based on gason
#include <yyjson.h>


void amVK_Instance::ExportJSON(void) {
    yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
    yyjson_mut_val *root = yyjson_mut_obj(doc);
    yyjson_mut_val *vkEnumeratePhysicalDevices = yyjson_mut_obj(doc);

    for (int i = 0, lim = amVK_GPU_List.n; i < lim; i++) {
        std::string gpuKey = toSTR(&amVK_GPU_List[i]);
        yyjson_mut_val *GPU = yyjson_mut_obj(doc);

        for (int j = 0, lim = amVK_2D_GPUs_QFAMs[i].n; j < lim; j++) {
            std::string key = "QueueFamily" + std::to_string(j) + "_Properties";
            yyjson_mut_val *QFam = yyjson_mut_obj(doc);

            yyjson_mut_obj_add_int(doc, QFam, "queueFlags", amVK_2D_GPUs_QFAMs[i][j].queueFlags);
            yyjson_mut_obj_add_int(doc, QFam, "queueCount", amVK_2D_GPUs_QFAMs[i][j].queueCount);
            yyjson_mut_obj_add_int(doc, QFam, "timestampValidBits", amVK_2D_GPUs_QFAMs[i][j].timestampValidBits);

            yyjson_mut_val *minImageTransferGranularity = yyjson_mut_obj(doc);
            yyjson_mut_obj_add_int(doc, minImageTransferGranularity, "width", amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.width);
            yyjson_mut_obj_add_int(doc, minImageTransferGranularity, "height", amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.height);
            yyjson_mut_obj_add_int(doc, minImageTransferGranularity, "depth", amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.depth);

            yyjson_mut_obj_add_val(doc, QFam, "minImageTransferGranularity", minImageTransferGranularity);
            yyjson_mut_obj_add_val(doc, GPU, key.c_str(), QFam);
        }

        yyjson_mut_obj_add_val(doc, vkEnumeratePhysicalDevices, gpuKey.c_str(), GPU);
    }

    yyjson_mut_obj_add_val(doc, root, "vkEnumeratePhysicalDevices", vkEnumeratePhysicalDevices);

    // Write to file
    yyjson_write_flag flg = YYJSON_WRITE_PRETTY;
    yyjson_mut_doc_set_root(doc, root);
    yyjson_write_file("data.json", doc, flg, NULL);
    yyjson_mut_doc_free(doc);
}