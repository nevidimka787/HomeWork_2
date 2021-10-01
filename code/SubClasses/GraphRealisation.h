#include <iostream>

#include "../Classes/Mat.h"
#include "../Types/AllTypes.h"

using namespace GraphTypes;

class Connection;
class DirectConnection;
class Graph;

class Connection
{
protected:
    point_t p1;
    point_t p2;
    
public:
    Connection();
    Connection(const Connection& connection);
    Connection(point_t p1, point_t p2);
    
    void ChangePoint1(point_t value);
    void ChangePoint2(point_t value);
    point_t GetPoint1();
    point_t GetPoint2();
    point_t GetMaxPoint();
    point_t GetMinPoint();
    bool IsCollectPoint(point_t p);
    void Set(Connection* connection);
    void Set(point_t p1, point_t p2);
    Connection Swap();
    void SwapThis();
    
    void operator=(Connection connection);
    bool operator==(Connection connection);
    
    ~Connection();
};

class DirectConnection : public Connection
{
public:
    DirectConnection();
    DirectConnection(const DirectConnection& connection);
    DirectConnection(point_t p1, point_t p2);
    
    void Set(DirectConnection* connection);
    DirectConnection Swap();
    
    void operator=(DirectConnection connection);
    bool operator==(DirectConnection connection);
    
    ~DirectConnection();
};

std::ostream& operator<<(std::ostream& stream, Connection connection);



class Graph
{
protected:
    point_t connections_count;
    Connection* connections;
public:
    Graph();
    Graph(const Graph& graph);
    Graph(Connection* connections, point_t connections_count);
    Graph(MatNI matrix);
    Graph(MatNI* matrix);
    
    //The function return count of all connections.
    point_t GetConnectionsCount();
    //The function return count of indicated connection.
    point_t GetConnectionsCount(Connection connection);
    //The function return count of indicated connection.
    point_t GetConnectionsCount(Connection* connection);
    //The function return count of conections that collect indicated point.
    point_t GetConnectionsCount(point_t p);
    point_t GetPointsCount();
    //The function create a new block of memory and return pointer to it.
    //The function can return nullptr.
    //Don't foget clear this block after use.
    Connection* GetConnectionsArray();
    //The function create a new block of memory and return pointer to it.
    //The functin return connections that have indicated point.
    //The function can return nullptr.
    //Don't foget clear this block after use.
    Connection* GetConnectionsArray(point_t point_number);
    bool IsCollectPoint(point_t point_number);
    
    void operator=(Graph graph);
    bool operator==(Graph graph);
    
    ~Graph();
};

std::ostream& operator<<(std::ostream& stream, Graph graph);







