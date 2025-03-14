```cpp
#include <ryml.hpp>
#include <ryml_std.hpp> // for std::string support
#include <iostream>
#include <fstream>

int main() {
    // Create a YAML tree
    ryml::Tree tree;

    // Root node (map)
    auto root = tree.rootref();
    root |= ryml::MAP;

    // Add "learnt" languages (sequence)
    root["learnt"] |= ryml::SEQ;
    root["learnt"].append_child() << "C++";
    root["learnt"].append_child() << "Python";

    // Add "want-to-learn" languages (sequence)
    root["want-to-learn"] |= ryml::SEQ;
    root["want-to-learn"].append_child() << "Ruby";
    root["want-to-learn"].append_child() << "Rust";

    // Add nested groups (e.g., "vulkan-features" as a map of groups)
    root["vulkan-features"] |= ryml::MAP;
    root["vulkan-features"]["raytracing"] |= ryml::MAP;
    root["vulkan-features"]["raytracing"]["supported"] << true;
    root["vulkan-features"]["raytracing"]["maxRecursionDepth"] << 31;

    root["vulkan-features"]["computeShaders"] |= ryml::MAP;
    root["vulkan-features"]["computeShaders"]["supported"] << true;
    root["vulkan-features"]["computeShaders"]["maxWorkgroupSize"] << 1024;

    // Emit YAML to a string
    std::string yaml = ryml::emitrs<std::string>(tree);

    // Write to file
    std::ofstream("data.yaml") << yaml;

    // Print to console
    std::cout << "Generated YAML:\n" << yaml << "\n";

    return 0;
}
```