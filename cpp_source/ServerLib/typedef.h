#pragma once

class Client;

class FieldMap;
class FieldObject;
class FieldObjectComponent;
class FieldObjectFSM;

typedef std::unique_ptr<FieldObjectComponent> UPtrComp;
typedef std::unique_ptr<FieldObjectFSM> UPtrFSM;

typedef std::shared_ptr<Client> SPtrClient;
typedef std::shared_ptr<FieldMap> SPtrMap;
typedef std::shared_ptr<FieldObject> SPtrObj;