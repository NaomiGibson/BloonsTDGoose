#include "Track.h"


void Track::init(ResourceManager& rm, MyD3D& d3d) {
    length = calculateLength();
    //rm.loadTexture(d3d, L"../bin/data/IndicatorLine.dds", "indicatorLine");
    //db_spr.init(rm.loadTexture(d3d, L"../bin/data/Indicator.dds", "indicator"), { 0, 0, 4, 4 }, points[0], 0, { 1, 1 });
    db_spr.setOrigin({ 0.5, 0.5 });
}
void Track::db_render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
    for (unsigned int i(1); i < points.size(); i++) {
        db_spr.setTexName("indicatorLine");
        float length = getLength(points[i - 1], points[i]);
        if (points[i].x > points[i - 1].x) { // if the x is bigger than the last, it is a horizontal line going right
            db_spr.setOrigin({ 0, 0.5 });
            db_spr.setScale({ length / 4, 1 });
        }
        else if (points[i].y > points[i - 1].y) {// if the y is bigger than the last, it is a vertical line going down
            db_spr.setOrigin({ 0.5, 0 });
            db_spr.setScale({ 1, length / 4 });
        }
        else if (points[i].x < points[i - 1].x) { // if the x is smaller than the last, it is a horizontal line going left
            db_spr.setOrigin({ 1, 0.5 });            
            db_spr.setScale({ length / 4, 1 });
        }
        else if (points[i].y < points[i - 1].y) { // if the y is smaller than the last, it is a vertical line going up
            db_spr.setOrigin({ 0.5, 1 });            
            db_spr.setScale({ 1, length / 4 });
        }
        db_spr.render(d3d, rm, dTime, batch);

        db_spr.setTexName("indicator");
        db_spr.setPos(points[i]);
        db_spr.setOrigin({ 0.5, 0.5 });
        db_spr.setScale({ 2, 2 });
        db_spr.render(d3d, rm, dTime, batch);
    }
}

// find location at n distance along track
Vector2 Track::findPos(float progress) {
    assert(progress <= length);
    Vector2 pos = points[0]; // for holding the running total for return value
    Vector2 dist = { 0, 0 }; // ignores signs. for holding running total of calculated distance 
    float remaining = progress;

    for (unsigned int i(0); i < points.size() - 1; i++) {
        dist += {   abs(points[i + 1].x - points[i].x), 
                    abs(points[i + 1].y - points[i].y) };
        if (dist.x + dist.y >= progress) {                          // at the first point to surpass the requested progress,
            Vector2 dir = { points[i + 1].x - points[i].x,              // in the direction of the next point,
                            points[i + 1].y - points[i].y };
            dir.Normalize();
            pos = points[i] + dir * remaining;                          // pos = this point + remaining progress
            return pos;
        }
        else {                                   
            remaining = progress - (dist.x + dist.y);               // keep a running total of the distance remaining until entire progress has been made
        }
    }
    assert(false);
    return { 0, 0 };
}
float Track::getProgressAtPoint(int point) {
    assert(point <= points.size());
    float len(0);
    for (int i(0); i < point - 1; i++) {
        len += getLength(points[i], points[i + 1]);
    }
    return len;
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
    for (unsigned int i(0); i < points.size() - 1; i++) {
        len += getLength(points[i], points[i + 1]);
    }
    return len;
}
bool Track::isOverlappingSection(Vector2 otherCentre, float otherRad) {
    bool isOverlapping{ false };
    for (int section(1); section < points.size(); section++) {
        Vector2 rectPos; // top left of this track section
        rectPos.x = (points[section].x < points[section - 1].x) ? points[section].x - (width / 2) : points[section - 1].x - (width / 2);
        rectPos.y = (points[section].y < points[section - 1].y) ? points[section].y - (width / 2) : points[section - 1].y - (width / 2);
        Vector2 rectSize; // width and height of this track section
        rectSize.x = abs((points[section].x - points[section - 1].x + width));
        rectSize.y = abs((points[section].y - points[section - 1].y + width));
        Vector2 dist; // distance between the other circle and this track section
        Vector2 otherPos = { otherCentre.x - otherRad, otherCentre.y - otherRad };
        Vector2 otherSize = { otherRad * 2, otherRad * 2 };
        if (
            rectPos.x < otherPos.x + otherSize.x &&
            rectPos.x + rectSize.x > otherPos.x &&
            rectPos.y < otherPos.y + otherSize.y &&
            rectPos.y + rectSize.y > otherPos.y
            ) {
            isOverlapping = true;
        }
    }

    return isOverlapping;
}
bool Track::isOverlapping(Vector2 centre, float rad) {
    return false;
}