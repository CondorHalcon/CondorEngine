#pragma once
#include <CondorEngine.hpp>
#include <CondorEngine/serialization.hpp>
#include <yaml-cpp/yaml.h>

using namespace CondorEngine;

namespace CondorEditor
{
    class Serializer
    {
    public:
        static YAML::Node SerializeScene(Scene* scene) {
            YAML::Node root;
            root["Scene"]["Version"] = 1;

            // sceneobjects
            YAML::Node objectsNode = root["Scene"]["Objects"];
            for (SceneObject* obj : scene->hierarchy) {
                YAML::Node objNode = SerializeSceneObject(obj);
                objectsNode.push_back(objNode);
            }

            return root;
        }
        static YAML::Node SerializeSceneObject(SceneObject* sceneObject) {
            YAML::Node objectNode;
            objectNode["id"] = sceneObject->id;
            objectNode["name"] = sceneObject->name;

            // components
            YAML::Node componentsNode = objectNode["Components"];
            for (Component* comp : sceneObject->components) {
                YAML::Node compNode = SerializeComponent(comp);
                componentsNode.push_back(compNode);
            }

            // children
            YAML::Node childrenNode = objectNode["Children"];
            for (SceneObject* child : sceneObject->children) {
                YAML::Node childNode = SerializeSceneObject(child);
                childrenNode.push_back(childNode);
            }

            return objectNode;
        }
        static YAML::Node SerializeComponent(Component* component) {
            YAML::Node componentNode;
            componentNode["Type"] = component->GetType();

            // fields
            YAML::Node fieldsNode = componentNode["Fields"];
            std::vector<FieldInfo> fields;
            component->GetTypeInfo()->CollectFields(fields);
            for (const FieldInfo& field : fields) {
                if (!(field.flags & FieldFlags::Save)) {
                    continue;
                }

                void* data = (char*)component + field.offset;
                SerializeField(fieldsNode, field, data);
            }

            return componentNode;
        }
        static void SerializeField(YAML::Node& node, const FieldInfo& field, void* data) {
            TypeInfo* typeInfo = ReflectionRegistry::GetType(field.type);
            // TODO fix
            /*if (typeInfo->Serialize != nullptr) {
                typeInfo->Serialize(data);
            }*/
        }

        static Scene* DeserializeScene(YAML::Node node) {
            Scene* scene;
            for (auto objNode : node["Scene"]["Objects"]) {
                SceneObject* sceneObject = DeserializeSceneObject(objNode);
                scene->Instantiate(sceneObject);
            }

            return scene;
        }
        static SceneObject* DeserializeSceneObject(YAML::Node node) {
            SceneObject* sceneObject = new SceneObject();
            sceneObject->id = node["id"].as<unsigned int>();
            sceneObject->name = node["name"].as<std::string>();

            for (auto compNode : node["Components"]) {
                Component* component = DeserializeComponent(compNode);
                sceneObject->AddComponent(component);
            }

            for (auto childNode : node["Children"]) {
                SceneObject* child = DeserializeSceneObject(childNode);
                child->setParent(sceneObject);
            }

            return sceneObject;
        }
        static Component* DeserializeComponent(YAML::Node node) {
            std::string type = node["Type"].as<std::string>();
            Component* component = new Component(); // TODO: change to component factory

            std::vector<FieldInfo> fields;
            component->GetTypeInfo()->CollectFields(fields);

            for (auto& field : fields) {
                if (!(field.flags & FieldFlags::Save)) { continue; }
                if (!node["Fields"][field.name]) { continue; }

                void* data = (char*)component + field.offset;
                DeserializeField(node["Fields"], field, data);
            }

            return component;
        }
        static void DeserializeField(YAML::Node& node, const FieldInfo& field, void* data) {
            TypeInfo* type = ReflectionRegistry::GetType(field.type);
            // TODO fix
            /*if (type != nullptr && type->Deserialize != nullptr) {
                type->Deserialize(data);
            }*/
        }
    };
}