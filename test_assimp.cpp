#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "spdlog/spdlog.h"

#define ASSIMP_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals)

int main() {
    const std::string filename {"../assets/bizon.obj"};

    Assimp::Importer importer;
    const aiScene* res = importer.ReadFile(filename, ASSIMP_FLAGS);
    if (res == 0) {
        spdlog::error("Failed to read file {}.", filename);
        exit(1);
    }
    {
        spdlog::info("Loaded mesh from file {}.", filename);
    }

    spdlog::info("Model has meshes: {}", res->mNumMeshes);

    return 0;
}