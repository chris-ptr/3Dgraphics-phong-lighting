#include "Sphere.h"
#include <iostream>

const float PI = 3.14159265359f;
const float TAU = 6.28318530717f;


Sphere::Sphere(unsigned int xSegments, unsigned int ySegments)
{

    Vertex vertex;
    glm::vec3 vector;

    for (unsigned int y = 0; y <= ySegments; ++y)
    {
        for (unsigned int x = 0; x <= xSegments; ++x)
        {

            Vertex vertex;
            glm::vec3 vector;

            float xSegment = (float)x / (float)xSegments;
            float ySegment = (float)y / (float)ySegments;
            float xPos = std::cos(xSegment * TAU) * std::sin(ySegment * PI); // TAU is 2PI
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * TAU) * std::sin(ySegment * PI);


            vector.x = xPos;
            vector.y = yPos;
            vector.z = zPos;

            vertex.Position = vector;
            vertex.TexCoords = glm::vec2(xSegment, ySegment);
            vertex.Normal = vector;

            vertices.push_back(vertex);

        }
    }

    bool oddRow = false;
    for (int y = 0; y < ySegments; ++y)
    {
        for (int x = 0; x < xSegments; ++x)
        {
            Indices.push_back((y + 1) * (xSegments + 1) + x);
            Indices.push_back(y * (xSegments + 1) + x);
            Indices.push_back(y * (xSegments + 1) + x + 1);

            Indices.push_back((y + 1) * (xSegments + 1) + x);
            Indices.push_back(y * (xSegments + 1) + x + 1);
            Indices.push_back((y + 1) * (xSegments + 1) + x + 1);
        }
    }


    // You must implement this function!
    setupSphere();
}


void Sphere::setupSphere() {
    std::cout << "Setting up sphere..." << std::endl;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);

    std::cout << "Sphere setup completed! VAO: " << VAO << std::endl;
}



void Sphere::Draw() {
    if (VAO == 0) {
        std::cerr << "ERROR: Sphere VAO is not initialized!" << std::endl;
        return;
    }

    glBindVertexArray(VAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode to make it visible
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(Indices.size()), GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Restore normal rendering
    glBindVertexArray(0);
}





glm::vec3 Sphere::getPosition(float time) {
    float radius = 3.0f;  // Orbit radius
    float speed = 2.0f;   // Rotation speed
    float x = radius * cos(speed * time);
    float y = 1.5f;       // Fixed height
    float z = radius * sin(speed * time);
    return glm::vec3(x, y, z);
}
