/*
 * bindings.cc
 *
 *  Created on: Dec 13, 2011
 *      Author: ngk437
 */


#include "gl.h"
#include "image.h"
#include <cstdlib>

#define JS_GL_CONSTANT(name) target->Set(JS_STR( #name ), JS_INT(GL_ ## name))

extern "C" {
void init(Handle<Object> target)
{
  atexit(gl::AtExit);
  atexit(Image::AtExit);

  Image::Initialize(target);

  NODE_SET_METHOD(target, "Init", gl::Init);
 
  NODE_SET_METHOD(target, "uniform1f", gl::Uniform1f);
  NODE_SET_METHOD(target, "uniform2f", gl::Uniform2f);
  NODE_SET_METHOD(target, "uniform3f", gl::Uniform3f);
  NODE_SET_METHOD(target, "uniform4f", gl::Uniform4f);
  NODE_SET_METHOD(target, "uniform1i", gl::Uniform1i);
  NODE_SET_METHOD(target, "uniform2i", gl::Uniform2i);
  NODE_SET_METHOD(target, "uniform3i", gl::Uniform3i);
  NODE_SET_METHOD(target, "uniform4i", gl::Uniform4i);
  NODE_SET_METHOD(target, "uniform1fv", gl::Uniform1fv);
  NODE_SET_METHOD(target, "uniform2fv", gl::Uniform2fv);
  NODE_SET_METHOD(target, "uniform3fv", gl::Uniform3fv);
  NODE_SET_METHOD(target, "uniform4fv", gl::Uniform4fv);
  NODE_SET_METHOD(target, "uniform1iv", gl::Uniform1iv);
  NODE_SET_METHOD(target, "uniform2iv", gl::Uniform2iv);
  NODE_SET_METHOD(target, "uniform3iv", gl::Uniform3iv);
  NODE_SET_METHOD(target, "uniform4iv", gl::Uniform4iv);
  NODE_SET_METHOD(target, "pixelStorei", gl::PixelStorei);
  NODE_SET_METHOD(target, "bindAttribLocation", gl::BindAttribLocation);
  NODE_SET_METHOD(target, "getError", gl::GetError);
  NODE_SET_METHOD(target, "drawArrays", gl::DrawArrays);
  NODE_SET_METHOD(target, "uniformMatrix2fv", gl::UniformMatrix2fv);
  NODE_SET_METHOD(target, "uniformMatrix3fv", gl::UniformMatrix3fv);
  NODE_SET_METHOD(target, "uniformMatrix4fv", gl::UniformMatrix4fv);

  NODE_SET_METHOD(target, "generateMipmap", gl::GenerateMipmap);

  NODE_SET_METHOD(target, "getAttribLocation", gl::GetAttribLocation);
  NODE_SET_METHOD(target, "depthFunc", gl::DepthFunc);
  NODE_SET_METHOD(target, "viewport", gl::Viewport);
  NODE_SET_METHOD(target, "createShader", gl::CreateShader);
  NODE_SET_METHOD(target, "shaderSource", gl::ShaderSource);
  NODE_SET_METHOD(target, "compileShader", gl::CompileShader);
  NODE_SET_METHOD(target, "getShaderParameter", gl::GetShaderParameter);
  NODE_SET_METHOD(target, "getShaderInfoLog", gl::GetShaderInfoLog);
  NODE_SET_METHOD(target, "createProgram", gl::CreateProgram);
  NODE_SET_METHOD(target, "attachShader", gl::AttachShader);
  NODE_SET_METHOD(target, "linkProgram", gl::LinkProgram);
  NODE_SET_METHOD(target, "getProgramParameter", gl::GetProgramParameter);
  NODE_SET_METHOD(target, "getUniformLocation", gl::GetUniformLocation);
  NODE_SET_METHOD(target, "clearColor", gl::ClearColor);
  NODE_SET_METHOD(target, "clearDepth", gl::ClearDepth);

  NODE_SET_METHOD(target, "disable", gl::Disable);
  NODE_SET_METHOD(target, "createTexture", gl::CreateTexture);
  NODE_SET_METHOD(target, "bindTexture", gl::BindTexture);
  NODE_SET_METHOD(target, "texImage2D", gl::TexImage2D);
  NODE_SET_METHOD(target, "texParameteri", gl::TexParameteri);
  NODE_SET_METHOD(target, "texParameterf", gl::TexParameterf);
  NODE_SET_METHOD(target, "clear", gl::Clear);
  NODE_SET_METHOD(target, "useProgram", gl::UseProgram);
  NODE_SET_METHOD(target, "createFramebuffer", gl::CreateFramebuffer);
  NODE_SET_METHOD(target, "bindFramebuffer", gl::BindFramebuffer);
  NODE_SET_METHOD(target, "framebufferTexture2D", gl::FramebufferTexture2D);
  NODE_SET_METHOD(target, "createBuffer", gl::CreateBuffer);
  NODE_SET_METHOD(target, "bindBuffer", gl::BindBuffer);
  NODE_SET_METHOD(target, "bufferData", gl::BufferData);
  NODE_SET_METHOD(target, "bufferSubData", gl::BufferSubData);
  NODE_SET_METHOD(target, "enable", gl::Enable);
  NODE_SET_METHOD(target, "blendEquation", gl::BlendEquation);
  NODE_SET_METHOD(target, "blendFunc", gl::BlendFunc);
  NODE_SET_METHOD(target, "enableVertexAttribArray", gl::EnableVertexAttribArray);
  NODE_SET_METHOD(target, "vertexAttribPointer", gl::VertexAttribPointer);
  NODE_SET_METHOD(target, "activeTexture", gl::ActiveTexture);
  NODE_SET_METHOD(target, "drawElements", gl::DrawElements);
  NODE_SET_METHOD(target, "flush", gl::Flush);
  NODE_SET_METHOD(target, "finish", gl::Finish);

  NODE_SET_METHOD(target, "vertexAttrib1f", gl::VertexAttrib1f);
  NODE_SET_METHOD(target, "vertexAttrib2f", gl::VertexAttrib2f);
  NODE_SET_METHOD(target, "vertexAttrib3f", gl::VertexAttrib3f);
  NODE_SET_METHOD(target, "vertexAttrib4f", gl::VertexAttrib4f);
  NODE_SET_METHOD(target, "vertexAttrib1fv", gl::VertexAttrib1fv);
  NODE_SET_METHOD(target, "vertexAttrib2fv", gl::VertexAttrib2fv);
  NODE_SET_METHOD(target, "vertexAttrib3fv", gl::VertexAttrib3fv);
  NODE_SET_METHOD(target, "vertexAttrib4fv", gl::VertexAttrib4fv);

  NODE_SET_METHOD(target, "blendColor", gl::BlendColor);
  NODE_SET_METHOD(target, "blendEquationSeparate", gl::BlendEquationSeparate);
  NODE_SET_METHOD(target, "blendFuncSeparate", gl::BlendFuncSeparate);
  NODE_SET_METHOD(target, "clearStencil", gl::ClearStencil);
  NODE_SET_METHOD(target, "colorMask", gl::ColorMask);
  NODE_SET_METHOD(target, "copyTexImage2D", gl::CopyTexImage2D);
  NODE_SET_METHOD(target, "copyTexSubImage2D", gl::CopyTexSubImage2D);
  NODE_SET_METHOD(target, "cullFace", gl::CullFace);
  NODE_SET_METHOD(target, "depthMask", gl::DepthMask);
  NODE_SET_METHOD(target, "depthRange", gl::DepthRange);
  NODE_SET_METHOD(target, "disableVertexAttribArray", gl::DisableVertexAttribArray);
  NODE_SET_METHOD(target, "hint", gl::Hint);
  NODE_SET_METHOD(target, "isEnabled", gl::IsEnabled);
  NODE_SET_METHOD(target, "lineWidth", gl::LineWidth);
  NODE_SET_METHOD(target, "polygonOffset", gl::PolygonOffset);

  NODE_SET_METHOD(target, "scissor", gl::Scissor);
  NODE_SET_METHOD(target, "stencilFunc", gl::StencilFunc);
  NODE_SET_METHOD(target, "stencilFuncSeparate", gl::StencilFuncSeparate);
  NODE_SET_METHOD(target, "stencilMask", gl::StencilMask);
  NODE_SET_METHOD(target, "stencilMaskSeparate", gl::StencilMaskSeparate);
  NODE_SET_METHOD(target, "stencilOp", gl::StencilOp);
  NODE_SET_METHOD(target, "stencilOpSeparate", gl::StencilOpSeparate);
  NODE_SET_METHOD(target, "bindRenderbuffer", gl::BindRenderbuffer);
  NODE_SET_METHOD(target, "createRenderbuffer", gl::CreateRenderbuffer);

  NODE_SET_METHOD(target, "deleteBuffer", gl::DeleteBuffer);
  NODE_SET_METHOD(target, "deleteFramebuffer", gl::DeleteFramebuffer);
  NODE_SET_METHOD(target, "deleteProgram", gl::DeleteProgram);
  NODE_SET_METHOD(target, "deleteRenderbuffer", gl::DeleteRenderbuffer);
  NODE_SET_METHOD(target, "deleteShader", gl::DeleteShader);
  NODE_SET_METHOD(target, "deleteTexture", gl::DeleteTexture);
  NODE_SET_METHOD(target, "detachShader", gl::DetachShader);
  NODE_SET_METHOD(target, "framebufferRenderbuffer", gl::FramebufferRenderbuffer);
  NODE_SET_METHOD(target, "getVertexAttribOffset", gl::GetVertexAttribOffset);

  NODE_SET_METHOD(target, "isBuffer", gl::IsBuffer);
  NODE_SET_METHOD(target, "isFramebuffer", gl::IsFramebuffer);
  NODE_SET_METHOD(target, "isProgram", gl::IsProgram);
  NODE_SET_METHOD(target, "isRenderbuffer", gl::IsRenderbuffer);
  NODE_SET_METHOD(target, "isShader", gl::IsShader);
  NODE_SET_METHOD(target, "isTexture", gl::IsTexture);

  NODE_SET_METHOD(target, "renderbufferStorage", gl::RenderbufferStorage);
  NODE_SET_METHOD(target, "getShaderSource", gl::GetShaderSource);
  NODE_SET_METHOD(target, "validateProgram", gl::ValidateProgram);

  NODE_SET_METHOD(target, "texSubImage2D", gl::TexSubImage2D);
  NODE_SET_METHOD(target, "readPixels", gl::ReadPixels);
  NODE_SET_METHOD(target, "getTexParameter", gl::GetTexParameter);
  NODE_SET_METHOD(target, "getActiveAttrib", gl::GetActiveAttrib);
  NODE_SET_METHOD(target, "getActiveUniform", gl::GetActiveUniform);
  NODE_SET_METHOD(target, "getAttachedShaders", gl::GetAttachedShaders);
  NODE_SET_METHOD(target, "getParameter", gl::GetParameter);
  NODE_SET_METHOD(target, "getBufferParameter", gl::GetBufferParameter);
  NODE_SET_METHOD(target, "getFramebufferAttachmentParameter", gl::GetFramebufferAttachmentParameter);
  NODE_SET_METHOD(target, "getProgramInfoLog", gl::GetProgramInfoLog);
  NODE_SET_METHOD(target, "getRenderbufferParameter", gl::GetRenderbufferParameter);
  NODE_SET_METHOD(target, "getVertexAttrib", gl::GetVertexAttrib);
  NODE_SET_METHOD(target, "getSupportedExtensions", gl::GetSupportedExtensions);
  NODE_SET_METHOD(target, "getExtension", gl::GetExtension);
  NODE_SET_METHOD(target, "checkFramebufferStatus", gl::CheckFramebufferStatus);

  NODE_SET_METHOD(target, "frontFace", gl::FrontFace);

  NODE_SET_METHOD(target, "matrixMode", gl::MatrixMode);
  NODE_SET_METHOD(target, "loadIdentity", gl::LoadIdentity);
  NODE_SET_METHOD(target, "begin", gl::Begin);        
  NODE_SET_METHOD(target, "end", gl::End);
  
  NODE_SET_METHOD(target, "color3b", gl::Color3b);
  NODE_SET_METHOD(target, "color3s", gl::Color3s);
  NODE_SET_METHOD(target, "color3f", gl::Color3f);
  NODE_SET_METHOD(target, "color3d", gl::Color3d);
  NODE_SET_METHOD(target, "color3ub", gl::Color3ub);
  NODE_SET_METHOD(target, "color3us", gl::Color3us);
  NODE_SET_METHOD(target, "color3ui", gl::Color3ui);
  NODE_SET_METHOD(target, "color4b", gl::Color4b);
  NODE_SET_METHOD(target, "color4s", gl::Color4s);
  NODE_SET_METHOD(target, "color4f", gl::Color4f);
  NODE_SET_METHOD(target, "color4d", gl::Color4d);
  NODE_SET_METHOD(target, "color4ub", gl::Color4ub);
  NODE_SET_METHOD(target, "color4us", gl::Color4us);
  NODE_SET_METHOD(target, "color4ui", gl::Color4ui);
  
  NODE_SET_METHOD(target, "color3bv", gl::Color3bv);
  NODE_SET_METHOD(target, "color3sv", gl::Color3sv);
  NODE_SET_METHOD(target, "color3fv", gl::Color3fv);
  NODE_SET_METHOD(target, "color3dv", gl::Color3dv);
  NODE_SET_METHOD(target, "color3ubv", gl::Color3ubv);
  NODE_SET_METHOD(target, "color3usv", gl::Color3usv);
  NODE_SET_METHOD(target, "color3uiv", gl::Color3uiv);
  NODE_SET_METHOD(target, "color4bv", gl::Color4bv);
  NODE_SET_METHOD(target, "color4sv", gl::Color4sv);
  NODE_SET_METHOD(target, "color4fv", gl::Color4fv);
  NODE_SET_METHOD(target, "color4dv", gl::Color4dv);
  NODE_SET_METHOD(target, "color4ubv", gl::Color4ubv);
  NODE_SET_METHOD(target, "color4usv", gl::Color4usv);
  NODE_SET_METHOD(target, "color4uiv", gl::Color4uiv);

  NODE_SET_METHOD(target, "vertex3f", gl::Vertex3f);
  NODE_SET_METHOD(target, "rotatef", gl::Rotatef);
  NODE_SET_METHOD(target, "ortho", gl::Ortho);
  NODE_SET_METHOD(target, "translatef", gl::Translatef);
  NODE_SET_METHOD(target, "shadeModel", gl::ShadeModel);
  NODE_SET_METHOD(target, "texCoord2f", gl::TexCoord2f);

  NODE_SET_METHOD(target, "lightf", gl::Lightf);
  NODE_SET_METHOD(target, "lighti", gl::Lighti);
  NODE_SET_METHOD(target, "lightfv", gl::Lightfv);
  NODE_SET_METHOD(target, "lightiv", gl::Lightiv);

  NODE_SET_METHOD(target, "normal3b", gl::Normal3b);
  NODE_SET_METHOD(target, "normal3d", gl::Normal3d);
  NODE_SET_METHOD(target, "normal3f", gl::Normal3f);
  NODE_SET_METHOD(target, "normal3i", gl::Normal3i);
  NODE_SET_METHOD(target, "normal3s", gl::Normal3s);

  NODE_SET_METHOD(target, "normal3bv", gl::Normal3b);
  NODE_SET_METHOD(target, "normal3dv", gl::Normal3d);
  NODE_SET_METHOD(target, "normal3fv", gl::Normal3f);
  NODE_SET_METHOD(target, "normal3iv", gl::Normal3i);
  NODE_SET_METHOD(target, "normal3sv", gl::Normal3s);

  NODE_SET_METHOD(target, "polygonMode", gl::PolygonMode);  
  NODE_SET_METHOD(target, "createList", gl::CreateList);
  NODE_SET_METHOD(target, "newList", gl::NewList);
  NODE_SET_METHOD(target, "endList", gl::EndList);  
  NODE_SET_METHOD(target, "callList", gl::CallList);  
  NODE_SET_METHOD(target, "fogi", gl::Fogi);  
  NODE_SET_METHOD(target, "fogf", gl::Fogf);  
  NODE_SET_METHOD(target, "fogiv", gl::Fogiv);  
  NODE_SET_METHOD(target, "fogfv", gl::Fogfv);  

  // OpenGL ES 2.1 constants

  /* ClearBufferMask */
  JS_GL_CONSTANT(DEPTH_BUFFER_BIT);
  JS_GL_CONSTANT(STENCIL_BUFFER_BIT);
  JS_GL_CONSTANT(COLOR_BUFFER_BIT);

  /* Boolean */
  JS_GL_CONSTANT(FALSE);
  JS_GL_CONSTANT(TRUE);

  /* BeginMode */
  JS_GL_CONSTANT(POINTS);
  JS_GL_CONSTANT(LINES);
  JS_GL_CONSTANT(LINE_LOOP);
  JS_GL_CONSTANT(LINE_STRIP);
  JS_GL_CONSTANT(TRIANGLES);
  JS_GL_CONSTANT(TRIANGLE_STRIP);
  JS_GL_CONSTANT(TRIANGLE_FAN);
  JS_GL_CONSTANT(QUADS);

  /* AlphaFunction (not supported in ES20) */
  /*      GL_NEVER */
  /*      GL_LESS */
  /*      GL_EQUAL */
  /*      GL_LEQUAL */
  /*      GL_GREATER */
  /*      GL_NOTEQUAL */
  /*      GL_GEQUAL */
  /*      GL_ALWAYS */

  /* BlendingFactorDest */
  JS_GL_CONSTANT(ZERO);
  JS_GL_CONSTANT(ONE);
  JS_GL_CONSTANT(SRC_COLOR);
  JS_GL_CONSTANT(ONE_MINUS_SRC_COLOR);
  JS_GL_CONSTANT(SRC_ALPHA);
  JS_GL_CONSTANT(ONE_MINUS_SRC_ALPHA);
  JS_GL_CONSTANT(DST_ALPHA);
  JS_GL_CONSTANT(ONE_MINUS_DST_ALPHA);

  /* BlendingFactorSrc */
  /*      GL_ZERO */
  /*      GL_ONE */
  JS_GL_CONSTANT(DST_COLOR);
  JS_GL_CONSTANT(ONE_MINUS_DST_COLOR);
  JS_GL_CONSTANT(SRC_ALPHA_SATURATE);
  /*      GL_SRC_ALPHA */
  /*      GL_ONE_MINUS_SRC_ALPHA */
  /*      GL_DST_ALPHA */
  /*      GL_ONE_MINUS_DST_ALPHA */

  /* BlendEquationSeparate */
  JS_GL_CONSTANT(FUNC_ADD);
  JS_GL_CONSTANT(BLEND_EQUATION);
  JS_GL_CONSTANT(BLEND_EQUATION_RGB);    /* same as BLEND_EQUATION */
  JS_GL_CONSTANT(BLEND_EQUATION_ALPHA);

  /* BlendSubtract */
  JS_GL_CONSTANT(FUNC_SUBTRACT);
  JS_GL_CONSTANT(FUNC_REVERSE_SUBTRACT);

  /* Separate Blend Functions */
  JS_GL_CONSTANT(BLEND_DST_RGB);
  JS_GL_CONSTANT(BLEND_SRC_RGB);
  JS_GL_CONSTANT(BLEND_DST_ALPHA);
  JS_GL_CONSTANT(BLEND_SRC_ALPHA);
  JS_GL_CONSTANT(CONSTANT_COLOR);
  JS_GL_CONSTANT(ONE_MINUS_CONSTANT_COLOR);
  JS_GL_CONSTANT(CONSTANT_ALPHA);
  JS_GL_CONSTANT(ONE_MINUS_CONSTANT_ALPHA);
  JS_GL_CONSTANT(BLEND_COLOR);

  /* Buffer Objects */
  JS_GL_CONSTANT(ARRAY_BUFFER);
  JS_GL_CONSTANT(ELEMENT_ARRAY_BUFFER);
  JS_GL_CONSTANT(ARRAY_BUFFER_BINDING);
  JS_GL_CONSTANT(ELEMENT_ARRAY_BUFFER_BINDING);

  JS_GL_CONSTANT(STREAM_DRAW);
  JS_GL_CONSTANT(STATIC_DRAW);
  JS_GL_CONSTANT(DYNAMIC_DRAW);

  JS_GL_CONSTANT(BUFFER_SIZE);
  JS_GL_CONSTANT(BUFFER_USAGE);

  JS_GL_CONSTANT(CURRENT_VERTEX_ATTRIB);

  /* CullFaceMode */
  JS_GL_CONSTANT(FRONT);
  JS_GL_CONSTANT(BACK);
  JS_GL_CONSTANT(FRONT_AND_BACK);

  /* DepthFunction */
  /*      GL_NEVER */
  /*      GL_LESS */
  /*      GL_EQUAL */
  /*      GL_LEQUAL */
  /*      GL_GREATER */
  /*      GL_NOTEQUAL */
  /*      GL_GEQUAL */
  /*      GL_ALWAYS */

  /* EnableCap */
  JS_GL_CONSTANT(ALPHA_TEST);
  JS_GL_CONSTANT(AUTO_NORMAL);
  JS_GL_CONSTANT(BLEND);
  JS_GL_CONSTANT(CLIP_PLANE0);
  JS_GL_CONSTANT(CLIP_PLANE1);
  JS_GL_CONSTANT(CLIP_PLANE2);
  JS_GL_CONSTANT(CLIP_PLANE3);
  JS_GL_CONSTANT(CLIP_PLANE4);
  JS_GL_CONSTANT(CLIP_PLANE5);
  JS_GL_CONSTANT(COLOR_LOGIC_OP);
  JS_GL_CONSTANT(COLOR_MATERIAL);
  JS_GL_CONSTANT(COLOR_SUM);
  JS_GL_CONSTANT(COLOR_TABLE);
  JS_GL_CONSTANT(CONVOLUTION_1D);
  JS_GL_CONSTANT(CONVOLUTION_2D);
  JS_GL_CONSTANT(CULL_FACE);
  JS_GL_CONSTANT(DEPTH_TEST);
  JS_GL_CONSTANT(DITHER);
  JS_GL_CONSTANT(FOG);
  JS_GL_CONSTANT(HISTOGRAM);
  JS_GL_CONSTANT(INDEX_LOGIC_OP);
  JS_GL_CONSTANT(LIGHT0);
  JS_GL_CONSTANT(LIGHT1);
  JS_GL_CONSTANT(LIGHT2);
  JS_GL_CONSTANT(LIGHT3);
  JS_GL_CONSTANT(LIGHT4);
  JS_GL_CONSTANT(LIGHT5);
  JS_GL_CONSTANT(LIGHT6);
  JS_GL_CONSTANT(LIGHT7);
  JS_GL_CONSTANT(LIGHTING);
  JS_GL_CONSTANT(LINE_SMOOTH);
  JS_GL_CONSTANT(LINE_STIPPLE);
  JS_GL_CONSTANT(MAP1_COLOR_4);
  JS_GL_CONSTANT(MAP1_INDEX);
  JS_GL_CONSTANT(MAP1_NORMAL);
  JS_GL_CONSTANT(MAP1_TEXTURE_COORD_1);
  JS_GL_CONSTANT(MAP1_TEXTURE_COORD_2);
  JS_GL_CONSTANT(MAP1_TEXTURE_COORD_3);
  JS_GL_CONSTANT(MAP1_TEXTURE_COORD_4);
  JS_GL_CONSTANT(MAP1_VERTEX_3);
  JS_GL_CONSTANT(MAP1_VERTEX_4);
  JS_GL_CONSTANT(MAP2_COLOR_4);
  JS_GL_CONSTANT(MAP2_INDEX);
  JS_GL_CONSTANT(MAP2_NORMAL);
  JS_GL_CONSTANT(MAP2_TEXTURE_COORD_1);
  JS_GL_CONSTANT(MAP2_TEXTURE_COORD_2);
  JS_GL_CONSTANT(MAP2_TEXTURE_COORD_3);
  JS_GL_CONSTANT(MAP2_TEXTURE_COORD_4);
  JS_GL_CONSTANT(MAP2_VERTEX_3);
  JS_GL_CONSTANT(MAP2_VERTEX_4);
  JS_GL_CONSTANT(MINMAX);
  JS_GL_CONSTANT(MULTISAMPLE);
  JS_GL_CONSTANT(NORMALIZE);
  JS_GL_CONSTANT(POINT_SMOOTH);
  JS_GL_CONSTANT(POINT_SPRITE);
  JS_GL_CONSTANT(POLYGON_OFFSET_FILL);
  JS_GL_CONSTANT(POLYGON_OFFSET_LINE);
  JS_GL_CONSTANT(POLYGON_OFFSET_POINT);
  JS_GL_CONSTANT(POLYGON_SMOOTH);
  JS_GL_CONSTANT(POLYGON_STIPPLE);
  JS_GL_CONSTANT(POST_COLOR_MATRIX_COLOR_TABLE);
  JS_GL_CONSTANT(POST_CONVOLUTION_COLOR_TABLE);
  JS_GL_CONSTANT(RESCALE_NORMAL);
  JS_GL_CONSTANT(SAMPLE_ALPHA_TO_COVERAGE);
  JS_GL_CONSTANT(SAMPLE_ALPHA_TO_ONE);
  JS_GL_CONSTANT(SAMPLE_COVERAGE);
  JS_GL_CONSTANT(SEPARABLE_2D);
  JS_GL_CONSTANT(SCISSOR_TEST);
  JS_GL_CONSTANT(STENCIL_TEST);
  JS_GL_CONSTANT(TEXTURE_1D);
  JS_GL_CONSTANT(TEXTURE_2D);
  JS_GL_CONSTANT(TEXTURE_3D);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP);
  JS_GL_CONSTANT(TEXTURE_GEN_Q);
  JS_GL_CONSTANT(TEXTURE_GEN_R);
  JS_GL_CONSTANT(TEXTURE_GEN_S);
  JS_GL_CONSTANT(TEXTURE_GEN_T);
  JS_GL_CONSTANT(VERTEX_PROGRAM_POINT_SIZE);
  JS_GL_CONSTANT(VERTEX_PROGRAM_TWO_SIDE);

  /* ErrorCode */
  JS_GL_CONSTANT(NO_ERROR);
  JS_GL_CONSTANT(INVALID_ENUM);
  JS_GL_CONSTANT(INVALID_VALUE);
  JS_GL_CONSTANT(INVALID_OPERATION);
  JS_GL_CONSTANT(OUT_OF_MEMORY);

  /* FrontFaceDirection */
  JS_GL_CONSTANT(CW);
  JS_GL_CONSTANT(CCW);

  /* GetPName */
  JS_GL_CONSTANT(LINE_WIDTH);
  JS_GL_CONSTANT(ALIASED_POINT_SIZE_RANGE);
  JS_GL_CONSTANT(ALIASED_LINE_WIDTH_RANGE);
  JS_GL_CONSTANT(CULL_FACE_MODE);
  JS_GL_CONSTANT(FRONT_FACE);
  JS_GL_CONSTANT(DEPTH_RANGE);
  JS_GL_CONSTANT(DEPTH_WRITEMASK);
  JS_GL_CONSTANT(DEPTH_CLEAR_VALUE);
  JS_GL_CONSTANT(DEPTH_FUNC);
  JS_GL_CONSTANT(STENCIL_CLEAR_VALUE);
  JS_GL_CONSTANT(STENCIL_FUNC);
  JS_GL_CONSTANT(STENCIL_FAIL);
  JS_GL_CONSTANT(STENCIL_PASS_DEPTH_FAIL);
  JS_GL_CONSTANT(STENCIL_PASS_DEPTH_PASS);
  JS_GL_CONSTANT(STENCIL_REF);
  JS_GL_CONSTANT(STENCIL_VALUE_MASK);
  JS_GL_CONSTANT(STENCIL_WRITEMASK);
  JS_GL_CONSTANT(STENCIL_BACK_FUNC);
  JS_GL_CONSTANT(STENCIL_BACK_FAIL);
  JS_GL_CONSTANT(STENCIL_BACK_PASS_DEPTH_FAIL);
  JS_GL_CONSTANT(STENCIL_BACK_PASS_DEPTH_PASS);
  JS_GL_CONSTANT(STENCIL_BACK_REF);
  JS_GL_CONSTANT(STENCIL_BACK_VALUE_MASK);
  JS_GL_CONSTANT(STENCIL_BACK_WRITEMASK);
  JS_GL_CONSTANT(VIEWPORT);
  JS_GL_CONSTANT(SCISSOR_BOX);
  /*      GL_SCISSOR_TEST */
  JS_GL_CONSTANT(COLOR_CLEAR_VALUE);
  JS_GL_CONSTANT(COLOR_WRITEMASK);
  JS_GL_CONSTANT(UNPACK_ALIGNMENT);
  JS_GL_CONSTANT(PACK_ALIGNMENT);
  JS_GL_CONSTANT(MAX_TEXTURE_SIZE);
  JS_GL_CONSTANT(MAX_VIEWPORT_DIMS);
  JS_GL_CONSTANT(SUBPIXEL_BITS);
  JS_GL_CONSTANT(RED_BITS);
  JS_GL_CONSTANT(GREEN_BITS);
  JS_GL_CONSTANT(BLUE_BITS);
  JS_GL_CONSTANT(ALPHA_BITS);
  JS_GL_CONSTANT(DEPTH_BITS);
  JS_GL_CONSTANT(STENCIL_BITS);
  JS_GL_CONSTANT(POLYGON_OFFSET_UNITS);
  /*      GL_POLYGON_OFFSET_FILL */
  JS_GL_CONSTANT(POLYGON_OFFSET_FACTOR);
  JS_GL_CONSTANT(TEXTURE_BINDING_2D);
  JS_GL_CONSTANT(SAMPLE_BUFFERS);
  JS_GL_CONSTANT(SAMPLES);
  JS_GL_CONSTANT(SAMPLE_COVERAGE_VALUE);
  JS_GL_CONSTANT(SAMPLE_COVERAGE_INVERT);

  /* GetTextureParameter */
  /*      GL_TEXTURE_MAG_FILTER */
  /*      GL_TEXTURE_MIN_FILTER */
  /*      GL_TEXTURE_WRAP_S */
  /*      GL_TEXTURE_WRAP_T */

  JS_GL_CONSTANT(NUM_COMPRESSED_TEXTURE_FORMATS);
  JS_GL_CONSTANT(COMPRESSED_TEXTURE_FORMATS);

  /* HintMode */
  JS_GL_CONSTANT(DONT_CARE);
  JS_GL_CONSTANT(FASTEST);
  JS_GL_CONSTANT(NICEST);

  /* HintTarget */
  JS_GL_CONSTANT(FOG_HINT);
  JS_GL_CONSTANT(FRAGMENT_SHADER_DERIVATIVE_HINT);
  JS_GL_CONSTANT(GENERATE_MIPMAP_HINT);
  JS_GL_CONSTANT(LINE_SMOOTH_HINT);
  JS_GL_CONSTANT(PERSPECTIVE_CORRECTION_HINT);
  JS_GL_CONSTANT(POINT_SMOOTH_HINT);
  JS_GL_CONSTANT(POLYGON_SMOOTH_HINT);
  JS_GL_CONSTANT(TEXTURE_COMPRESSION_HINT);


  /* DataType */
  JS_GL_CONSTANT(BYTE);
  JS_GL_CONSTANT(UNSIGNED_BYTE);
  JS_GL_CONSTANT(SHORT);
  JS_GL_CONSTANT(UNSIGNED_SHORT);
  JS_GL_CONSTANT(INT);
  JS_GL_CONSTANT(UNSIGNED_INT);
  JS_GL_CONSTANT(FLOAT);
#ifndef __APPLE__
  JS_GL_CONSTANT(FIXED);
#endif

  /* PixelFormat */
  JS_GL_CONSTANT(DEPTH_COMPONENT);
  JS_GL_CONSTANT(ALPHA);
  JS_GL_CONSTANT(RGB);
  JS_GL_CONSTANT(RGBA);
  JS_GL_CONSTANT(LUMINANCE);
  JS_GL_CONSTANT(LUMINANCE_ALPHA);

  /* PixelType */
  /*      GL_UNSIGNED_BYTE */
  JS_GL_CONSTANT(UNSIGNED_SHORT_4_4_4_4);
  JS_GL_CONSTANT(UNSIGNED_SHORT_5_5_5_1);
  JS_GL_CONSTANT(UNSIGNED_SHORT_5_6_5);

  /* Shaders */
  JS_GL_CONSTANT(FRAGMENT_SHADER);
  JS_GL_CONSTANT(VERTEX_SHADER);
  JS_GL_CONSTANT(MAX_VERTEX_ATTRIBS);
#ifndef __APPLE__
  JS_GL_CONSTANT(MAX_VERTEX_UNIFORM_VECTORS);
  JS_GL_CONSTANT(MAX_VARYING_VECTORS);
#endif
  JS_GL_CONSTANT(MAX_COMBINED_TEXTURE_IMAGE_UNITS);
  JS_GL_CONSTANT(MAX_VERTEX_TEXTURE_IMAGE_UNITS);
  JS_GL_CONSTANT(MAX_TEXTURE_IMAGE_UNITS);
#ifndef __APPLE__
  JS_GL_CONSTANT(MAX_FRAGMENT_UNIFORM_VECTORS);
#endif
  JS_GL_CONSTANT(SHADER_TYPE);
  JS_GL_CONSTANT(DELETE_STATUS);
  JS_GL_CONSTANT(LINK_STATUS);
  JS_GL_CONSTANT(VALIDATE_STATUS);
  JS_GL_CONSTANT(ATTACHED_SHADERS);
  JS_GL_CONSTANT(ACTIVE_UNIFORMS);
  JS_GL_CONSTANT(ACTIVE_UNIFORM_MAX_LENGTH);
  JS_GL_CONSTANT(ACTIVE_ATTRIBUTES);
  JS_GL_CONSTANT(ACTIVE_ATTRIBUTE_MAX_LENGTH);
  JS_GL_CONSTANT(SHADING_LANGUAGE_VERSION);
  JS_GL_CONSTANT(CURRENT_PROGRAM);

  /* StencilFunction */
  JS_GL_CONSTANT(NEVER);
  JS_GL_CONSTANT(LESS);
  JS_GL_CONSTANT(EQUAL);
  JS_GL_CONSTANT(LEQUAL);
  JS_GL_CONSTANT(GREATER);
  JS_GL_CONSTANT(NOTEQUAL);
  JS_GL_CONSTANT(GEQUAL);
  JS_GL_CONSTANT(ALWAYS);

  /* StencilOp */
  /*      GL_ZERO */
  JS_GL_CONSTANT(KEEP);
  JS_GL_CONSTANT(REPLACE);
  JS_GL_CONSTANT(INCR);
  JS_GL_CONSTANT(DECR);
  JS_GL_CONSTANT(INVERT);
  JS_GL_CONSTANT(INCR_WRAP);
  JS_GL_CONSTANT(DECR_WRAP);

  /* StringName */
  JS_GL_CONSTANT(VENDOR);
  JS_GL_CONSTANT(RENDERER);
  JS_GL_CONSTANT(VERSION);
  JS_GL_CONSTANT(EXTENSIONS);

  /* TextureMagFilter */
  JS_GL_CONSTANT(NEAREST);
  JS_GL_CONSTANT(LINEAR);

  /* TextureMinFilter */
  /*      GL_NEAREST */
  /*      GL_LINEAR */
  JS_GL_CONSTANT(NEAREST_MIPMAP_NEAREST);
  JS_GL_CONSTANT(LINEAR_MIPMAP_NEAREST);
  JS_GL_CONSTANT(NEAREST_MIPMAP_LINEAR);
  JS_GL_CONSTANT(LINEAR_MIPMAP_LINEAR);

  /* TextureParameterName */
  JS_GL_CONSTANT(TEXTURE_MAG_FILTER);
  JS_GL_CONSTANT(TEXTURE_MIN_FILTER);
  JS_GL_CONSTANT(TEXTURE_WRAP_S);
  JS_GL_CONSTANT(TEXTURE_WRAP_T);

  /* TextureTarget */
  /*      GL_TEXTURE_2D */
  JS_GL_CONSTANT(TEXTURE);

  JS_GL_CONSTANT(TEXTURE_CUBE_MAP);
  JS_GL_CONSTANT(TEXTURE_BINDING_CUBE_MAP);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP_POSITIVE_X);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP_NEGATIVE_X);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP_POSITIVE_Y);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP_NEGATIVE_Y);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP_POSITIVE_Z);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP_NEGATIVE_Z);
  JS_GL_CONSTANT(MAX_CUBE_MAP_TEXTURE_SIZE);

  /* TextureUnit */
  JS_GL_CONSTANT(TEXTURE0);
  JS_GL_CONSTANT(TEXTURE1);
  JS_GL_CONSTANT(TEXTURE2);
  JS_GL_CONSTANT(TEXTURE3);
  JS_GL_CONSTANT(TEXTURE4);
  JS_GL_CONSTANT(TEXTURE5);
  JS_GL_CONSTANT(TEXTURE6);
  JS_GL_CONSTANT(TEXTURE7);
  JS_GL_CONSTANT(TEXTURE8);
  JS_GL_CONSTANT(TEXTURE9);
  JS_GL_CONSTANT(TEXTURE10);
  JS_GL_CONSTANT(TEXTURE11);
  JS_GL_CONSTANT(TEXTURE12);
  JS_GL_CONSTANT(TEXTURE13);
  JS_GL_CONSTANT(TEXTURE14);
  JS_GL_CONSTANT(TEXTURE15);
  JS_GL_CONSTANT(TEXTURE16);
  JS_GL_CONSTANT(TEXTURE17);
  JS_GL_CONSTANT(TEXTURE18);
  JS_GL_CONSTANT(TEXTURE19);
  JS_GL_CONSTANT(TEXTURE20);
  JS_GL_CONSTANT(TEXTURE21);
  JS_GL_CONSTANT(TEXTURE22);
  JS_GL_CONSTANT(TEXTURE23);
  JS_GL_CONSTANT(TEXTURE24);
  JS_GL_CONSTANT(TEXTURE25);
  JS_GL_CONSTANT(TEXTURE26);
  JS_GL_CONSTANT(TEXTURE27);
  JS_GL_CONSTANT(TEXTURE28);
  JS_GL_CONSTANT(TEXTURE29);
  JS_GL_CONSTANT(TEXTURE30);
  JS_GL_CONSTANT(TEXTURE31);
  JS_GL_CONSTANT(ACTIVE_TEXTURE);

  /* TextureWrapMode */
  JS_GL_CONSTANT(REPEAT);
  JS_GL_CONSTANT(CLAMP_TO_EDGE);
  JS_GL_CONSTANT(MIRRORED_REPEAT);

  /* Uniform Types */
  JS_GL_CONSTANT(FLOAT_VEC2);
  JS_GL_CONSTANT(FLOAT_VEC3);
  JS_GL_CONSTANT(FLOAT_VEC4);
  JS_GL_CONSTANT(INT_VEC2);
  JS_GL_CONSTANT(INT_VEC3);
  JS_GL_CONSTANT(INT_VEC4);
  JS_GL_CONSTANT(BOOL);
  JS_GL_CONSTANT(BOOL_VEC2);
  JS_GL_CONSTANT(BOOL_VEC3);
  JS_GL_CONSTANT(BOOL_VEC4);
  JS_GL_CONSTANT(FLOAT_MAT2);
  JS_GL_CONSTANT(FLOAT_MAT3);
  JS_GL_CONSTANT(FLOAT_MAT4);
  JS_GL_CONSTANT(SAMPLER_2D);
  JS_GL_CONSTANT(SAMPLER_CUBE);

  /* Vertex Arrays */
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_ENABLED);
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_SIZE);
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_STRIDE);
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_TYPE);
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_NORMALIZED);
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_POINTER);
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);

  /* Read Format */
