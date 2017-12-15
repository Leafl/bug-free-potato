#include "Shader.hpp"

// The only constructor to be used is one that takes in file names for the 
//   shaders. If the second argument is 'true', start using this one now
// Pre: None
// Post: The shaders are initialized

Shader::Shader(string names[], bool useThisProgram)
{
    initialize(names);

    if(useThisProgram)
    {
	useProgram();
    }
}

// This function takes in a list of filenames (shaderTexts) and creates
//   a shader program out of it.
// Pre: shaderTexts contains strings
// Post: The shader program has been created

void Shader::initialize(string names[])
{
    // load shader info
    ShaderInfo shaders[]={
	{ GL_VERTEX_SHADER, names[0].c_str()},
	{ GL_FRAGMENT_SHADER, names[1].c_str()},
	{ GL_NONE, NULL},
    };

    // set shader program
    ShaderProgramId=LoadShaders(shaders);
}

// This function was stolen from OpenGL Red Book sample code
// It takes in a block of "shader info" and loads the appropriate shaders
// from their respective files
// Pre: shaders contains an array of strings with filenames for various 
//   shaders, including their types
// Post: The shaders are read from the files, compiled, and the program
//   ID is returned.

GLuint Shader::LoadShaders(ShaderInfo* shaders)
{
    if(shaders==NULL)
    {
	return 0;
    }

    GLuint program=glCreateProgram();

    ShaderInfo* entry=shaders;
    while(entry->type!=GL_NONE)
    {
	GLuint shader=glCreateShader(entry->type);

	entry->shader=shader;

	const GLchar* source=ReadShader(entry->filename);
	if(source==NULL)
	{
	    for(entry=shaders; entry->type!=GL_NONE; ++entry)
	    {
		glDeleteShader(entry->shader);
		entry->shader=0;
	    }

	    return 0;
	}

	glShaderSource(shader, 1, &source, NULL);
	delete [] source;

	glCompileShader(shader);

	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(!compiled)
	{
#ifdef _DEBUG
	    GLsizei len;
	    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

	    GLchar* log=new GLchar[len+1];
	    glGetShaderInfoLog(shader, len, &len, log);
	    std::cerr<<"Shader compilation failed: "<<log<<std::endl;
	    delete [] log;
#endif /* DEBUG */

	    return 0;
	}

	glAttachShader(program, shader);

	++entry;
    }

    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if(!linked)
    {
#ifdef _DEBUG
	GLsizei len;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

	GLchar* log=new GLchar[len+1];
	glGetProgramInfoLog(program, len, &len, log);
	std::cerr<<"Shader linking failed: "<<log<<std::endl;
	delete [] log;
#endif /* DEBUG */

	for(entry=shaders; entry->type!=GL_NONE; ++entry)
	{
	    glDeleteShader(entry->shader);
	    entry->shader=0;
	}

	return 0;
    }

    return program;
}

// This helper function reads in GLSL from a shader file
// Pre: filename is the name of a file, relative path, pointing to a shader
// Post: The shader is read in and a char* containing the shader text
//   is returned

const GLchar* Shader::ReadShader(const char* filename)
{
    FILE* infile=fopen(filename, "rb");

    if(!infile)
    {
#ifdef _DEBUG
	std::cerr<<"Unable to open file '"<<filename<<"'"<<std::endl;
#endif /* DEBUG */
	return NULL;
    }

    fseek(infile, 0, SEEK_END);
    int len=ftell(infile);
    fseek(infile, 0, SEEK_SET);

    GLchar* source=new GLchar[len+1];

    fread(source, 1, len, infile);
    fclose(infile);

    source[len]=0;

    return const_cast<const GLchar*> (source);
}


// This function shifts the currently-used shader program to this shader
// Pre: None
// Post: The program is now rendering using this shader program

void Shader::useProgram()
{
    glUseProgram(ShaderProgramId);
}

// This function stops using this shader program as the current shader program
// Pre: This is the currently-used shader program
// Post: No longer

void Shader::stopUsingProgram()
{
    glUseProgram(0);
}


// This function retrieves the ID number of a given GLSL variable name
// Pre: The name cannot be empty
// Post: The variable's name is used to retrieve the GLSL ID of the variable

GLint Shader::GetVariable(std::string strVariable)
{
    // If we don't have an active program object, let's return -1
    if(!ShaderProgramId)
	return -1;

    // This returns the variable Id for a variable in a shader file
    return glGetUniformLocation(ShaderProgramId, strVariable.c_str());
}


// This allows us to pass in 4x4 matrix (float array of 16) to a shader 
//    by the Id received from GetVariable()
// Pre: None
// Post: A particular uniform 4x4 matrix is assigned a value

void Shader::SetMatrix4(GLint id, GLsizei count, GLboolean transpose,
			const GLfloat *value)
{
    glUniformMatrix4fv(id, count, transpose, value);
}

void Shader::SetMatrix3(GLint id, GLsizei count, GLboolean transpose,
			const GLfloat *value)
{
    glUniformMatrix3fv(id, count, transpose, value);
}


// This allows us to pass in 3x1 vector (float array of 3) to a shader 
//    by the Id received from GetVariable()
// Pre: None
// Post: A particular uniform 4x4 matrix is assigned a value

void Shader::SetVector3(GLint id, GLsizei count, const GLfloat *value)
{
    glUniform3fv(id, count, value);
}

void Shader::SetFloat(GLint id, GLfloat value)
{
    glUniform1f(id, value);
}