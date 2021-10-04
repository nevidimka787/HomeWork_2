#include "GraphRealisation.h"

Connection::Connection() :
    p1(0),
    p2(0)
{
}

Connection::Connection(const Connection& connection) :
    p1(connection.p1),
    p2(connection.p2)
{
}

Connection::Connection(point_t p1, point_t p2) :
    p1(p1),
    p2(p2)
{
}


void Connection::ChangePoint1(point_t value)
{
    p1 = value;
}

void Connection::ChangePoint2(point_t value)
{
    p2 = value;
}

point_t Connection::GetPoint1()
{
    return p1;
}

point_t Connection::GetPoint2()
{
    return p2;
}

point_t Connection::GetMaxPoint()
{
    if(p1 > p2)
    {
        return p1;
    }
    return p2;
}

point_t Connection::GetMinPoint()
{
    if(p1 > p2)
    {
        return p2;
    }
    return p1;
}

bool Connection::IsCollectPoint(point_t p)
{
    return p1 == p || p2 == p;
}

Connection Connection::Swap()
{
    return Connection(p2, p1);
}

void Connection::SwapThis()
{
    point_t temp = p1;
    p1 = p2;
    p2 = temp;
}

void Connection::operator=(Connection connection)
{
    p1 = connection.p1;
    p2 = connection.p2;
}

bool Connection::operator==(Connection connection)
{
    return
        p1 == connection.p1 && p2 == connection.p2 ||
        connection.p1 == p2 && connection.p2 == p1;
}

Connection::~Connection()
{
}

std::ostream& operator<<(std::ostream& stream, Connection connection)
{
    stream << connection.GetPoint1() << " --- " << connection.GetPoint2();
}



DirectConnection::DirectConnection() :
    Connection()
{
}

DirectConnection::DirectConnection(const DirectConnection& connection) :
    Connection(connection.p1, connection.p2)
{
}

DirectConnection::DirectConnection(point_t p1, point_t p2) :
    Connection(p1, p2)
{
}

DirectConnection DirectConnection::Swap()
{
    return DirectConnection(p2, p1);
}

void DirectConnection::operator=(DirectConnection connection)
{
    p1 = connection.p1;
    p2 = connection.p2;
}

bool DirectConnection::operator==(DirectConnection connection)
{
    return
        p1 == connection.p1 && p2 == connection.p2;
}



Graph::Graph() :
    connections_count(0),
    connections(nullptr)
{
}

Graph::Graph(const Graph& graph) :
    connections_count(graph.connections_count)
{
    if(connections_count == 0)
    {
        connections = nullptr;
        return;
    }
    
    connections = new Connection[connections_count];
    
    for(point_t connection = 0; connection < connections_count; connection++)
    {
        connections[connection] = graph.connections[connection];
    }
}

Graph::Graph(Connection* connections, point_t connections_count) :
    connections_count(connections_count)
{
    if(connections_count == 0)
    {
        this->connections = nullptr;
        return;
    }
    
    this->connections = new Connection[connections_count];
    
    for(point_t connection = 0; connection < connections_count; connection++)
    {
        this->connections[connection] = connections[connection];
    }
}

Graph::Graph(MatNI matrix) :
    connections_count(0)
{
    unsigned matrix_size = matrix.GetSize();
    if(matrix_size == 0)
    {
        connections_count = 0;
        std::cout << "ERROR::GRAPH::Input matrix is null." << std::endl;
        return;
    }
    unsigned values_count = matrix_size * matrix_size;
    int* values = matrix.GetValuesArray();
    
    for(unsigned i = 0; i < values_count; i++)
    {
        connections_count += values[i];
    }
    
    if(connections_count == 0)
    {
        connections = nullptr;
        return;
    }
    
    connections = new Connection[connections_count];
    
    point_t connection = 0;
    for(unsigned i = 0; i < values_count; i++)
    {
        if(values[i] != 0)
        {
            connections[connection] = Connection(i % matrix_size, i / matrix_size);
            connection++;
            if(connection == connections_count)
            {
                delete[] values;
                return;
            }
        }
    }
    
    delete[] values;
}

