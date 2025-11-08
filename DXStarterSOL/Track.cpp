#include "Track.h"

// find location at n distance along track
Vector2 Track::findPos(float progress) {
    assert(progress <= length);
    Vector2 pos = points[0]; // for holding the running total for return value
    Vector2 dist = { 0, 0 }; // ignores signs. for holding running total of calculated distance 
    float remaining = progress;

    for (int i(0); i < points.size() - 1; i++) {
        dist += {   abs(points[i + 1].x - points[i].x), 
                    abs(points[i + 1].y - points[i].y) };
        if (dist.x + dist.y >= progress) {                           // at the first point to surpass the requested progress,
            Vector2 dir = { points[i + 1].x - points[i].x,          // in the direction of the next point,
                            points[i + 1].y - points[i].y };
            dir.Normalize();
            // pos += direction * remaining
            pos = points[i] + dir * remaining;                                 // pos = this point + remaining progress
            return pos;
        }
        else {
            // pos = points[i] + dist;                                        
            remaining = progress - (dist.x + dist.y);           // keep a running total of the distance remaining until entire progress has been made
        }
    }
    assert(false);
}
// calculate length between 2 points
float Track::getLength(Vector2 wp1, Vector2 wp2) {
    float len = sqrt((wp1.x - wp2.x) * (wp1.x - wp2.x) +
                    (wp1.y - wp2.y) * (wp1.y - wp2.y));
    return len;
}
// calculate length of entire track
float Track::calculateLength() {
    float len(0);
    for (int i(0); i < points.size() - 1; i++) {
        len += getLength(points[i], points[i + 1]);
    }
    return len;
}