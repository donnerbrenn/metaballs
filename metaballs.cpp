#include "metaballs.h"

using namespace std;

metaballs::metaballs(uint width, uint height, uint vCount, bool vsync)
{
    this->vCount=vCount;
    this->width=width;
    this->height=height;
    this->vsync=vsync;

    createFrame();

    metaballShader.loadFromFile("metaball_vShader.glsl","metaball_fShader.glsl");
    metaball_renderStates.shader=&metaballShader;
    metaballShader.setUniform("vCount",int(vCount));

    createVertices();
    vertexBuffer = VertexBuffer(Points,VertexBuffer::Usage::Dynamic);// new VertexBuffer(Points,VertexBuffer::Usage::Dynamic);
    vertexBuffer.create(vCount);
    window=new RenderWindow(VideoMode(width,height),"Metaballs");
    window->setVerticalSyncEnabled(vsync);
    mainLoop();
}

metaballs::~metaballs()
{
    if(window)
        delete window;
}

void metaballs::createFrame()
{
    frameVertices.emplace_back(Vector2f(0,0));
    frameVertices.emplace_back(Vector2f(0,height));
    frameVertices.emplace_back(Vector2f(width,height));

    frameVertices.emplace_back(Vector2f(0,0));
    frameVertices.emplace_back(Vector2f(width,0));
    frameVertices.emplace_back(Vector2f(width,height));

    frameVB=VertexBuffer(Triangles,VertexBuffer::Usage::Dynamic);
    frameVB.create(6);
    frameVB.update(frameVertices.data());
}

bool metaballs::collide(Vector2f posA, Vector2f posB, float radius)
{
    float distance;

    distance=sqrt(posA.x*posA.x+posB.y*posB.y);

    if(distance<radius)
        return true;
    else
        return false;
}

void metaballs::mainLoop()
{
    Event e;
    bool quit=false;

    while (!quit) {
        window->clear();

        Glsl::Vec2 vectors[1023];
        for(uint i=0;i<vCount;i++)
        {
            vectors[i].x=particleVertices[i].position.x;
            vectors[i].y=particleVertices[i].position.y;
        }

        metaballShader.setUniformArray("vectors",vectors,vCount);
//        metaballShader.setUniform("width",float(width));
        window->draw(frameVB,metaball_renderStates);
        window->display();
        move();
        while(window->pollEvent(e))
        {
            if(e.type==Event::Closed)
                quit=true;
        }
    }
}



void metaballs::createVertices()
{
    Color col(255,255,255,255);
    for(uint i=0;i<vCount;i++)
    {
        Vector2f v;
        v.x=uint(rand())%width;
        v.y=uint(rand())%height;
        particleVertices.emplace_back(Vertex(v,col));

        if(rand()%2)
            v.x=randomSpeed();
        else {
            v.x=-randomSpeed();
        }

        if(rand()%2)
            v.y=randomSpeed();
        else {
            v.y=-randomSpeed();
        }

        particleVelocities.emplace_back(v);
    }
}


void metaballs::move()
{
    for(uint i=0;i<particleVertices.size();i++)
    {
        particleVertices[i].position+=particleVelocities[i].position;
        if(particleVertices[i].position.x<=0)
            particleVelocities[i].position.x*=-1;

        if(particleVertices[i].position.y<=0)
            particleVelocities[i].position.y*=-1;

        if(particleVertices[i].position.x>=width)
            particleVelocities[i].position.x*=-1;

        if(particleVertices[i].position.y>=height)
            particleVelocities[i].position.y*=-1;

//        for(uint j=0;j<particleVertices.size();j++)
//        {
//            if(i!=j)
//                if(collide(particleVertices[i].position,particleVertices[j].position,30))
//                {
//                    particleVelocities[i].position.x*=-1;
//                    particleVelocities[i].position.y*=-1;

//                    particleVelocities[j].position.x*=-1;
//                    particleVelocities[j].position.y*=-1;
//                }
//        }
    }
}

float metaballs::randomSpeed()
{
    return (rand()%4+1)*.25;
}

