//
// Created by Madison on 8/27/2020.
//
/*
 * Usage:
 * Recommend putting the highest level of the code in a try/catch, i.e.:
 *
    try
    {
       // everything
    }
    catch(const std::exception & e)
    {
        std::cerr << "exception: " << e.what() << "\n";
        throw;
    }
 *
 * You can also put specific calls on lines that might cause problems, i.e.:
 *
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    throw_if_gl_error(EXC_MSG("glDrawArrays failed."));
 *
 * In the event this function call fails, this outputs:
 * "exception: glDrawArrays failed. (path\to\file.cpp:linenumber) - Err. Or code: <errorcode>"
 * It's very useful.
 */

#include "glerror_utility.h"

void throw_if_gl_error(std::string msg)
{
    if(GLenum err; (err = glGetError()) != GL_NO_ERROR)
    {
        std::ostringstream ss;
        ss << msg << " - Error code: " << err;
        throw std::runtime_error(ss.str());
    }
}

std::string exception_message(std::string message, const char * filename, std::size_t line)
{
    std::ostringstream ss;
    ss << message << " (" << filename << ":" << line << ")";
    return ss.str();
}

