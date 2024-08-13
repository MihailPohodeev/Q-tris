#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../setup.hxx"
#include "../Shader.hxx"
#include "OBJ_parser.hxx"

class Element
{
    glm::vec2 _position;
    glm::vec4 _color;
    OBJParser _model;
    Shader _shader;

    glm::mat4 _modelMatrix;
    
public:
    Element(const glm::vec3& size): _model("Models/Sphere.obj"), _shader("Shaders/shader.verx", "Shaders/shader.frag") 
    {
        _modelMatrix = glm::scale(glm::mat4(1.f), size);
    }
    ~Element() {}
    void set_color(const glm::vec4&);
    glm::vec4 get_color() const;
    void render()
    {
        _shader.use();
        _shader.setMat4("Model", _modelMatrix);
        glBindVertexArray( _model.getVAO() );
        glDrawElements(GL_TRIANGLES, _model.getIndicesCount(), GL_UNSIGNED_INT, 0);
    }
};

#endif