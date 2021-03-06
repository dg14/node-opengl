/*
 * gl.h
 *
 *  Created on: Dec 13, 2011
 *      Author: ngk437
 */

#ifndef WEBGL_H_
#define WEBGL_H_

#include "common.h"

using namespace node;
using namespace v8;

namespace gl {
void AtExit();

JS_METHOD(Init);

JS_METHOD(Uniform1f);
JS_METHOD(Uniform2f);
JS_METHOD(Uniform3f);
JS_METHOD(Uniform4f);
JS_METHOD(Uniform1i);
JS_METHOD(Uniform2i);
JS_METHOD(Uniform3i);
JS_METHOD(Uniform4i);
JS_METHOD(Uniform1fv);
JS_METHOD(Uniform2fv);
JS_METHOD(Uniform3fv);
JS_METHOD(Uniform4fv);
JS_METHOD(Uniform1iv);
JS_METHOD(Uniform2iv);
JS_METHOD(Uniform3iv);
JS_METHOD(Uniform4iv);
JS_METHOD(PixelStorei);
JS_METHOD(BindAttribLocation);
JS_METHOD(GetError);
JS_METHOD(DrawArrays);
JS_METHOD(UniformMatrix2fv);
JS_METHOD(UniformMatrix3fv);
JS_METHOD(UniformMatrix4fv);
JS_METHOD(GenerateMipmap);
JS_METHOD(GetAttribLocation);
JS_METHOD(DepthFunc);
JS_METHOD(Viewport);
JS_METHOD(CreateShader);
JS_METHOD(ShaderSource);
JS_METHOD(CompileShader);
JS_METHOD(GetShaderParameter);
JS_METHOD(GetShaderInfoLog);
JS_METHOD(CreateProgram);
JS_METHOD(AttachShader);
JS_METHOD(LinkProgram);
JS_METHOD(GetProgramParameter);
JS_METHOD(GetUniformLocation);
JS_METHOD(ClearColor);
JS_METHOD(ClearDepth);
JS_METHOD(Disable);
JS_METHOD(Enable);
JS_METHOD(CreateTexture);
JS_METHOD(BindTexture);
JS_METHOD(TexImage2D);
JS_METHOD(TexParameteri);
JS_METHOD(TexParameterf);
JS_METHOD(Clear);
JS_METHOD(UseProgram);
JS_METHOD(CreateBuffer);
JS_METHOD(BindBuffer);
JS_METHOD(CreateFramebuffer);
JS_METHOD(BindFramebuffer);
JS_METHOD(FramebufferTexture2D);
JS_METHOD(BufferData);
JS_METHOD(BufferSubData);
JS_METHOD(BlendEquation);
JS_METHOD(BlendFunc);
JS_METHOD(EnableVertexAttribArray);
JS_METHOD(VertexAttribPointer);
JS_METHOD(ActiveTexture);
JS_METHOD(DrawElements);
JS_METHOD(Flush);
JS_METHOD(Finish);

JS_METHOD(VertexAttrib1f);
JS_METHOD(VertexAttrib2f);
JS_METHOD(VertexAttrib3f);
JS_METHOD(VertexAttrib4f);
JS_METHOD(VertexAttrib1fv);
JS_METHOD(VertexAttrib2fv);
JS_METHOD(VertexAttrib3fv);
JS_METHOD(VertexAttrib4fv);

JS_METHOD(BlendColor);
JS_METHOD(BlendEquationSeparate);
JS_METHOD(BlendFuncSeparate);
JS_METHOD(ClearStencil);
JS_METHOD(ColorMask);
JS_METHOD(CopyTexImage2D);
JS_METHOD(CopyTexSubImage2D);
JS_METHOD(CullFace);
JS_METHOD(DepthMask);
JS_METHOD(DepthRange);
JS_METHOD(DisableVertexAttribArray);
JS_METHOD(Hint);
JS_METHOD(IsEnabled);
JS_METHOD(LineWidth);
JS_METHOD(PolygonOffset);

JS_METHOD(Scissor);
JS_METHOD(StencilFunc);
JS_METHOD(StencilFuncSeparate);
JS_METHOD(StencilMask);
JS_METHOD(StencilMaskSeparate);
JS_METHOD(StencilOp);
JS_METHOD(StencilOpSeparate);
JS_METHOD(BindRenderbuffer);
JS_METHOD(CreateRenderbuffer);

JS_METHOD(DeleteBuffer);
JS_METHOD(DeleteFramebuffer);
JS_METHOD(DeleteProgram);
JS_METHOD(DeleteRenderbuffer);
JS_METHOD(DeleteShader);
JS_METHOD(DeleteTexture);
JS_METHOD(DetachShader);
JS_METHOD(FramebufferRenderbuffer);
JS_METHOD(GetVertexAttribOffset);

JS_METHOD(IsBuffer);
JS_METHOD(IsFramebuffer);
JS_METHOD(IsProgram);
JS_METHOD(IsRenderbuffer);
JS_METHOD(IsShader);
JS_METHOD(IsTexture);

JS_METHOD(RenderbufferStorage);
JS_METHOD(GetShaderSource);
JS_METHOD(ValidateProgram);

JS_METHOD(TexSubImage2D);
JS_METHOD(ReadPixels);
JS_METHOD(GetTexParameter);
JS_METHOD(GetActiveAttrib);
JS_METHOD(GetActiveUniform);
JS_METHOD(GetAttachedShaders);
JS_METHOD(GetParameter);
JS_METHOD(GetBufferParameter);
JS_METHOD(GetFramebufferAttachmentParameter);
JS_METHOD(GetProgramInfoLog);
JS_METHOD(GetRenderbufferParameter);
JS_METHOD(GetVertexAttrib);
JS_METHOD(GetSupportedExtensions);
JS_METHOD(GetExtension);
JS_METHOD(CheckFramebufferStatus);

JS_METHOD(FrontFace);

JS_METHOD(MatrixMode);
JS_METHOD(LoadIdentity);
JS_METHOD(Begin);
JS_METHOD(End);
JS_METHOD(Color3b);
JS_METHOD(Color3s);
JS_METHOD(Color3i);
JS_METHOD(Color3f);
JS_METHOD(Color3d);
JS_METHOD(Color3ub);
JS_METHOD(Color3us);
JS_METHOD(Color3ui);
JS_METHOD(Color4b);
JS_METHOD(Color4s);
JS_METHOD(Color4i);
JS_METHOD(Color4f);
JS_METHOD(Color4d);
JS_METHOD(Color4ub);
JS_METHOD(Color4us);
JS_METHOD(Color4ui);

JS_METHOD(Color3bv);
JS_METHOD(Color3sv);
JS_METHOD(Color3iv);
JS_METHOD(Color3fv);
JS_METHOD(Color3dv);
JS_METHOD(Color3ubv);
JS_METHOD(Color3usv);
JS_METHOD(Color3uiv);
JS_METHOD(Color4bv);
JS_METHOD(Color4sv);
JS_METHOD(Color4iv);
JS_METHOD(Color4fv);
JS_METHOD(Color4dv);
JS_METHOD(Color4ubv);
JS_METHOD(Color4usv);
JS_METHOD(Color4uiv);

JS_METHOD(Vertex2s);
JS_METHOD(Vertex2i);
JS_METHOD(Vertex2f);
JS_METHOD(Vertex2d);
JS_METHOD(Vertex3s);
JS_METHOD(Vertex3i);
JS_METHOD(Vertex3f);
JS_METHOD(Vertex3d);
JS_METHOD(Vertex4s);
JS_METHOD(Vertex4i);
JS_METHOD(Vertex4f);
JS_METHOD(Vertex4d);

JS_METHOD(Rotatef);
JS_METHOD(Ortho);
JS_METHOD(Translatef);
JS_METHOD(Translated);
JS_METHOD(Scalef);
JS_METHOD(Scaled);
JS_METHOD(ShadeModel);
JS_METHOD(TexCoord2f);
JS_METHOD(Lightf);
JS_METHOD(Lighti);
JS_METHOD(Lightfv);
JS_METHOD(Lightiv);

JS_METHOD(Normal3b);
JS_METHOD(Normal3d);
JS_METHOD(Normal3f);
JS_METHOD(Normal3i);
JS_METHOD(Normal3s);

JS_METHOD(Normal3bv);
JS_METHOD(Normal3dv);
JS_METHOD(Normal3fv);
JS_METHOD(Normal3iv);
JS_METHOD(Normal3sv);
JS_METHOD(PolygonMode);

JS_METHOD(CreateList);
JS_METHOD(NewList);
JS_METHOD(EndList);
JS_METHOD(GenLists);
JS_METHOD(CallList);
JS_METHOD(CallLists);
JS_METHOD(ListBase);

JS_METHOD(Fogi);
JS_METHOD(Fogf);
JS_METHOD(Fogfv);
JS_METHOD(Fogiv);

JS_METHOD(PointSize);

}

#endif /* WEBGL_H_ */
