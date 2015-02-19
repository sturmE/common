#ifndef __gl_utils_h__
#define __gl_utils_h__

#include <string>
#include <OpenGL/gl3.h>
#include "../../foundation/Logging.h"

static const char* glEnumName(GLenum _enum) {
#define GLENUM(_ty) case _ty: return #_ty
    
    switch (_enum)
    {
            GLENUM(GL_TEXTURE);
            GLENUM(GL_RENDERBUFFER);
            
            GLENUM(GL_INVALID_ENUM);
            GLENUM(GL_INVALID_VALUE);
            GLENUM(GL_INVALID_OPERATION);
            GLENUM(GL_OUT_OF_MEMORY);
            
            GLENUM(GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
            GLENUM(GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
            //          GLENUM(GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER);
            //          GLENUM(GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER);
            GLENUM(GL_FRAMEBUFFER_UNSUPPORTED);
            GLENUM(GL_FLOAT_VEC2);
            GLENUM(GL_FLOAT_VEC3);
            GLENUM(GL_FLOAT_VEC4);
            GLENUM(GL_FLOAT_MAT2);
            GLENUM(GL_FLOAT_MAT3);
            GLENUM(GL_FLOAT_MAT4);
            GLENUM(GL_SAMPLER_2D);
            GLENUM(GL_SAMPLER_CUBE);
    }
}

#ifndef NDEBUG
#   define GL_CHECK(func) \
do { \
func;\
GLenum err = glGetError(); \
if(err != GL_NO_ERROR) { LOG_E(LogChannel::Graphics, "GL error " << err << ": " << #func << "-->" << glEnumName(err)); }  \
}  \
while (false)
#else
#   define GL_CHECK(func) func
#endif

#endif