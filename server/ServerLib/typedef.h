#pragma once

class Client;

class FieldMap;
class FieldObject;
class FieldObjectComponent;
class FieldObjectFSM;

typedef google::protobuf::Message MSG;

typedef std::unique_ptr<FieldObjectComponent> UPtrComp;
typedef std::unique_ptr<FieldObjectFSM> UPtrFSM;
typedef std::unique_ptr<MSG> UPtrMessage;

typedef std::shared_ptr<Client> SPtrClient;
typedef std::shared_ptr<FieldMap> SPtrMap;
typedef std::shared_ptr<FieldObject> SPtrObj;
typedef std::shared_ptr<MSG> SPtrMessage;