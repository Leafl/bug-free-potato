#ifndef _SHADER_PROGRAM_H_
#define _SHADER_PROGRAM_H_

#define GLEW_STATIC

/**************************
 **** GRAPHICS INCLUDES ***
 *************************/

#include <GL/glew.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>

using std::string;
using std::cerr;
using std::endl;

#define BUFFER_OFFSET(i) ((void*)(intptr_t)(i))

typedef struct
{
    GLenum type;
    const char* filename;
    GLuint shader;
} ShaderInfo;

class Shader
{
private:
    GLuint ShaderProgramId;
    void initialize(string[]);
    GLuint LoadShaders(ShaderInfo*);
    const GLchar* ReadShader(const char*);

public:
    // Turn this shader off and on
    void useProgram();
    void stopUsingProgram();

    // Interact with the shaders via GLSL and OpenGL API
    GLint GetVariable(string);
    void SetFloat(GLint, const GLfloat);
    void SetMatrix4(GLint, GLsizei, GLboolean, const GLfloat*);
    void SetMatrix3(GLint, GLsizei, GLboolean, const GLfloat*);
    void SetVector3(GLint, GLsizei, const GLfloat*);

    Shader(string[], bool);
};




#endif


/* Parts of this class were copied from gametutorials.com. 
 
 
 */
