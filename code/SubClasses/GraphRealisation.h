#pragma once

#include <iostream>

#include "../Classes/Math.h"
#include "../Types/AllTypes.h"

using namespace GraphTypes;

class Connection;
class DirectConnection;
class Graph;
class PhysicConnection;
class Point;

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
    Connection Swap();
    void SwapThis();
    
    void operator=(Connection connection);
    bool operator==(Connection connection);
    bool operator!=(Connection connection);
    bool operator<(Connection connection);
    bool operator>(Connection connection);
    
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
    bool operator!=(DirectConnection connection);
    
    ~DirectConnection();
};

std::ostream& operator<<(std::ostream& stream, Connection connection);



class Graph
{
private:
    //Next connections -- connections are existing after "from_connection".
    Connection* GetNextConnectionsArray(point_t connection_index);
    point_t GetNextConnectionsCount(point_t connection_index);
    bool IsHaveCycleAsConnected();
protected:
    point_t connections_count;
    Connection* connections;
public:
    Graph();
    Graph(const Graph& graph);
    Graph(Connection* connections, point_t connections_count);
    Graph(MatNI matrix);
    Graph(MatNI* matrix);
    
    bool Divide(Graph* return_graph);
    //The function return count of all connections.
    point_t GetConnectionsCount();
    //The function return count of indicated connection.
    point_t GetConnectionsCount(Connection connection);
    //The function return count of indicated connection.
    point_t GetConnectionsCount(Connection* connection);
    //The function return count of conections that collect indicated point.
    point_t GetConnectionsCount(point_t p);
    point_t GetMaxPoint();
    point_t* GetPointsArray();
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
    
    //Properties
    
    bool IsBasic();
    bool IsConnected();
    bool IsHaveCycle();
    bool IsTree();
    
    //Properties
    
    void Sort();
    
    //only sorted
    
    unsigned GetHight();
    unsigned GetWidth();
    
    //only sorted
    
    void operator=(Graph graph);
    bool operator==(Graph graph);
    bool operator!=(Graph graph);
    
    ~Graph();
};

std::ostream& operator<<(std::ostream& stream, Graph graph);

class Point
{
public:
    float radius;
    Vec2F position;
    float text_size;
    point_t number;
    
    Point(const Point& point);
    Point(
        point_t number = POINT_DEFAULT_NUMBER,
        Vec2F position = POINT_DEFAULT_POSITION,
        float radius = POINT_DEFAULT_RADIUS,
        float text_size = POINT_TEXT_SIZE_AUTO);
    
    char* GetNumberAsTextC();
    int* GetNumberAsTextI();
    unsigned GetNumberTextLength();
    void Update();
    
    void operator=(Point point);
    
    ~Point();
};

//Broked line with three segments.
class PhysicConnection
{
protected:
    Vec2F p1;
    Vec2F p2;
    
    //p1_p -> p1 -> p2 -> p2_p
    
public:
    Vec2F* p1_p;//pointer to pisition of point
    Vec2F* p2_p;//pointer to pisition of point
    float shift_x;
    float shift_y;
    
    PhysicConnection(const PhysicConnection& connection);
    PhysicConnection(
        Point* p1,
        Point* p2,
        float center_parameter = CONNECTION_DEFAULT_DISTANCE_TO_POINT,
        float shift = CONNECTION_DEFAULT_SHIFT);
    Segment GetSegment(ConnectionTypes::segment_id_t segment_id = CONNECTION_SEGMENT_ID_CENTER);
    void Update();
    
    void operator=(PhysicConnection connection);
    
    ~PhysicConnection();
};








