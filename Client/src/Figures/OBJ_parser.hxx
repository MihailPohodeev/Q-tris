#ifndef _OBJ_PARSER_H_
#define _OBJ_PARSER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class OBJParser
{
    int size;
    int indices_count;
    GLuint VBO[2], VAO, EBO;
    
public:

    OBJParser( const std::string& str ) : size(0), indices_count(0)
    {
        std::ifstream ifs( str );
        std::string a;
        
        while(std::getline( ifs, a ))
        {
            if ( a[0] == 'v' )
                ++size;
            if ( a[0] == 'f' )
                indices_count += 3;
        }
        ifs.close();
        ifs = std::ifstream( str );
        std::cout << size << ' ' << indices_count / 3 << '\n';
        
        GLfloat* pos   = new GLfloat[size * 3];
        GLfloat* norm  = new GLfloat[size * 3];
        GLint* indices = new GLint[indices_count];
        
        int index_pos  = 0;
        int index_norm = 0;
        int index_ind  = 0;
        while (std::getline( ifs, a ))
        {
            std::string temp;
            
            if ( a[0] == 'v' && a[1] == 'n' )
            {
                std::stringstream ss(a);
                ss >> temp;
                ss >> temp;
                norm[index_norm]     = (GLfloat)(std::stof(temp));
                ss >> temp;
                norm[index_norm + 1] = (GLfloat)(std::stof(temp));
                ss >> temp;
                norm[index_norm + 2] = (GLfloat)(std::stof(temp));
                index_norm += 3;
            }
            else if ( a[0] == 'v' )
            {
                std::stringstream ss(a);
                ss >> temp;
                ss >> temp;
                pos[index_pos]     = (GLfloat)(std::stof(temp));
                ss >> temp;
                pos[index_pos + 1] = (GLfloat)(std::stof(temp));
                ss >> temp;
                pos[index_pos + 2] = (GLfloat)(std::stof(temp));
                index_pos += 3;
            }
            else if ( a[0] == 'f' )
            {
                std::string t = "";
                std::stringstream ss(a);
                ss >> temp;
                
                while( ss >> temp )
                {
                    t = "";
                    for ( int i = 0; i < temp.size() && temp[i] != '/'; ++i )
                        t += temp[i];
                    indices[index_ind] = (GLint)(std::stoi(t) - 1);
                    ++index_ind;
                }
            }            
        }
        ifs.close();
        
        //for ( int i = 0; i < size * 3; i += 3 )
        //  std::cout << pos[i] << ' ' << pos[i + 1] << ' ' << pos[i + 2] << '\n';
        
        //for ( int i = 0; i < index_ind; i += 3 )
        //  std::cout << indices[i] << ' ' << indices[i + 1] << ' ' << indices[i + 2] << '\n';
        
        glGenBuffers( 2, VBO );
        glGenBuffers( 1, &EBO );
        glGenVertexArrays( 1, &VAO );
        glBindVertexArray( VAO );
        
        GLuint posVBO = VBO[0];
        GLuint normVBO = VBO[1];
        
        glBindBuffer( GL_ARRAY_BUFFER, posVBO );
        // Заполняем его данными функцией glBufferData
        glBufferData( GL_ARRAY_BUFFER, 3 * size * sizeof(GLfloat), pos, GL_DYNAMIC_DRAW );
        // Биндим VBO: glBindBuffer
        glBindBuffer( GL_ARRAY_BUFFER, normVBO );
        // Заполняем его данными функцией glBufferData
        glBufferData( GL_ARRAY_BUFFER, 3 * size * sizeof(GLfloat), norm, GL_DYNAMIC_DRAW );
        // Биндим EBO: glBindBuffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // Заполняем его данными функцией glBufferData
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count * sizeof(GLint), indices, GL_DYNAMIC_DRAW);
    
        // Создаём VAO
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glBindBuffer( GL_ARRAY_BUFFER, posVBO );
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glBindBuffer( GL_ARRAY_BUFFER, normVBO );
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        
        glBindVertexArray( 0 );
        
        delete [] pos;
        delete [] norm;
    }
    
    ~OBJParser()
    {
        glDeleteVertexArrays( 1, &VAO );
        glDeleteBuffers( 2, VBO );
        glDeleteBuffers( 1, &EBO );
    }
    
    GLfloat getVAO() const
    {
        return VAO;
    }
    
    int getVertexesCount() const
    {
        return size;
    }
    
    int getIndicesCount() const
    {
        return indices_count;
    }
};

#endif
