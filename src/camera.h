#ifndef CAMERA_H
#define CAMERA_H

#include "vector_util.h"
#include <SFML/System.hpp>

extern const size_t WINDOW_WIDTH;
extern const size_t WINDOW_HEIGHT;
extern const float WORLD_WIDTH;
extern const float WORLD_HEIGHT;

class Camera {
public:
    Camera(const sf::Vector2f& windowSize, const sf::Vector2f& viewCenterWorld,
           float worldUnitsPerPixel = 1.f)
        : mWindowSize{windowSize},
          mViewCenterWorld{viewCenterWorld},
          mWorldUnitsPerPixel{worldUnitsPerPixel} {}

    // TODO: all of these:

    sf::Vector2f windowToWorld(const sf::Vector2f& pWindow)
    {
        sf::Vector2f temp; 
        temp.x = (pWindow.x/WINDOW_WIDTH) * WORLD_WIDTH * mWorldUnitsPerPixel;
        temp.y = (pWindow.y/WINDOW_HEIGHT) * WORLD_HEIGHT * mWorldUnitsPerPixel;
        return {temp};
    };

    sf::Vector2f worldToWindow(const sf::Vector2f& pWorld)
    {
        sf::Vector2f temp;
        temp.x = (pWorld.x/WORLD_WIDTH/mWorldUnitsPerPixel) * WINDOW_WIDTH;
        temp.y = (pWorld.y/WORLD_HEIGHT/mWorldUnitsPerPixel) * WINDOW_HEIGHT;
        return {temp};
    };

    sf::Vector2f windowPercentToWorld(const sf::Vector2f& pWindowPercent)
    {
        sf::Vector2f temp;
        temp.x = pWindowPercent.x * WORLD_WIDTH;
        temp.y = pWindowPercent.y * WORLD_HEIGHT;
        return {temp};
    };

    sf::Vector2f worldToWindowPercent(const sf::Vector2f& pWorld)
    {
        sf::Vector2f temp;
        temp.x = pWorld.x / WORLD_WIDTH;
        temp.y = pWorld.y / WORLD_HEIGHT;
        return {temp};
    };

    void translateWorld(const sf::Vector2f& deltaWorld)
    {
        mViewCenterWorld.x += deltaWorld.x;
        mViewCenterWorld.y += deltaWorld.y;
    };

    void translateWindow(const sf::Vector2f& deltaScreen)
    {
        mViewCenterWorld.x += ((deltaScreen.x * mWorldUnitsPerPixel / WINDOW_WIDTH) * WORLD_WIDTH);
        mViewCenterWorld.y += ((deltaScreen.y * mWorldUnitsPerPixel / WINDOW_HEIGHT) * WORLD_HEIGHT);
    };

    void translateWindowPercent(const sf::Vector2f& deltaScreenPercent)
    {
        mViewCenterWorld.x += (deltaScreenPercent.x * WORLD_WIDTH);
        mViewCenterWorld.y += (deltaScreenPercent.y * WORLD_HEIGHT);
    };

    void setCamera(const sf::Vector2f& pWorld, const sf::Vector2f& pWindow)
    {
        sf::Vector2f diff;
        diff.x = ((pWindow.x / WINDOW_WIDTH * mWorldUnitsPerPixel) * WORLD_WIDTH) - pWorld.x;
        diff.x = ((pWindow.y / WINDOW_HEIGHT * mWorldUnitsPerPixel) * WORLD_HEIGHT) - pWorld.y;
        mViewCenterWorld.x += diff.x;
        mViewCenterWorld.y += diff.y;
    };

    void setCameraPercent(const sf::Vector2f& pWorld, const sf::Vector2f& pWindowPercent)
    {
        sf::Vector2f diff;
        diff.x = pWindowPercent.x * WORLD_WIDTH - pWorld.x;
        diff.y = pWindowPercent.y * WORLD_HEIGHT - pWorld.y;
        mViewCenterWorld.x += diff.x;
        mViewCenterWorld.y += diff.y;
    };

    void setCameraCenter(const sf::Vector2f& pWorld)
    {
        mViewCenterWorld.x = pWorld.x;
        mViewCenterWorld.y = pWorld.y;
    };

    sf::Vector2f getCameraCenter() const
    {
        return {mViewCenterWorld};
    };

private:
    sf::Vector2f mWindowSize;       // size of the window in screen pixels (i.e. window coords)
    sf::Vector2f mViewCenterWorld;  // world coords point corresponding to the center of our window.
    float mWorldUnitsPerPixel;      // distance in world coords covered by one pixel
};

#endif  // CAMERA_H
