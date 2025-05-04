#pragma once
#include <CondorEngine.hpp>
#include <CondorEngine/Rendering.hpp>
#include <CondorEngine/rendering/renderfeatures/colorrenderfeature.hpp>
#include <CondorEngine/rendering/renderfeatures/directionalshadowmappingrenderfeature.hpp>

using namespace CondorEngine;
using namespace CondorEngine::Rendering;

class ToonRenderer : public Renderer
{
public:
    ToonRenderer() {}

    virtual void init() override {
        Renderer::init();

        // initialize render features
        features = std::vector<RenderFeature*>{
            new ColorRenderFeature(),
            DirectionalShadowMappingRenderFeature::Instance()
        };
    }
};