#ifndef __APPLE__
  JS_GL_CONSTANT(IMPLEMENTATION_COLOR_READ_TYPE);
  JS_GL_CONSTANT(IMPLEMENTATION_COLOR_READ_FORMAT);
#endif

  /* Shader Source */
  JS_GL_CONSTANT(COMPILE_STATUS);
  JS_GL_CONSTANT(INFO_LOG_LENGTH);
  JS_GL_CONSTANT(SHADER_SOURCE_LENGTH);
#ifndef __APPLE__
  JS_GL_CONSTANT(SHADER_COMPILER);
#endif

  /* Shader Binary */
#ifndef __APPLE__
  JS_GL_CONSTANT(SHADER_BINARY_FORMATS);
  JS_GL_CONSTANT(NUM_SHADER_BINARY_FORMATS);
#endif

  /* Shader Precision-Specified Types */
#ifndef __APPLE__
  JS_GL_CONSTANT(LOW_FLOAT);
  JS_GL_CONSTANT(MEDIUM_FLOAT);
  JS_GL_CONSTANT(HIGH_FLOAT);
  JS_GL_CONSTANT(LOW_INT);
  JS_GL_CONSTANT(MEDIUM_INT);
  JS_GL_CONSTANT(HIGH_INT);
#endif

  /* Framebuffer Object. */
  JS_GL_CONSTANT(FRAMEBUFFER);
  JS_GL_CONSTANT(RENDERBUFFER);

  JS_GL_CONSTANT(RGBA4);
  JS_GL_CONSTANT(RGB5_A1);