Graph::Graph(MatNI* matrix) :
    connections_count(0)
{
    unsigned matrix_size = matrix->GetSize();
    if(matrix_size == 0)
    {
        connections_count = 0;
        std::cout << "ERROR::GRAPH::Input matrix is null." << std::endl;
        return;
    }
    unsigned values_count = matrix_size * matrix_size;
    int* values = matrix->GetValuesArray();
    
    for(unsigned i = 0; i < values_count; i++)
    {
        connections_count += values[i];
    }
    
    if(connections_count == 0)
    {
        connections = nullptr;
        return;
    }
    
    connections = new Connection[connections_count];
    
    point_t connection = 0;
    for(unsigned i = 0; i < values_count; i++)
    {
        if(values[i] != 0)
        {
            connections[connection] = Connection(i % matrix_size, i / matrix_size);
            connection++;
            if(connection == connections_count)
            {
                delete[] values;
                return;
            }
        }
    }
    
    delete[] values;
}

point_t Graph::GetConnectionsCount()
{
    return connections_count;
}

point_t Graph::GetConnectionsCount(Connection connection)
{
    if(connections_count == 0)
    {
        return 0;
    }
    
    point_t return_count = 0;
    
    for(point_t i = 0; i < connections_count; i++)
    {
        if(connections[i] == connection)
        {
            return_count++;
        }
    }
    
    return return_count;
}

point_t Graph::GetConnectionsCount(Connection* connection)
{
    if(connections_count == 0)
    {
        return 0;
    }
    
    point_t return_count = 0;
    
    for(point_t i = 0; i < connections_count; i++)
    {
        if(connections[i] == *connection)
        {
            return_count++;
        }
    }
    
    return return_count;
}

point_t Graph::GetConnectionsCount(point_t p)
{
    if(connections_count == 0)
    {
        return 0;
    }
    
    point_t count = 0;
    
    for(point_t c = 0; c < connections_count; c++)
    {
        if(connections[c].IsCollectPoint(p))
        {
            count++;
        }
    }
    return count;
}

point_t Graph::GetPointsCount()
{
    if(connections_count == 0)
    {
        return 0;
    }
    
    point_t max_point = 0;
    point_t temp_point;
    
    for(point_t c = 0; c < connections_count; c++)
    {
        temp_point = connections[c].GetMaxPoint();
        if(max_point < temp_point)
        {
            max_point = temp_point;
        }
    }
    
    temp_point = 0;
    
    for(point_t p = 0; p <= max_point; p++)
    {
        for(point_t c = 0; c < connections_count; c++)
        {
            if(connections[c].IsCollectPoint(p))
            {
                temp_point++;
                break;
            }
        }
    }
    
    return temp_point;
}

Connection* Graph::GetConnectionsArray()
{
    if(connections_count == 0)
    {
        return nullptr;
    }
    
    Connection* return_connections_array = new Connection[connections_count];
    
    for(point_t c = 0; c < connections_count; c++)
    {
        return_connections_array[c] = connections[c];
    }
    
    return return_connections_array;
}

Connection* Graph::GetConnectionsArray(point_t p)
{
    if(connections_count == 0)
    {
        return nullptr;
    }
    
    point_t count = GetConnectionsCount(p);
    Connection* return_connections_array = new Connection[count];
    
    for(point_t c = 0, rc = 0; c < connections_count; c++)
    {
        if(connections[c].IsCollectPoint(p))
        {
            return_connections_array[rc] = connections[c];
            rc++;
            if(rc == count)
            {
                return return_connections_array;
            }
        }
    }
    
    return return_connections_array;
}

bool Graph::IsCollectPoint(point_t p)
{
    if(connections_count == 0)
    {
        return false;
    }
    
    for(point_t c = 0; c < connections_count; c++)
    {
       if(connections[c].IsCollectPoint(p))
       {
           return true;
       }
    }
    return false;
}

void Graph::operator=(Graph graph)
{
    if(connections_count > 0)
    {
        delete[] connections;
    }
    connections_count = graph.connections_count;
    if(connections_count == 0)
    {
        connections = nullptr;
        return;
    }
    
    connections = new Connection[connections_count];
    
    for(point_t c = 0; c < connections_count; c++)
    {
       connections[c] = graph.connections[c];
    }
}

Graph::~Graph()
{
    if(connections_count > 0)
    {
        delete[] connections;
    }
}

