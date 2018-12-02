#include "aeroflot/GraphView.h"
#include "doctest.h"

TEST_CASE("GraphView works")
{
    std::unique_ptr<GraphView> graph(new GraphView);
    CHECK_NOTHROW(graph->print());
}
