#include "JsonSerializer.h"

JsonSerializer::JsonSerializer() {}
JsonSerializer::~JsonSerializer() {}

string JsonSerializer::GetType() {
    return "json";
}

string JsonSerializer::Serialize(JsonSerializable* object) {
    Json::Value root;
    Json::FastWriter writer;

    object->Serialize(root);

    return writer.write(root);
}

string JsonSerializer::Serialize(vector<JsonSerializable*>* list) {
    Json::Value jsonList( Json::arrayValue );
    for(int i = 0; i != list->size(); i++) {
        Json::Value item;
        list->at(i)->Serialize(item);
        jsonList.append(item);
    }
    Json::FastWriter writer;
    return writer.write(jsonList);
}

void JsonSerializer::Deserialize(string source, JsonSerializable* object) {
    Json::Value root;
    Json::Reader reader;

    if (!reader.parse(source, root)) {
        std::cout  << "Failed to parse sources\n";
    } else {
        object->Deserialize(root);
    }
}
