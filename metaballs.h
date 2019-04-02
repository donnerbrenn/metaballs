#ifndef METABALLS_H
#define METABALLS_H
#include <SFML/Graphics.hpp>
#include <vector>
#include<random>
#include<math.h>

using namespace sf;

class metaballs
{
public:
    metaballs(uint width, uint height, uint vCount, bool vsync);
    ~metaballs();

private:
    RenderWindow *window;
    VertexBuffer vertexBuffer;
    std::vector<sf::Vertex> particleVertices;
    std::vector<sf::Vertex> particleVelocities;
    Shader metaballShader;
    RenderStates metaball_renderStates;

    void createFrame();

    std::vector<Vertex> frameVertices;
    VertexBuffer frameVB;

    bool collide(Vector2f posA, Vector2f posB, float radius);


    uint width;
    uint height;
    uint vCount;
    bool vsync;
    void mainLoop();
    void createVertices();
    void move();
    float randomSpeed();


};

#endif // METABALLS_H