#ifndef __APPLE__
  //JS_GL_CONSTANT(RGB565);
#endif
  JS_GL_CONSTANT(DEPTH_COMPONENT16);
  JS_GL_CONSTANT(STENCIL_INDEX);
  JS_GL_CONSTANT(STENCIL_INDEX8);

  JS_GL_CONSTANT(RENDERBUFFER_WIDTH);
  JS_GL_CONSTANT(RENDERBUFFER_HEIGHT);
  JS_GL_CONSTANT(RENDERBUFFER_INTERNAL_FORMAT);
  JS_GL_CONSTANT(RENDERBUFFER_RED_SIZE);
  JS_GL_CONSTANT(RENDERBUFFER_GREEN_SIZE);
  JS_GL_CONSTANT(RENDERBUFFER_BLUE_SIZE);
  JS_GL_CONSTANT(RENDERBUFFER_ALPHA_SIZE);
  JS_GL_CONSTANT(RENDERBUFFER_DEPTH_SIZE);
  JS_GL_CONSTANT(RENDERBUFFER_STENCIL_SIZE);

  JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
  JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
  JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
  JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE);

  JS_GL_CONSTANT(COLOR_ATTACHMENT0);
  JS_GL_CONSTANT(DEPTH_ATTACHMENT);
  JS_GL_CONSTANT(STENCIL_ATTACHMENT);

  JS_GL_CONSTANT(NONE);

  JS_GL_CONSTANT(FRAMEBUFFER_COMPLETE);
  JS_GL_CONSTANT(FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
  JS_GL_CONSTANT(FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
#ifndef __APPLE__
  //JS_GL_CONSTANT(FRAMEBUFFER_INCOMPLETE_DIMENSIONS);
#endif
  JS_GL_CONSTANT(FRAMEBUFFER_UNSUPPORTED);

  JS_GL_CONSTANT(FRAMEBUFFER_BINDING);
  JS_GL_CONSTANT(RENDERBUFFER_BINDING);
  JS_GL_CONSTANT(MAX_RENDERBUFFER_SIZE);

  JS_GL_CONSTANT(INVALID_FRAMEBUFFER_OPERATION);

  // matrixmode
  JS_GL_CONSTANT(MODELVIEW);
  JS_GL_CONSTANT(PROJECTION);
  JS_GL_CONSTANT(TEXTURE);
  JS_GL_CONSTANT(COLOR);  

  JS_GL_CONSTANT(COMPILE);

  JS_GL_CONSTANT(FOG);  
  JS_GL_CONSTANT(FOG_MODE);  
  JS_GL_CONSTANT(FOG_DENSITY);  
  JS_GL_CONSTANT(FOG_START);  
  JS_GL_CONSTANT(FOG_END);  
  JS_GL_CONSTANT(FOG_INDEX);  
  JS_GL_CONSTANT(FOG_COLOR);  
  JS_GL_CONSTANT(FOG_COORD_SRC);  


  /* WebGL-specific enums */
  target->Set(JS_STR( "UNPACK_FLIP_Y_WEBGL" ), JS_INT(0x9240));
  target->Set(JS_STR( "UNPACK_PREMULTIPLY_ALPHA_WEBGL" ), JS_INT(0x9241));
  target->Set(JS_STR( "CONTEXT_LOST_WEBGL" ), JS_INT(0x9242));
  target->Set(JS_STR( "UNPACK_COLORSPACE_CONVERSION_WEBGL" ), JS_INT(0x9243));
  target->Set(JS_STR( "BROWSER_DEFAULT_WEBGL" ), JS_INT(0x9244));

  //////////////////////////////
  // NOT in WebGL spec
  //////////////////////////////

  // PBO
  target->Set(JS_STR( "PIXEL_PACK_BUFFER" ), JS_INT(0x88EB));
  target->Set(JS_STR( "PIXEL_UNPACK_BUFFER" ), JS_INT(0x88EC));
  target->Set(JS_STR( "PIXEL_PACK_BUFFER_BINDING" ), JS_INT(0x88ED));
  target->Set(JS_STR( "PIXEL_UNPACK_BUFFER_BINDING" ), JS_INT(0x88EF));
}

NODE_MODULE(gl, init)
} // extern "C"
