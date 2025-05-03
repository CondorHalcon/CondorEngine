#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <regex>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

std::string preprocessShader(
    const fs::path& filePath,
    const fs::path& baseDir,
    std::unordered_set<std::string>& includedFiles,
    const std::vector<fs::path>& includePaths
) {
    // open shader
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open shader file: " + filePath.string());
    }

    std::stringstream output;
    std::string line;

    // regex
    std::regex includeRegex(R"(^\s*#include\s+<(.+?)>\s*$)");

    // parse
    while (std::getline(file, line)) {
        std::smatch match;

        // include another shader file
        if (std::regex_match(line, match, includeRegex)) {
            fs::path includePath = baseDir / match[1].str();

            // search other include folders
            if (!fs::exists(includePath)) {
                for (const auto& path : includePaths) {
                    fs::path candidatePath = path / match[1].str();
                    if (fs::exists(candidatePath)) {
                        includePath = candidatePath;
                        break;
                    }
                }
            }
            if (!fs::exists(includePath)) {
                throw std::runtime_error("Include file not found: " + match[1].str());
            }
            includePath = fs::canonical(includePath);

            // add include
            if (!includedFiles.count(includePath.string())) {
                includedFiles.insert(includePath.string());
                output << "// Begin include: " << includePath.filename() << "\n";
                output << preprocessShader(includePath, includePath.parent_path(), includedFiles, includePaths);
                output << "// End include: " << includePath.filename() << "\n";
            }
        }
        // no matches
        else {
            output << line << '\n';
        }
    }

    return output.str();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: shader_preprocessor <input_shader> <output_shader> [include_paths...]\n";
        return 1;
    }

    fs::path inputPath(argv[1]);
    fs::path outputPath(argv[2]);
    fs::path baseDir = inputPath.parent_path();

    // Collect additional include paths
    std::vector<fs::path> includePaths;
    for (int i = 3; i < argc; ++i) {
        includePaths.emplace_back(argv[i]);
    }

    try {
        std::unordered_set<std::string> includedFiles;
        std::string processedShader = preprocessShader(inputPath, baseDir, includedFiles, includePaths);

        std::ofstream outFile(outputPath);
        if (!outFile.is_open()) {
            throw std::runtime_error("Failed to write output shader: " + outputPath.string());
        }
        outFile << processedShader;
        std::cout << "Shader preprocessed to: " << outputPath << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
