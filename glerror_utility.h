//
// Created by Madison on 8/27/2020.
//

#include <iostream>
#include <string>
#include <sstream>

#include "include/GLEW/glew.h"
#include "include/GLFW/glfw3.h"

#ifndef GLERROR_UTILITY_H
#define GLERROR_UTILITY_H

#define EXC_MSG(msg) exception_message(msg, __FILE__, __LINE__)

void throw_if_gl_error(std::string msg);
std::string exception_message(std::string message, const char * filename, std::size_t line);

#endif //GLERROR_UTILITY_H

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