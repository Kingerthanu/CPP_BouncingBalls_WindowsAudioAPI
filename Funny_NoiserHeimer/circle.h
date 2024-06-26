#ifndef CIRCLE_H
#define CIRCLE_H

#include "Vertex_Array.h"
#include "Element_Buffer.h"
#include "Audio_Driver.h"
#include <vector>
#include <cmath>

class Circle
{

private:
    VAO arrayBuffer;
    VBO vertexBuffer;
    const unsigned int segments = 15;
    //EBO elementBuffer;
    float xCoord, yCoord;
    const float radius = 0.05f;
    float velocity[2];
    const glm::vec3 color;

public:

    bool isOverlap(const float& xCoord, const float& yCoord, const float& radius) const
    {
        // Calculate distance between centers of the circles
        float dx = this->xCoord - xCoord;
        float dy = this->yCoord - yCoord;
        float distance = std::sqrt(dx * dx + dy * dy);

        return distance < (this->radius + radius);
    }

    Circle(const float& xNormalized, const float& yNormalized, const float& xVelocity,
           const float& yVelocity, const float& newRadius = 0.05f, const unsigned int& segAmnt = 15, const glm::vec3& newColor = { 0.8f, 0.2f, 0.5f }) : radius(newRadius), segments(segAmnt), color(newColor)
    {

        this->velocity[0] = xVelocity;
        this->velocity[1] = yVelocity;

        std::vector<Vertex> vertices;

        // Calculate circle vertices

        for (int i = 0; i < this->segments; ++i) {
            float angle = 2.0f * 3.1415926f * i / this->segments;
            float x = xNormalized + radius * std::cos(angle);
            float y = yNormalized + radius * std::sin(angle);
            vertices.push_back(Vertex{ glm::vec2{x, y}, color });
        }

        this->xCoord = xNormalized;
        this->yCoord = yNormalized;

        // Create vertex buffer
        this->vertexBuffer = VBO(vertices);

        // Bind VAO
        this->arrayBuffer.Bind();

        // Link vertex buffer with VAO
        this->arrayBuffer.LinkAttrib(this->vertexBuffer, 0, 2, GL_FLOAT, sizeof(Vertex), (void*)0);
        this->arrayBuffer.LinkAttrib(this->vertexBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(sizeof(float) * 2));

        // Unbind VAO
        this->arrayBuffer.unBind();

    };

    

    void tick()
    {
        
        float newOriginX = this->xCoord + this->velocity[0], newOriginY = this->yCoord + this->velocity[1];
    
        if ((-1.0f <= newOriginX && newOriginX <= 1.0f) && (-1.0f <= newOriginY && newOriginY <= 1.0f)) {
            //  std::cout << "In Bounds\n";

            this->vertexBuffer.Bind();

            Vertex* bufferData = static_cast<Vertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));

            for (int i = 0; i < segments; ++i) {

                bufferData[i].position[0] += velocity[0];
                bufferData[i].position[1] += velocity[1];
                bufferData[i].color *= 1.01f;

            }

            glUnmapBuffer(GL_ARRAY_BUFFER);

            this->velocity[1] -= 0.004f;
            this->xCoord = newOriginX;
            this->yCoord = newOriginY;
            this->update();


        }
        else {

            this->vertexBuffer.Bind();

            Vertex* bufferData = static_cast<Vertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));

            for (int i = 0; i < segments; ++i) {

                bufferData[i].color = { 0.8f, 0.2f, 0.5f };

            }

            glUnmapBuffer(GL_ARRAY_BUFFER);

            
           //  std::cout << "Out of Bounds\n";
            this->velocity[0] *= -10.95f;
            this->velocity[1] *= -10.95f;

        }


        

    }

    void tick(Audio_Driver& _Audio, Circle& boundingCircle)
    {

        float newOriginX = this->xCoord + this->velocity[0], newOriginY = this->yCoord + this->velocity[1];

        //if ((-1.0f <= newOriginX && newOriginX <= 1.0f) && (-1.0f <= newOriginY && newOriginY <= 1.0f)) {
        if (boundingCircle.isOverlap(newOriginX, newOriginY, this->radius)) {
            //  std::cout << "In Bounds\n";

            this->vertexBuffer.Bind();

            Vertex* bufferData = (Vertex*)(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));

            for (int i = 0; i < segments; ++i) {

                bufferData[i].position[0] += velocity[0];
                bufferData[i].position[1] += velocity[1];
                // bufferData[i].color *= 1.01f;

            }

            glUnmapBuffer(GL_ARRAY_BUFFER);

            this->velocity[1] -= 0.0008f;
            this->velocity[0] *= 1.001f;
            this->xCoord = newOriginX;
            this->yCoord = newOriginY;
            this->update();


        }
        else {


            this->vertexBuffer.Bind();

            Vertex* bufferData = (Vertex*)(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));

            glm::vec3 newColor = { ((std::rand() % 255) / 255.0f), ((std::rand() % 255) / 255.0f), ((std::rand() % 255) / 255.0f) };

            for (int i = 0; i < segments; ++i) {

                bufferData[i].color = newColor;

            }

            glUnmapBuffer(GL_ARRAY_BUFFER);



            // Check if velocity is below the threshold for terminal velocity
            if (( std::sqrt(this->velocity[0] * this->velocity[0] + this->velocity[1] * this->velocity[1]) ) < 0.1f) {
                // If velocity is below threshold, multiply by a factor slightly greater than -1.0f
                this->velocity[0] *= -0.99f;
                this->velocity[1] *= -0.99f;
            }
            else {
                // If velocity is not below threshold, multiply by -1.0f
                this->velocity[0] = -this->velocity[0];
                this->velocity[1] = -this->velocity[1];
            }

            //this->update();

            //if (this->velocity[0] < 0.05f && this->velocity[1] < 0.05f) {

                //_Audio.Write_Sound_Thread(std::abs((this->velocity[0] * 10000.0f) + (this->velocity[0] * 10000.0f)) * 37532.145614, 0.0025);
                _Audio.Write_Sound_Thread(std::abs(this->velocity[0]), std::abs(this->velocity[1]));
           // }
            
            

        }




    }


    void update()
    {
       
        this->arrayBuffer.Bind();
        this->vertexBuffer.Bind();

        glDrawArrays(GL_LINE_LOOP, 0, this->segments);

    }

};

#endif
