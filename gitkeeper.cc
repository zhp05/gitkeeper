#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void process_directory(const fs::path& dir) {
    bool has_content = false;
    bool has_empty_file = false;

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_directory()) {
            process_directory(entry.path());
            has_content = true;
        } else if (entry.is_regular_file()) {
            if (entry.path().filename() == "empty") {
                has_empty_file = true;
            } else {
                has_content = true;
            }
        }
    }

    fs::path empty_file = dir / "empty";

    if (!has_content) {
        // 如果是空目录，创建empty文件
        if (!has_empty_file) {
            std::ofstream(empty_file).close();
            std::cout << "Created empty file in: " << dir << std::endl;
        }
    } else {
        // 如果不是空目录，删除empty文件（如果存在）
        if (has_empty_file && fs::exists(empty_file)) {
            fs::remove(empty_file);
            std::cout << "Removed empty file from: " << dir << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    fs::path root_dir = argc > 1 ? argv[1] : ".";

    try {
        if (!fs::exists(root_dir)) {
            std::cerr << "Error: Directory does not exist: " << root_dir << std::endl;
            return 1;
        }

        std::cout << "Processing directory: " << fs::absolute(root_dir) << std::endl;
        process_directory(root_dir);
        std::cout << "Done!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}