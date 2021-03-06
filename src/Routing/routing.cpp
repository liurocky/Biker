/*
    Biker wants to be a routing software, intended to be useful for planning bike tours.
    Copyright (C) 2011  Lena Brueder

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/ 

#include "src/Routing/routing.hpp"

class SortByDistance
{
private:
    GPSPosition pos;
public:
    SortByDistance(GPSPosition pos) : pos(pos) {}
    inline bool operator()(const boost::shared_ptr<OSMNode> &t1, const boost::shared_ptr<OSMNode> &t2) const
    {
        return (t1->calcDistance(pos) < t2->calcDistance(pos));
    }
};

RoutingNode::RoutingNode(OSMNode parent, ID_Datatype predecessor_, float overAllCost_) :
		OSMNode(parent.getID(), GPSPosition(parent.getLon(), parent.getLat()), parent.getProperties()), predecessor(predecessor_), overallCost(overAllCost_)
{
	
}

uint qHash(RoutingNode& node)
{
	return node.getID();
}
uint qHash(boost::shared_ptr<RoutingNode>& node)
{
	return node->getID();
}


Router::Router(OSMDatabaseReader* db_, RouterMetric* metric_) :
		db(db_), metric(metric_)
{
	
}

OSMNode Router::calcStartEndNode(GPSPosition pos, double radius)
{
    OSMPropertyTreeAlwaysTrueNode alwaystrue;
    QList<boost::shared_ptr<OSMNode> > nodeList = db->getNodes(pos, radius, alwaystrue);
    
    qSort(nodeList.begin(), nodeList.end(), SortByDistance(pos) );
    
    for (QList<boost::shared_ptr<OSMNode> >::iterator it = nodeList.begin(); it < nodeList.end(); it++)
    {
        QList<boost::shared_ptr<OSMEdge> > edgeList = db->getEdges(*(it->get()), *(metric->getAssociatedPropertyTree()));
        if (!edgeList.isEmpty())
            return *(it->get());
    }
    
    return OSMNode();
}
Router::~Router()
{
	delete metric;
	//db nicht löschen! brauchen wir ja noch soanders.
}

void HashClosedList::addNode(ID_Datatype nodeID)
{
	hashtable << nodeID;
}
void HashClosedList::removeNode(ID_Datatype nodeID)
{
	hashtable.remove(nodeID);
}
bool HashClosedList::contains(ID_Datatype nodeID)
{
	return hashtable.contains(nodeID);
}
int HashClosedList::size()
{
	return hashtable.size();
}
