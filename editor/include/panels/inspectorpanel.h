#pragma once
#include "editorpanel.h"
#include "serialization.hpp"
#include <string>

using namespace CondorEngine;

namespace CondorEditor
{
    class InspectorPanel : public EditorPanel
    {
    private:
        static inline InspectorPanel* instance = nullptr;
    public:
        static InspectorPanel* Instance() {
            if (instance == nullptr) {
                instance = new InspectorPanel();
            }
            return instance;
        }

        virtual const char* getTitle() { return "Inspector"; }

        static inline std::vector<std::string> specialFieldNames = { "name", "enabled", "components", "hierarchy", "children" };
        static inline bool isSpecialFieldName(const char* fieldName);

        virtual void OnGui() override;
    private:
        static void DrawObjectAsField(FieldInfo& field, void* data);
    };
}