std::ostream& operator<<(std::ostream& stream, Graph graph)
{
    point_t connections_count = graph.GetConnectionsCount();
    if(connections_count != 0)
    {
        Connection* connections = graph.GetConnectionsArray();

        for(point_t c = 0; c < connections_count; c++)
        {
            stream  << connections[c] << std::endl;
        }
        delete[] connections;
        std::cout << "";
    }
}



Point::Point(const Point& point) :
    number(point.number),
    position(point.position),
    radius(point.radius),
    text_size(point.text_size)
{
}

Point::Point(point_t number, Vec2F position, float radius, float text_size) :
    number(number),
    position(position),
    radius(radius)
{
    if(text_size != text_size)
    {
        this->text_size = fminf(1.0f / (float)GetNumberTextLength() * POINT_NORMAL_TEXT_SIZE, POINT_MAX_TEXT_SIZE);
        std::cout << "Text size: " << this->text_size << std::endl;
        return;
    }
    this->text_size = text_size;
}

int* Point::GetNumberAsTextI()
{
    int* text;
    if(number == 0)
    {
        text = new int[2];
        text[0] = '0';
        text[1] = '\0';
    }
    unsigned text_length = GetNumberTextLength();
    
    text = new int[text_length + 1];
    point_t temp = number;
    
    for(unsigned i = text_length; i > 0; i--)
    {
        text[i - 1] = '0' + (temp % 10);
        temp /= 10;
    }
    text[text_length] = '\0';
    return text;
}

char* Point::GetNumberAsTextC()
{
    char* text;
    if(number == 0)
    {
        text = new char[2];
        text[0] = '0';
        text[1] = '\0';
    }
    unsigned text_length = 0u;
    
    for(point_t n = number; n > 0; n /= 10)
    {
        text_length++;
    }
    
    text = new char[text_length + 1];
    point_t temp = number;
    
    for(unsigned i = text_length; i > 0; i--)
    {
        text[i - 1] = '0' + (temp % 10);
        temp /= 10;
    }
    text[text_length] = '\0';
}

unsigned Point::GetNumberTextLength()
{
    if(number == 0)
    {
        return 1u;
    }
    unsigned l = 0u;
    for(point_t n = number; n > 0; n /= 10)
    {
        l++;
    }
    return l;
}

void Point::Update()
{
    if(text_size != text_size)
    {
        text_size = fminf(1.0f / (float)GetNumberTextLength() * POINT_NORMAL_TEXT_SIZE, POINT_MAX_TEXT_SIZE);
    }
}

void Point::operator=(Point point)
{
    number = point.number;
    position = point.position;
    radius = point.radius;
    text_size = point.text_size;
}

Point::~Point()
{
}



PhysicConnection::PhysicConnection(const PhysicConnection& connection) :
    p1_p(connection.p1_p),
    p2_p(connection.p2_p),
    p1(connection.p1),
    p2(connection.p2),
    center_parameter(connection.center_parameter),
    shift(connection.shift)
{
}

PhysicConnection::PhysicConnection(Point* point_1, Point* point_2, float center_parameter, float shift) :
    p1_p(&point_1->position),
    p2_p(&point_2->position),
    center_parameter(center_parameter),
    shift(shift)
{    
    Update();
}

Segment PhysicConnection::GetSegment(ConnectionTypes::segment_id_t segment_id)
{
    if(segment_id == CONNECTION_SEGMENT_ID_START)
    {
        return Segment(p1_p, &p1, true);
    }
    if(segment_id == CONNECTION_SEGMENT_ID_END)
    {
        return Segment(&p2, p2_p, true);
    }
    return Segment(p1, p2, true);
}

void PhysicConnection::Update()
{
    Vec2F vec = (*p2_p - *p1_p).Normalize().Perpendicular() * shift;
    Vec2F center = (*p2_p - *p1_p) / 2.0f;
    p1 = *p1_p + center * (1.0f - center_parameter) + vec;
    p2 = *p2_p - center * (1.0f - center_parameter) + vec;
}

void PhysicConnection::operator=(PhysicConnection connection)
{
    p1_p = connection.p1_p;
    p2_p = connection.p2_p;
    p1 = connection.p1;
    p2 = connection.p2;
    shift = connection.shift;
    center_parameter = connection.center_parameter;
}

PhysicConnection::~PhysicConnection()
{
}



























