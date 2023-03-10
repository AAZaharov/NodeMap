#include <QPainter>

#include "edge.h"
#include "node.h"

#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

Edge::Edge(Node* sourceNode, Node* destNode)
   : arrowSize(10)
{
   setAcceptedMouseButtons(0);
   source = sourceNode;
   dest = destNode;
   source->addEdge(this);
   dest->addEdge(this);
   adjust();
}

Node* Edge::sourceNode() const
{
   return source;
}

Node* Edge::destNode() const
{
   return dest;
}

void Edge::adjust()
{
   if (!source || !dest)
      return;

   QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
   qreal length = line.length();

   prepareGeometryChange();

   if (length > qreal(20.)) {
      QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
      sourcePoint = line.p1() + edgeOffset;
      destPoint = line.p2() - edgeOffset;
   }
   else {
      sourcePoint = destPoint = line.p1();
   }
}

QRectF Edge::boundingRect() const
{
   if (!source || !dest)
      return QRectF();

   qreal penWidth = 1;
   qreal extra = (penWidth + arrowSize) / 2.0;

   return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
      destPoint.y() - sourcePoint.y()))
      .normalized()
      .adjusted(-extra, -extra, extra, extra);
}

