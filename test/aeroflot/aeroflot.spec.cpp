#include "aeroflot/GraphView.h"
#include "doctest.h"

TEST_CASE("GraphView works")
{
    GraphView graph;
    CHECK_NOTHROW(graph.print());
}
