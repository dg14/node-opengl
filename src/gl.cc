#include <cstring>
#include <vector>
#include <iostream>

#include "gl.h"
#include "image.h"
#include <node.h>
#include <node_buffer.h>
#include <GL/glew.h>
#include <GL/glu.h>

#ifdef _WIN32
  #define  strcasestr(s, t) strstr(strupr(s), t)
#endif

namespace gl {

using namespace node;
using namespace v8;
using namespace std;

// forward declarations
enum GLObjectType {
  GLOBJECT_TYPE_BUFFER,
  GLOBJECT_TYPE_FRAMEBUFFER,
  GLOBJECT_TYPE_PROGRAM,
  GLOBJECT_TYPE_RENDERBUFFER,
  GLOBJECT_TYPE_SHADER,
  GLOBJECT_TYPE_TEXTURE,
};

void registerGLObj(GLObjectType type, GLuint obj);
void unregisterGLObj(GLuint obj);

v8::Handle<v8::Value> ThrowError(const char* msg) {
  return v8::ThrowException(v8::Exception::Error(v8::String::New(msg)));
}

// A 32-bit and 64-bit compatible way of converting a pointer to a GLuint.
static GLuint ToGLuint(const void* ptr) {
  return static_cast<GLuint>(reinterpret_cast<size_t>(ptr));
}

static int SizeOfArrayElementForType(v8::ExternalArrayType type) {
  switch (type) {
  case v8::kExternalByteArray:
  case v8::kExternalUnsignedByteArray:
    return 1;
  case v8::kExternalShortArray:
  case v8::kExternalUnsignedShortArray:
    return 2;
  case v8::kExternalIntArray:
  case v8::kExternalUnsignedIntArray:
  case v8::kExternalFloatArray:
    return 4;
  default:
    return 0;
  }
}

inline void *getImageData(Local<Value> arg) {
  void *pixels = NULL;
  if (!arg->IsNull()) {
    Local<Object> obj = Local<Object>::Cast(arg);
    if (!obj->IsObject())
      ThrowException(JS_STR("Bad texture argument"));

    pixels = obj->GetIndexedPropertiesExternalArrayData();
  }
  return pixels;
}

/*
template<typename Type>
inline Type* getArrayData(Local<Value> arg, int* num = NULL) {
  Type *data=NULL;
  if(num) *num=0;
  if(!arg->IsNull()) {
    if(arg->IsArray()) {
      Local<Array> arr = Array::Cast(*arg);
      if(num) *num=arr->Length();
      data = reinterpret_cast<Type*>(arr->GetIndexedPropertiesExternalArrayData());
    }
    else if(arg->IsObject()) {
      if(num) *num = arg->ToObject()->GetIndexedPropertiesExternalArrayDataLength();
      data = reinterpret_cast<Type*>(arg->ToObject()->GetIndexedPropertiesExternalArrayData());
    }
    else
      ThrowException(JS_STR("Bad array argument"));
  }

  return data;
}
*/

template<typename Type>
inline Type *arg2v(Local<Array> arg, bool isFloat, unsigned int expectedNum, unsigned int *num=NULL) {
  if(!arg->IsNull() && arg->IsArray()) {
    if (num) *num=arg->Length();
    if (expectedNum!=0 && arg->Length()!=expectedNum) ThrowException(JS_STR("Bad array argument count"));
    Type *var=new Type[arg->Length()];
    for (unsigned int i=0;i<arg->Length();i++) {
      var[i]=isFloat?arg->Get(Integer::New(i))->NumberValue():arg->Get(Integer::New(i))->Int32Value();;
    }
    return var;
  } else {
    ThrowException(JS_STR("Bad array argument"));
  }
  return NULL;
}

JS_METHOD(Init) {
  HandleScope scope;
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    return scope.Close(JS_INT(-1));
  }
  //fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
  return scope.Close(JS_INT(0));
}

JS_METHOD(Uniform1f) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  float x = (float) args[1]->NumberValue();

  glUniform1f(location, x);
  return scope.Close(Undefined());
}

JS_METHOD(Uniform2f) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  float x = (float) args[1]->NumberValue();
  float y = (float) args[2]->NumberValue();

  glUniform2f(location, x, y);
  return scope.Close(Undefined());
}

JS_METHOD(Uniform3f) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  float x = (float) args[1]->NumberValue();
  float y = (float) args[2]->NumberValue();
  float z = (float) args[3]->NumberValue();

  glUniform3f(location, x, y, z);
  return scope.Close(Undefined());
}

JS_METHOD(Uniform4f) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  float x = (float) args[1]->NumberValue();
  float y = (float) args[2]->NumberValue();
  float z = (float) args[3]->NumberValue();
  float w = (float) args[4]->NumberValue();

  glUniform4f(location, x, y, z, w);
  return scope.Close(Undefined());
}

JS_METHOD(Uniform1i) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  int x = args[1]->Int32Value();

  glUniform1i(location, x);
  return scope.Close(Undefined());
}

JS_METHOD(Uniform2i) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  int x = args[1]->Int32Value();
  int y = args[2]->Int32Value();

  glUniform2i(location, x, y);
  return scope.Close(Undefined());
}

JS_METHOD(Uniform3i) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  int x = args[1]->Int32Value();
  int y = args[2]->Int32Value();
  int z = args[3]->Int32Value();

  glUniform3i(location, x, y, z);
  return scope.Close(Undefined());
}

JS_METHOD(Uniform4i) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  int x = args[1]->Int32Value();
  int y = args[2]->Int32Value();
  int z = args[3]->Int32Value();
  int w = args[4]->Int32Value();

  glUniform4i(location, x, y, z, w);
  return scope.Close(Undefined());
}

JS_METHOD(Uniform1fv) {
  HandleScope scope;
  int location = args[0]->Int32Value();
  unsigned int num=0;
  GLfloat *param=arg2v<GLfloat>(Array::Cast(*args[1]),true,0,&num);      
  glUniform1fv(location, num, param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Uniform2fv) {
  HandleScope scope;
  int location = args[0]->Int32Value();
  unsigned int num=0;
  GLfloat *param=arg2v<GLfloat>(Array::Cast(*args[1]),true,0,&num);      
  num /= 2;
  glUniform2fv(location, num, param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Uniform3fv) {
  HandleScope scope;
  int location = args[0]->Int32Value();
  unsigned int num=0;
  GLfloat *param=arg2v<GLfloat>(Array::Cast(*args[1]),true,0,&num);      
  num /= 3;
  glUniform3fv(location, num, param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Uniform4fv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  unsigned int num=0;
  GLfloat *param=arg2v<GLfloat>(Array::Cast(*args[1]),true,0,&num);  
  num /= 4;
  glUniform4fv(location, num, param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Uniform1iv) {
  HandleScope scope;
  int location = args[0]->Int32Value();
  unsigned int num=0;
  GLint *param=arg2v<GLint>(Array::Cast(*args[1]),false,0,&num);      

  glUniform1iv(location, num, param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Uniform2iv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  unsigned int num=0;
  GLint *param=arg2v<GLint>(Array::Cast(*args[1]),false,0,&num);
  num /= 2;

  glUniform2iv(location, num, param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Uniform3iv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  unsigned int num=0;
  GLint *param=arg2v<GLint>(Array::Cast(*args[1]),false,0,&num);      
  num /= 3;
  glUniform3iv(location, num, param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Uniform4iv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  unsigned int num=0;
  GLint *param=arg2v<GLint>(Array::Cast(*args[1]),false,0,&num);      
  num /= 4;
  glUniform4iv(location, num, param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(PixelStorei) {
  HandleScope scope;

  int pname = args[0]->Int32Value();
  int param = args[1]->Int32Value();

  glPixelStorei(pname,param);

  return scope.Close(Undefined());
}

JS_METHOD(BindAttribLocation) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  int index = args[1]->Int32Value();
  String::Utf8Value name(args[2]);

  glBindAttribLocation(program, index, *name);

  return scope.Close(Undefined());
}


JS_METHOD(GetError) {
  HandleScope scope;

  return scope.Close(Number::New(glGetError()));
}


JS_METHOD(DrawArrays) {
  HandleScope scope;

  int mode = args[0]->Int32Value();
  int first = args[1]->Int32Value();
  int count = args[2]->Int32Value();

  glDrawArrays(mode, first, count);

  return scope.Close(Undefined());
}

JS_METHOD(UniformMatrix2fv) {
  HandleScope scope;

  GLint location = args[0]->Int32Value();
  GLboolean transpose = args[1]->BooleanValue();

  GLsizei count=0;
  GLfloat *data=arg2v<GLfloat>(Array::Cast(*args[2]),true,0,(unsigned int *)&count);      

  if (count < 4) {
    delete data;
    return ThrowError("Not enough data for UniformMatrix2fv");    
  }

  glUniformMatrix2fv(location, count / 4, transpose, data);
  delete data;

  return scope.Close(Undefined());
}

JS_METHOD(UniformMatrix3fv) {
  HandleScope scope;

  GLint location = args[0]->Int32Value();
  GLboolean transpose = args[1]->BooleanValue();
  GLsizei count=0;
  GLfloat *data=arg2v<GLfloat>(Array::Cast(*args[2]),true,0,(unsigned int *)&count);      

  if (count < 9) {
    delete data;
    return ThrowError("Not enough data for UniformMatrix3fv");
  }

  glUniformMatrix3fv(location, count / 9, transpose, data);
  delete data;

  return scope.Close(Undefined());
}

JS_METHOD(UniformMatrix4fv) {
  HandleScope scope;

  GLint location = args[0]->Int32Value();
  GLboolean transpose = args[1]->BooleanValue();
  GLsizei count=0;
  GLfloat *data=arg2v<GLfloat>(Array::Cast(*args[2]),true,0,(unsigned int *)&count);      

  if (count < 16) {
    delete data;
    return ThrowError("Not enough data for UniformMatrix4fv");
  }

  glUniformMatrix4fv(location, count / 16, transpose, data);
  delete data;

  return scope.Close(Undefined());
}

JS_METHOD(GenerateMipmap) {
  HandleScope scope;

  GLint target = args[0]->Int32Value();
  glGenerateMipmap(target);

  return scope.Close(Undefined());
}

JS_METHOD(GetAttribLocation) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  String::Utf8Value name(args[1]);

  return scope.Close(Number::New(glGetAttribLocation(program, *name)));
}


JS_METHOD(DepthFunc) {
  HandleScope scope;

  glDepthFunc(args[0]->Int32Value());

  return scope.Close(Undefined());
}


JS_METHOD(Viewport) {
  HandleScope scope;

  int x = args[0]->Int32Value();
  int y = args[1]->Int32Value();
  int width = args[2]->Int32Value();
  int height = args[3]->Int32Value();

  glViewport(x, y, width, height);

  return scope.Close(Undefined());
}

JS_METHOD(CreateShader) {
  HandleScope scope;

  GLuint shader=glCreateShader(args[0]->Int32Value());
  #ifdef LOGGING
  cout<<"createShader "<<shader<<endl;
  #endif
  registerGLObj(GLOBJECT_TYPE_SHADER, shader);
  return scope.Close(Number::New(shader));
}


JS_METHOD(ShaderSource) {
  HandleScope scope;

  int id = args[0]->Int32Value();
  String::Utf8Value code(args[1]);

  const char* codes[1];
  codes[0] = *code;
  GLint length=code.length();

  glShaderSource  (id, 1, codes, &length);

  return scope.Close(Undefined());
}


JS_METHOD(CompileShader) {
  HandleScope scope;

  glCompileShader(args[0]->Int32Value());

  return scope.Close(Undefined());
}

JS_METHOD(FrontFace) {
  HandleScope scope;

  glFrontFace(args[0]->Int32Value());

  return scope.Close(Undefined());
}


JS_METHOD(GetShaderParameter) {
  HandleScope scope;

  int shader = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  int value = 0;
  switch (pname) {
  case GL_DELETE_STATUS:
  case GL_COMPILE_STATUS:
    glGetShaderiv(shader, pname, &value);
    return scope.Close(JS_BOOL(static_cast<bool>(value!=0)));
  case GL_SHADER_TYPE:
    glGetShaderiv(shader, pname, &value);
    return scope.Close(JS_INT(static_cast<unsigned long>(value)));
  case GL_INFO_LOG_LENGTH:
  case GL_SHADER_SOURCE_LENGTH:
    glGetShaderiv(shader, pname, &value);
    return scope.Close(JS_INT(static_cast<long>(value)));
  default:
    return ThrowException(Exception::TypeError(String::New("GetShaderParameter: Invalid Enum")));
  }
}

JS_METHOD(GetShaderInfoLog) {
  HandleScope scope;

  int id = args[0]->Int32Value();
  int Len = 1024;
  char Error[1024];
  glGetShaderInfoLog(id, 1024, &Len, Error);

  return scope.Close(String::New(Error));
}


JS_METHOD(CreateProgram) {
  HandleScope scope;

  GLuint program=glCreateProgram();
  #ifdef LOGGING
  cout<<"createProgram "<<program<<endl;
  #endif
  registerGLObj(GLOBJECT_TYPE_PROGRAM, program);
  return scope.Close(Number::New(program));
}


JS_METHOD(AttachShader) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  int shader = args[1]->Int32Value();

  glAttachShader(program, shader);

  return scope.Close(Undefined());
}


JS_METHOD(LinkProgram) {
  HandleScope scope;

  glLinkProgram(args[0]->Int32Value());

  return scope.Close(Undefined());
}


JS_METHOD(GetProgramParameter) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  int pname = args[1]->Int32Value();

  int value = 0;
  switch (pname) {
  case GL_DELETE_STATUS:
  case GL_LINK_STATUS:
  case GL_VALIDATE_STATUS:
    glGetProgramiv(program, pname, &value);
    return scope.Close(JS_BOOL(static_cast<bool>(value!=0)));
  case GL_ATTACHED_SHADERS:
  case GL_ACTIVE_ATTRIBUTES:
  case GL_ACTIVE_UNIFORMS:
    glGetProgramiv(program, pname, &value);
    return scope.Close(JS_INT(static_cast<long>(value)));
  default:
    return ThrowException(Exception::TypeError(String::New("GetProgramParameter: Invalid Enum")));
  }
}


JS_METHOD(GetUniformLocation) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  String::AsciiValue name(args[1]);

  return scope.Close(JS_INT(glGetUniformLocation(program, *name)));
}


JS_METHOD(ClearColor) {
  HandleScope scope;

  float red = (float) args[0]->NumberValue();
  float green = (float) args[1]->NumberValue();
  float blue = (float) args[2]->NumberValue();
  float alpha = (float) args[3]->NumberValue();

  glClearColor(red, green, blue, alpha);

  return scope.Close(Undefined());
}


JS_METHOD(ClearDepth) {
  HandleScope scope;

  float depth = (float) args[0]->NumberValue();

  glClearDepthf(depth);

  return scope.Close(Undefined());
}

JS_METHOD(Disable) {
  HandleScope scope;

  glDisable(args[0]->Int32Value());
  return scope.Close(Undefined());
}

JS_METHOD(Enable) {
  HandleScope scope;

  glEnable(args[0]->Int32Value());
  return scope.Close(Undefined());
}


JS_METHOD(CreateTexture) {
  HandleScope scope;

  GLuint texture;
  glGenTextures(1, &texture);
  #ifdef LOGGING
  cout<<"createTexture "<<texture<<endl;
  #endif
  registerGLObj(GLOBJECT_TYPE_TEXTURE, texture);
  return scope.Close(Number::New(texture));
}


JS_METHOD(BindTexture) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int texture = args[1]->IsNull() ? 0 : args[1]->Int32Value();

  glBindTexture(target, texture);
  return scope.Close(Undefined());
}


JS_METHOD(TexImage2D) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int level = args[1]->Int32Value();
  int internalformat = args[2]->Int32Value();
  int width = args[3]->Int32Value();
  int height = args[4]->Int32Value();
  int border = args[5]->Int32Value();
  int format = args[6]->Int32Value();
  int type = args[7]->Int32Value();
  void *pixels=getImageData(args[8]);

  glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);

  return scope.Close(Undefined());
}


JS_METHOD(TexParameteri) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  int param = args[2]->Int32Value();

  glTexParameteri(target, pname, param);

  return scope.Close(Undefined());
}

JS_METHOD(TexParameterf) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  float param = (float) args[2]->NumberValue();

  glTexParameterf(target, pname, param);

  return scope.Close(Undefined());
}


JS_METHOD(Clear) {
  HandleScope scope;

  glClear(args[0]->Int32Value());

  return scope.Close(Undefined());
}


JS_METHOD(UseProgram) {
  HandleScope scope;

  glUseProgram(args[0]->Int32Value());

  return scope.Close(Undefined());
}

JS_METHOD(CreateBuffer) {
  HandleScope scope;

  GLuint buffer;
  glGenBuffers(1, &buffer);
  #ifdef LOGGING
  cout<<"createBuffer "<<buffer<<endl;
  #endif
  registerGLObj(GLOBJECT_TYPE_BUFFER, buffer);
  return scope.Close(Number::New(buffer));
}

JS_METHOD(BindBuffer) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int buffer = args[1]->Uint32Value();
  glBindBuffer(target,buffer);

  return scope.Close(Undefined());
}


JS_METHOD(CreateFramebuffer) {
  HandleScope scope;

  GLuint buffer;
  glGenFramebuffers(1, &buffer);
  #ifdef LOGGING
  cout<<"createFrameBuffer "<<buffer<<endl;
  #endif
  registerGLObj(GLOBJECT_TYPE_FRAMEBUFFER, buffer);
  return scope.Close(Number::New(buffer));
}


JS_METHOD(BindFramebuffer) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int buffer = args[1]->IsNull() ? 0 : args[1]->Int32Value();

  glBindFramebuffer(target, buffer);

  return scope.Close(Undefined());
}


JS_METHOD(FramebufferTexture2D) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int attachment = args[1]->Int32Value();
  int textarget = args[2]->Int32Value();
  int texture = args[3]->Int32Value();
  int level = args[4]->Int32Value();

  glFramebufferTexture2D(target, attachment, textarget, texture, level);

  return scope.Close(Undefined());
}


JS_METHOD(BufferData) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  if(args[1]->IsObject()) {
    Local<Object> obj = Local<Object>::Cast(args[1]);
    GLenum usage = args[2]->Int32Value();

    int element_size = SizeOfArrayElementForType(obj->GetIndexedPropertiesExternalArrayDataType());
    GLsizeiptr size = obj->GetIndexedPropertiesExternalArrayDataLength() * element_size;
    void* data = obj->GetIndexedPropertiesExternalArrayData();
    glBufferData(target, size, data, usage);
  }
  else if(args[1]->IsNumber()) {
    GLsizeiptr size = args[1]->Uint32Value();
    GLenum usage = args[2]->Int32Value();
    glBufferData(target, size, NULL, usage);
  }
  return scope.Close(Undefined());
}


JS_METHOD(BufferSubData) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int offset = args[1]->Int32Value();
  Local<Object> obj = Local<Object>::Cast(args[2]);

  int element_size = SizeOfArrayElementForType( obj->GetIndexedPropertiesExternalArrayDataType());
  int size = obj->GetIndexedPropertiesExternalArrayDataLength() * element_size;
  void* data = obj->GetIndexedPropertiesExternalArrayData();

  glBufferSubData(target, offset, size, data);

  return scope.Close(Undefined());
}


JS_METHOD(BlendEquation) {
  HandleScope scope;

  int mode=args[0]->Int32Value();;

  glBlendEquation(mode);

  return scope.Close(Undefined());
}


JS_METHOD(BlendFunc) {
  HandleScope scope;

  int sfactor=args[0]->Int32Value();;
  int dfactor=args[1]->Int32Value();;

  glBlendFunc(sfactor,dfactor);

  return scope.Close(Undefined());
}


JS_METHOD(EnableVertexAttribArray) {
  HandleScope scope;

  glEnableVertexAttribArray(args[0]->Int32Value());

  return scope.Close(Undefined());
}


JS_METHOD(VertexAttribPointer) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  int size = args[1]->Int32Value();
  int type = args[2]->Int32Value();
  int normalized = args[3]->BooleanValue();
  int stride = args[4]->Int32Value();
  int offset = args[5]->Int32Value();

  //    printf("VertexAttribPointer %d %d %d %d %d %d\n", indx, size, type, normalized, stride, offset);
  glVertexAttribPointer(indx, size, type, normalized, stride, (const GLvoid *)offset);

  return scope.Close(Undefined());
}


JS_METHOD(ActiveTexture) {
  HandleScope scope;

  glActiveTexture(args[0]->Int32Value());
  return scope.Close(Undefined());
}


JS_METHOD(DrawElements) {
  HandleScope scope;

  int mode = args[0]->Int32Value();
  int count = args[1]->Int32Value();
  int type = args[2]->Int32Value();
  GLvoid *offset = reinterpret_cast<GLvoid*>(args[3]->Uint32Value());
  glDrawElements(mode, count, type, offset);
  return scope.Close(Undefined());
}


JS_METHOD(Flush) {
  HandleScope scope;
  glFlush();
  return scope.Close(Undefined());
}

JS_METHOD(Finish) {
  HandleScope scope;
  glFinish();
  return scope.Close(Undefined());
}

JS_METHOD(VertexAttrib1f) {
  HandleScope scope;

  GLuint indx = args[0]->Int32Value();
  float x = (float) args[1]->NumberValue();

  glVertexAttrib1f(indx, x);
  return scope.Close(Undefined());
}

JS_METHOD(VertexAttrib2f) {
  HandleScope scope;

  GLuint indx = args[0]->Int32Value();
  float x = (float) args[1]->NumberValue();
  float y = (float) args[2]->NumberValue();

  glVertexAttrib2f(indx, x, y);
  return scope.Close(Undefined());
}

JS_METHOD(VertexAttrib3f) {
  HandleScope scope;

  GLuint indx = args[0]->Int32Value();
  float x = (float) args[1]->NumberValue();
  float y = (float) args[2]->NumberValue();
  float z = (float) args[3]->NumberValue();

  glVertexAttrib3f(indx, x, y, z);
  return scope.Close(Undefined());
}

JS_METHOD(VertexAttrib4f) {
  HandleScope scope;

  GLuint indx = args[0]->Int32Value();
  float x = (float) args[1]->NumberValue();
  float y = (float) args[2]->NumberValue();
  float z = (float) args[3]->NumberValue();
  float w = (float) args[4]->NumberValue();

  glVertexAttrib4f(indx, x, y, z, w);
  return scope.Close(Undefined());
}

JS_METHOD(VertexAttrib1fv) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  GLfloat *data=arg2v<GLfloat>(Array::Cast(*args[1]),true,0,NULL);
  glVertexAttrib1fv(indx, data);
  delete data;

  return scope.Close(Undefined());
}

JS_METHOD(VertexAttrib2fv) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  GLfloat *data=arg2v<GLfloat>(Array::Cast(*args[1]),true,0,NULL);
  glVertexAttrib2fv(indx, data);
  delete data;

  return scope.Close(Undefined());
}

JS_METHOD(VertexAttrib3fv) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  GLfloat *data=arg2v<GLfloat>(Array::Cast(*args[1]),true,0,NULL);
  glVertexAttrib3fv(indx, data);
  delete data;

  return scope.Close(Undefined());
}

JS_METHOD(VertexAttrib4fv) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  GLfloat *data=arg2v<GLfloat>(Array::Cast(*args[1]),true,0,NULL);
  glVertexAttrib4fv(indx, data);
  delete data;

  return scope.Close(Undefined());
}

JS_METHOD(BlendColor) {
  HandleScope scope;

  GLclampf r= (float) args[0]->NumberValue();
  GLclampf g= (float) args[1]->NumberValue();
  GLclampf b= (float) args[2]->NumberValue();
  GLclampf a= (float) args[3]->NumberValue();

  glBlendColor(r,g,b,a);
  return scope.Close(Undefined());
}

JS_METHOD(BlendEquationSeparate) {
  HandleScope scope;

  GLenum modeRGB= args[0]->Int32Value();
  GLenum modeAlpha= args[1]->Int32Value();

  glBlendEquationSeparate(modeRGB,modeAlpha);
  return scope.Close(Undefined());
}

JS_METHOD(BlendFuncSeparate) {
  HandleScope scope;

  GLenum srcRGB= args[0]->Int32Value();
  GLenum dstRGB= args[1]->Int32Value();
  GLenum srcAlpha= args[2]->Int32Value();
  GLenum dstAlpha= args[3]->Int32Value();

  glBlendFuncSeparate(srcRGB,dstRGB,srcAlpha,dstAlpha);
  return scope.Close(Undefined());
}

JS_METHOD(ClearStencil) {
  HandleScope scope;

  GLint s = args[0]->Int32Value();

  glClearStencil(s);
  return scope.Close(Undefined());
}

JS_METHOD(ColorMask) {
  HandleScope scope;

  GLboolean r = args[0]->BooleanValue();
  GLboolean g = args[1]->BooleanValue();
  GLboolean b = args[2]->BooleanValue();
  GLboolean a = args[3]->BooleanValue();

  glColorMask(r,g,b,a);
  return scope.Close(Undefined());
}

JS_METHOD(CopyTexImage2D) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLint level = args[1]->Int32Value();
  GLenum internalformat = args[2]->Int32Value();
  GLint x = args[3]->Int32Value();
  GLint y = args[4]->Int32Value();
  GLsizei width = args[5]->Int32Value();
  GLsizei height = args[6]->Int32Value();
  GLint border = args[7]->Int32Value();

  glCopyTexImage2D( target, level, internalformat, x, y, width, height, border);
  return scope.Close(Undefined());
}

JS_METHOD(CopyTexSubImage2D) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLint level = args[1]->Int32Value();
  GLint xoffset = args[2]->Int32Value();
  GLint yoffset = args[3]->Int32Value();
  GLint x = args[4]->Int32Value();
  GLint y = args[5]->Int32Value();
  GLsizei width = args[6]->Int32Value();
  GLsizei height = args[7]->Int32Value();

  glCopyTexSubImage2D( target, level, xoffset, yoffset, x, y, width, height);
  return scope.Close(Undefined());
}

JS_METHOD(CullFace) {
  HandleScope scope;

  GLenum mode = args[0]->Int32Value();

  glCullFace(mode);
  return scope.Close(Undefined());
}

JS_METHOD(DepthMask) {
  HandleScope scope;

  GLboolean flag = args[0]->BooleanValue();

  glDepthMask(flag);
  return scope.Close(Undefined());
}

JS_METHOD(DepthRange) {
  HandleScope scope;

  GLclampf zNear = (float) args[0]->NumberValue();
  GLclampf zFar = (float) args[1]->NumberValue();

  glDepthRangef(zNear, zFar);
  return scope.Close(Undefined());
}

JS_METHOD(DisableVertexAttribArray) {
  HandleScope scope;

  GLuint index = args[0]->Int32Value();

  glDisableVertexAttribArray(index);
  return scope.Close(Undefined());
}

JS_METHOD(Hint) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLenum mode = args[1]->Int32Value();

  glHint(target, mode);
  return scope.Close(Undefined());
}

JS_METHOD(IsEnabled) {
  HandleScope scope;

  GLenum cap = args[0]->Int32Value();

  bool ret=glIsEnabled(cap)!=0;
  return scope.Close(Boolean::New(ret));
}

JS_METHOD(LineWidth) {
  HandleScope scope;

  GLfloat width = (float) args[0]->NumberValue();

  glLineWidth(width);
  return scope.Close(Undefined());
}

JS_METHOD(PolygonOffset) {
  HandleScope scope;

  GLfloat factor = (float) args[0]->NumberValue();
  GLfloat units = (float) args[1]->NumberValue();

  glPolygonOffset(factor, units);
  return scope.Close(Undefined());
}

JS_METHOD(SampleCoverage) {
  HandleScope scope;

  GLclampf value = (float) args[0]->NumberValue();
  GLboolean invert = args[1]->BooleanValue();

  glSampleCoverage(value, invert);
  return scope.Close(Undefined());
}

JS_METHOD(Scissor) {
  HandleScope scope;

  GLint x = args[0]->Int32Value();
  GLint y = args[1]->Int32Value();
  GLsizei width = args[2]->Int32Value();
  GLsizei height = args[3]->Int32Value();

  glScissor(x, y, width, height);
  return scope.Close(Undefined());
}

JS_METHOD(StencilFunc) {
  HandleScope scope;

  GLenum func = args[0]->Int32Value();
  GLint ref = args[1]->Int32Value();
  GLuint mask = args[2]->Int32Value();

  glStencilFunc(func, ref, mask);
  return scope.Close(Undefined());
}

JS_METHOD(StencilFuncSeparate) {
  HandleScope scope;

  GLenum face = args[0]->Int32Value();
  GLenum func = args[1]->Int32Value();
  GLint ref = args[2]->Int32Value();
  GLuint mask = args[3]->Int32Value();

  glStencilFuncSeparate(face, func, ref, mask);
  return scope.Close(Undefined());
}

JS_METHOD(StencilMask) {
  HandleScope scope;

  GLuint mask = args[0]->Uint32Value();

  glStencilMask(mask);
  return scope.Close(Undefined());
}

JS_METHOD(StencilMaskSeparate) {
  HandleScope scope;

  GLenum face = args[0]->Int32Value();
  GLuint mask = args[1]->Uint32Value();

  glStencilMaskSeparate(face, mask);
  return scope.Close(Undefined());
}

JS_METHOD(StencilOp) {
  HandleScope scope;

  GLenum fail = args[0]->Int32Value();
  GLenum zfail = args[1]->Int32Value();
  GLenum zpass = args[2]->Int32Value();

  glStencilOp(fail, zfail, zpass);
  return scope.Close(Undefined());
}

JS_METHOD(StencilOpSeparate) {
  HandleScope scope;

  GLenum face = args[0]->Int32Value();
  GLenum fail = args[1]->Int32Value();
  GLenum zfail = args[2]->Int32Value();
  GLenum zpass = args[3]->Int32Value();

  glStencilOpSeparate(face, fail, zfail, zpass);
  return scope.Close(Undefined());
}

JS_METHOD(BindRenderbuffer) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLuint buffer = args[1]->IsNull() ? 0 : args[1]->Int32Value();

  glBindRenderbuffer(target, buffer);

  return scope.Close(Undefined());
}

JS_METHOD(CreateRenderbuffer) {
  HandleScope scope;

  GLuint renderbuffers;
  glGenRenderbuffers(1,&renderbuffers);
  #ifdef LOGGING
  cout<<"createRenderBuffer "<<renderbuffers<<endl;
  #endif
  registerGLObj(GLOBJECT_TYPE_RENDERBUFFER, renderbuffers);
  return scope.Close(Number::New(renderbuffers));
}

JS_METHOD(DeleteBuffer) {
  HandleScope scope;

  GLuint buffer = args[0]->Uint32Value();

  glDeleteBuffers(1,&buffer);
  return scope.Close(Undefined());
}

JS_METHOD(DeleteFramebuffer) {
  HandleScope scope;

  GLuint buffer = args[0]->Uint32Value();

  glDeleteFramebuffers(1,&buffer);
  return scope.Close(Undefined());
}

JS_METHOD(DeleteProgram) {
  HandleScope scope;

  GLuint program = args[0]->Uint32Value();

  glDeleteProgram(program);
  return scope.Close(Undefined());
}

JS_METHOD(DeleteRenderbuffer) {
  HandleScope scope;

  GLuint renderbuffer = args[0]->Uint32Value();

  glDeleteRenderbuffers(1, &renderbuffer);
  return scope.Close(Undefined());
}

JS_METHOD(DeleteShader) {
  HandleScope scope;

  GLuint shader = args[0]->Uint32Value();

  glDeleteShader(shader);
  return scope.Close(Undefined());
}

JS_METHOD(DeleteTexture) {
  HandleScope scope;

  GLuint texture = args[0]->Uint32Value();

  glDeleteTextures(1,&texture);
  return scope.Close(Undefined());
}

JS_METHOD(DetachShader) {
  HandleScope scope;

  GLuint program = args[0]->Uint32Value();
  GLuint shader = args[1]->Uint32Value();

  glDetachShader(program, shader);
  return scope.Close(Undefined());
}

JS_METHOD(FramebufferRenderbuffer) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLenum attachment = args[1]->Int32Value();
  GLenum renderbuffertarget = args[2]->Int32Value();
  GLuint renderbuffer = args[3]->Uint32Value();

  glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
  return scope.Close(Undefined());
}

JS_METHOD(GetVertexAttribOffset) {
  HandleScope scope;

  GLuint index = args[0]->Uint32Value();
  GLenum pname = args[1]->Int32Value();
  void *ret=NULL;

  glGetVertexAttribPointerv(index, pname, &ret);
  return scope.Close(JS_INT(ToGLuint(ret)));
}

JS_METHOD(IsBuffer) {
  HandleScope scope;

  return scope.Close(Boolean::New(glIsBuffer(args[0]->Uint32Value())!=0));
}

JS_METHOD(IsFramebuffer) {
  HandleScope scope;

  return scope.Close(JS_BOOL(glIsFramebuffer(args[0]->Uint32Value())!=0));
}

JS_METHOD(IsProgram) {
  HandleScope scope;

  return scope.Close(JS_BOOL(glIsProgram(args[0]->Uint32Value())!=0));
}

JS_METHOD(IsRenderbuffer) {
  HandleScope scope;

  return scope.Close(JS_BOOL(glIsRenderbuffer( args[0]->Uint32Value())!=0));
}

JS_METHOD(IsShader) {
  HandleScope scope;

  return scope.Close(JS_BOOL(glIsShader(args[0]->Uint32Value())!=0));
}

JS_METHOD(IsTexture) {
  HandleScope scope;

  return scope.Close(JS_BOOL(glIsTexture(args[0]->Uint32Value())!=0));
}

JS_METHOD(RenderbufferStorage) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLenum internalformat = args[1]->Int32Value();
  GLsizei width = args[2]->Uint32Value();
  GLsizei height = args[3]->Uint32Value();

  glRenderbufferStorage(target, internalformat, width, height);
  return scope.Close(Undefined());
}

JS_METHOD(GetShaderSource) {
  HandleScope scope;

  int shader = args[0]->Int32Value();

  GLint len;
  glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &len);
  GLchar *source=new GLchar[len];
  glGetShaderSource(shader, len, NULL, source);

  Local<String> str=String::New(source);
  delete source;

  return str;
}

JS_METHOD(ValidateProgram) {
  HandleScope scope;

  glValidateProgram(args[0]->Int32Value());

  return scope.Close(Undefined());
}

JS_METHOD(TexSubImage2D) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLint level = args[1]->Int32Value();
  GLint xoffset = args[2]->Int32Value();
  GLint yoffset = args[3]->Int32Value();
  GLsizei width = args[4]->Int32Value();
  GLsizei height = args[5]->Int32Value();
  GLenum format = args[6]->Int32Value();
  GLenum type = args[7]->Int32Value();
  void *pixels=getImageData(args[8]);

  glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);

  return scope.Close(Undefined());
}

JS_METHOD(ReadPixels) {
  HandleScope scope;

  GLint x = args[0]->Int32Value();
  GLint y = args[1]->Int32Value();
  GLsizei width = args[2]->Int32Value();
  GLsizei height = args[3]->Int32Value();
  GLenum format = args[4]->Int32Value();
  GLenum type = args[5]->Int32Value();
  void *pixels=getImageData(args[6]);

  glReadPixels(x, y, width, height, format, type, pixels);

  return scope.Close(Undefined());
}

JS_METHOD(GetTexParameter) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLenum pname = args[1]->Int32Value();

  GLint param_value=0;
  glGetTexParameteriv(target, pname, &param_value);

  return scope.Close(Number::New(param_value));
}

JS_METHOD(GetActiveAttrib) {
  HandleScope scope;

  GLuint program = args[0]->Int32Value();
  GLuint index = args[1]->Int32Value();

  char name[1024];
  GLsizei length=0;
  GLenum type;
  GLsizei size;
  glGetActiveAttrib(program, index, 1024, &length, &size, &type, name);

  Local<Array> activeInfo = Array::New(3);
  activeInfo->Set(JS_STR("size"), JS_INT(size));
  activeInfo->Set(JS_STR("type"), JS_INT((int)type));
  activeInfo->Set(JS_STR("name"), JS_STR(name));

  return scope.Close(activeInfo);
}

JS_METHOD(GetActiveUniform) {
  HandleScope scope;

  GLuint program = args[0]->Int32Value();
  GLuint index = args[1]->Int32Value();

  char name[1024];
  GLsizei length=0;
  GLenum type;
  GLsizei size;
  glGetActiveUniform(program, index, 1024, &length, &size, &type, name);

  Local<Array> activeInfo = Array::New(3);
  activeInfo->Set(JS_STR("size"), JS_INT(size));
  activeInfo->Set(JS_STR("type"), JS_INT((int)type));
  activeInfo->Set(JS_STR("name"), JS_STR(name));

  return scope.Close(activeInfo);
}

JS_METHOD(GetAttachedShaders) {
  HandleScope scope;

  GLuint program = args[0]->Int32Value();

  GLuint shaders[1024];
  GLsizei count;
  glGetAttachedShaders(program, 1024, &count, shaders);

  Local<Array> shadersArr = Array::New(count);
  for(int i=0;i<count;i++)
    shadersArr->Set(i, JS_INT((int)shaders[i]));

  return scope.Close(shadersArr);
}

JS_METHOD(GetParameter) {
  HandleScope scope;

  GLenum name = args[0]->Int32Value();

  switch(name) {
  case GL_BLEND:
  case GL_CULL_FACE:
  case GL_DEPTH_TEST:
  case GL_DEPTH_WRITEMASK:
  case GL_DITHER:
  case GL_POLYGON_OFFSET_FILL:
  case GL_SAMPLE_COVERAGE_INVERT:
  case GL_SCISSOR_TEST:
  case GL_STENCIL_TEST:
  case 0x9240 /* UNPACK_FLIP_Y_WEBGL */:
  case 0x9241 /* UNPACK_PREMULTIPLY_ALPHA_WEBGL*/:
  {
    // return a boolean
    GLboolean params;
    ::glGetBooleanv(name, &params);
    return scope.Close(JS_BOOL(params!=0));
  }
  case GL_DEPTH_CLEAR_VALUE:
  case GL_LINE_WIDTH:
  case GL_POLYGON_OFFSET_FACTOR:
  case GL_POLYGON_OFFSET_UNITS:
  case GL_SAMPLE_COVERAGE_VALUE:
  {
    // return a float
    GLfloat params;
    ::glGetFloatv(name, &params);
    return scope.Close(JS_FLOAT(params));
  }
  case GL_RENDERER:
  case GL_SHADING_LANGUAGE_VERSION:
  case GL_VENDOR:
  case GL_VERSION:
  case GL_EXTENSIONS:
  {
    // return a string
    char *params=(char*) ::glGetString(name);
    return scope.Close(params ? JS_STR(params) : Undefined());
  }
  case GL_MAX_VIEWPORT_DIMS:
  {
    // return a int32[2]
    GLint params[2];
    ::glGetIntegerv(name, params);

    Local<Array> arr=Array::New(2);
    arr->Set(0,JS_INT(params[0]));
    arr->Set(1,JS_INT(params[1]));
    return scope.Close(arr);
  }
  case GL_SCISSOR_BOX:
  case GL_VIEWPORT:
  {
    // return a int32[4]
    GLint params[4];
    ::glGetIntegerv(name, params);

    Local<Array> arr=Array::New(4);
    arr->Set(0,JS_INT(params[0]));
    arr->Set(1,JS_INT(params[1]));
    arr->Set(2,JS_INT(params[2]));
    arr->Set(3,JS_INT(params[3]));
    return scope.Close(arr);
  }
  case GL_ALIASED_LINE_WIDTH_RANGE:
  case GL_ALIASED_POINT_SIZE_RANGE:
  case GL_DEPTH_RANGE:
  {
    // return a float[2]
    GLfloat params[2];
    ::glGetFloatv(name, params);
    Local<Array> arr=Array::New(2);
    arr->Set(0,JS_FLOAT(params[0]));
    arr->Set(1,JS_FLOAT(params[1]));
    return scope.Close(arr);
  }
  case GL_BLEND_COLOR:
  case GL_COLOR_CLEAR_VALUE:
  {
    // return a float[4]
    GLfloat params[4];
    ::glGetFloatv(name, params);
    Local<Array> arr=Array::New(4);
    arr->Set(0,JS_FLOAT(params[0]));
    arr->Set(1,JS_FLOAT(params[1]));
    arr->Set(2,JS_FLOAT(params[2]));
    arr->Set(3,JS_FLOAT(params[3]));
    return scope.Close(arr);
  }
  case GL_COLOR_WRITEMASK:
  {
    // return a boolean[4]
    GLboolean params[4];
    ::glGetBooleanv(name, params);
    Local<Array> arr=Array::New(4);
    arr->Set(0,JS_BOOL(params[0]==1));
    arr->Set(1,JS_BOOL(params[1]==1));
    arr->Set(2,JS_BOOL(params[2]==1));
    arr->Set(3,JS_BOOL(params[3]==1));
    return scope.Close(arr);
  }
  case GL_ARRAY_BUFFER_BINDING:
  case GL_CURRENT_PROGRAM:
  case GL_ELEMENT_ARRAY_BUFFER_BINDING:
  case GL_FRAMEBUFFER_BINDING:
  case GL_RENDERBUFFER_BINDING:
  case GL_TEXTURE_BINDING_2D:
  case GL_TEXTURE_BINDING_CUBE_MAP:
  {
    GLint params;
    ::glGetIntegerv(name, &params);
    return scope.Close(JS_INT(params));
  }
  default: {
    // return a long
    GLint params;
    ::glGetIntegerv(name, &params);
    return scope.Close(JS_INT(params));
  }
  }

  return scope.Close(Undefined());
}

JS_METHOD(GetBufferParameter) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLenum pname = args[1]->Int32Value();

  GLint params;
  glGetBufferParameteriv(target,pname,&params);
  return scope.Close(JS_INT(params));
}

JS_METHOD(GetFramebufferAttachmentParameter) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLenum attachment = args[1]->Int32Value();
  GLenum pname = args[2]->Int32Value();

  GLint params;
  glGetFramebufferAttachmentParameteriv(target,attachment, pname,&params);
  return scope.Close(JS_INT(params));
}

JS_METHOD(GetProgramInfoLog) {
  HandleScope scope;

  GLuint program = args[0]->Int32Value();
  int Len = 1024;
  char Error[1024];
  glGetProgramInfoLog(program, 1024, &Len, Error);

  return scope.Close(String::New(Error));
}

JS_METHOD(GetRenderbufferParameter) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  int value = 0;
  glGetRenderbufferParameteriv(target,pname,&value);

  return scope.Close(JS_INT(value));
}

JS_METHOD(GetUniform) {
  HandleScope scope;

  GLuint program = args[0]->Int32Value();
  GLint location = args[1]->Int32Value();
  if(location < 0 ) return scope.Close(Undefined());

  float data[16]; // worst case scenario is 16 floats

  glGetUniformfv(program, location, data);

  Local<Array> arr=Array::New(16);
  for(int i=0;i<16;i++)
    arr->Set(i,JS_FLOAT(data[i]));

  return scope.Close(arr);
}

JS_METHOD(GetVertexAttrib) {
  HandleScope scope;

  GLuint index = args[0]->Int32Value();
  GLuint pname = args[1]->Int32Value();

  GLint value=0;

  switch (pname) {
  case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
  case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
    glGetVertexAttribiv(index,pname,&value);
    return scope.Close(JS_BOOL(value!=0));
  case GL_VERTEX_ATTRIB_ARRAY_SIZE:
  case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
  case GL_VERTEX_ATTRIB_ARRAY_TYPE:
    glGetVertexAttribiv(index,pname,&value);
    return scope.Close(JS_INT(value));
  case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
    glGetVertexAttribiv(index,pname,&value);
    return scope.Close(JS_INT(value));
  case GL_CURRENT_VERTEX_ATTRIB: {
    float vextex_attribs[4];
    glGetVertexAttribfv(index,pname,vextex_attribs);
    Local<Array> arr=Array::New(4);
    arr->Set(0,JS_FLOAT(vextex_attribs[0]));
    arr->Set(1,JS_FLOAT(vextex_attribs[1]));
    arr->Set(2,JS_FLOAT(vextex_attribs[2]));
    arr->Set(3,JS_FLOAT(vextex_attribs[3]));
    return scope.Close(arr);
  }
  default:
    return ThrowError("GetVertexAttrib: Invalid Enum");
  }

  return scope.Close(Undefined());
}

JS_METHOD(GetSupportedExtensions) {
  HandleScope scope;

  char *extensions=(char*) glGetString(GL_EXTENSIONS);

  return scope.Close(JS_STR(extensions));
}

// TODO GetExtension(name) return the extension name if found, should be an object...
JS_METHOD(GetExtension) {
  HandleScope scope;

  String::AsciiValue name(args[0]);
  char *sname=*name;
  char *extensions=(char*) glGetString(GL_EXTENSIONS);

  char *ext=strcasestr(extensions, sname);

  if(!ext) return scope.Close(Undefined());
  return scope.Close(JS_STR(ext, (int)::strlen(sname)));
}

JS_METHOD(CheckFramebufferStatus) {
  HandleScope scope;

  GLenum target=args[0]->Int32Value();

  return scope.Close(JS_INT((int)glCheckFramebufferStatus(target)));
}

JS_METHOD(Vertex3f) {
  HandleScope scope;

  float x = (float) args[0]->NumberValue();
  float y = (float) args[1]->NumberValue();
  float z = (float) args[2]->NumberValue();

  glVertex3f(x, y, z);
  return scope.Close(Undefined());
}

JS_METHOD(Color3b) {
  HandleScope scope;

  GLbyte x = (GLbyte) args[0]->Int32Value();
  GLbyte y = (GLbyte) args[1]->Int32Value();
  GLbyte z = (GLbyte) args[2]->Int32Value();

  glColor3b(x, y, z);
  return scope.Close(Undefined());
}

JS_METHOD(Color3s) {
  HandleScope scope;

  GLshort x = (GLshort) args[0]->Int32Value();
  GLshort y = (GLshort) args[1]->Int32Value();
  GLshort z = (GLshort) args[2]->Int32Value();

  glColor3s(x, y, z);
  return scope.Close(Undefined());
}

JS_METHOD(Color3i) {
  HandleScope scope;

  GLint x = (GLint) args[0]->Int32Value();
  GLint y = (GLint) args[1]->Int32Value();
  GLint z = (GLint) args[2]->Int32Value();

  glColor3i(x, y, z);
  return scope.Close(Undefined());
}

JS_METHOD(Color3f) {
  HandleScope scope;

  GLfloat x = (GLfloat) args[0]->NumberValue();
  GLfloat y = (GLfloat) args[1]->NumberValue();
  GLfloat z = (GLfloat) args[2]->NumberValue();

  glColor3f(x, y, z);
  return scope.Close(Undefined());
}

JS_METHOD(Color3d) {
  HandleScope scope;

  GLdouble x = (GLdouble) args[0]->NumberValue();
  GLdouble y = (GLdouble) args[1]->NumberValue();
  GLdouble z = (GLdouble) args[2]->NumberValue();

  glColor3d(x, y, z);
  return scope.Close(Undefined());
}

JS_METHOD(Color3us) {
  HandleScope scope;

  GLushort x = (GLushort) args[0]->Int32Value();
  GLushort y = (GLushort) args[1]->Int32Value();
  GLushort z = (GLushort) args[2]->Int32Value();

  glColor3us(x, y, z);
  return scope.Close(Undefined());
}

JS_METHOD(Color3ui) {
  HandleScope scope;

  GLuint x = (GLuint) args[0]->Int32Value();
  GLuint y = (GLuint) args[1]->Int32Value();
  GLuint z = (GLuint) args[2]->Int32Value();

  glColor3i(x, y, z);
  return scope.Close(Undefined());
}

JS_METHOD(Color3ub) {
  HandleScope scope;

  GLubyte x = (GLubyte) args[0]->Int32Value();
  GLubyte y = (GLubyte) args[1]->Int32Value();
  GLubyte z = (GLubyte) args[2]->Int32Value();

  glColor3ub(x, y, z);
  return scope.Close(Undefined());
}

JS_METHOD(Color4b) {
  HandleScope scope;

  GLbyte x = (GLbyte) args[0]->Int32Value();
  GLbyte y = (GLbyte) args[1]->Int32Value();
  GLbyte z = (GLbyte) args[2]->Int32Value();
  GLbyte a = (GLbyte) args[3]->Int32Value();

  glColor4b(x, y, z, a);
  return scope.Close(Undefined());
}

JS_METHOD(Color4s) {
  HandleScope scope;

  GLshort x = (GLshort) args[0]->Int32Value();
  GLshort y = (GLshort) args[1]->Int32Value();
  GLshort z = (GLshort) args[2]->Int32Value();
  GLshort a = (GLshort) args[3]->Int32Value();

  glColor4s(x, y, z, a);
  return scope.Close(Undefined());
}

JS_METHOD(Color4i) {
  HandleScope scope;

  GLint x = (GLint) args[0]->Int32Value();
  GLint y = (GLint) args[1]->Int32Value();
  GLint z = (GLint) args[2]->Int32Value();
  GLint a = (GLint) args[3]->Int32Value();

  glColor4i(x, y, z, a);
  return scope.Close(Undefined());
}

JS_METHOD(Color4f) {
  HandleScope scope;

  GLfloat x = (GLfloat) args[0]->NumberValue();
  GLfloat y = (GLfloat) args[1]->NumberValue();
  GLfloat z = (GLfloat) args[2]->NumberValue();
  GLfloat a = (GLfloat) args[3]->NumberValue();

  glColor4f(x, y, z, a);
  return scope.Close(Undefined());
}

JS_METHOD(Color4d) {
  HandleScope scope;

  GLdouble x = (GLdouble) args[0]->NumberValue();
  GLdouble y = (GLdouble) args[1]->NumberValue();
  GLdouble z = (GLdouble) args[2]->NumberValue();
  GLdouble a = (GLdouble) args[3]->NumberValue();

  glColor4d(x, y, z, a);
  return scope.Close(Undefined());
}

JS_METHOD(Color4us) {
  HandleScope scope;

  GLushort x = (GLushort) args[0]->Int32Value();
  GLushort y = (GLushort) args[1]->Int32Value();
  GLushort z = (GLushort) args[2]->Int32Value();
  GLushort a = (GLushort) args[3]->Int32Value();

  glColor4us(x, y, z, a);
  return scope.Close(Undefined());
}

JS_METHOD(Color4ui) {
  HandleScope scope;
  GLuint x = (GLuint) args[0]->Int32Value();
  GLuint y = (GLuint) args[1]->Int32Value();
  GLuint z = (GLuint) args[2]->Int32Value();
  GLuint a = (GLuint) args[3]->Int32Value();
  glColor4ui(x, y, z, a);
  return scope.Close(Undefined());
}

JS_METHOD(Color4ub) {
  HandleScope scope;
  GLubyte x = (GLubyte) args[0]->Int32Value();
  GLubyte y = (GLubyte) args[1]->Int32Value();
  GLubyte z = (GLubyte) args[2]->Int32Value();
  GLubyte a = (GLubyte) args[3]->Int32Value();
  glColor4ub(x, y, z, a);
  return scope.Close(Undefined());
}

JS_METHOD(Color3bv) {  
  HandleScope scope;
  unsigned int num=0;
  GLbyte *param=arg2v<GLbyte>(Array::Cast(*args[0]),false,3,&num);      
  glColor3bv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color3sv) {
  HandleScope scope;
  unsigned int num=0;
  GLshort *param=arg2v<GLshort>(Array::Cast(*args[0]),false,3,&num);      
  glColor3sv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color3iv) {
  HandleScope scope;
  unsigned int num=0;
  GLint *param=arg2v<GLint>(Array::Cast(*args[0]),false,3,&num);      
  glColor3iv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color3fv) {
  HandleScope scope;
  unsigned int num=0;
  GLfloat *param=arg2v<GLfloat>(Array::Cast(*args[0]),true,3,&num);      
  glColor3fv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color3dv) {
  HandleScope scope;
  unsigned int num=0;
  GLdouble *param=arg2v<GLdouble>(Array::Cast(*args[0]),true,3,&num);
  glColor3dv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color3usv) {
  HandleScope scope;
  unsigned int num=0;
  GLushort *param=arg2v<GLushort>(Array::Cast(*args[0]),false,3,&num);      
  glColor3usv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color3uiv) {
  HandleScope scope;
  unsigned int num=0;
  GLuint *param=arg2v<GLuint>(Array::Cast(*args[0]),false,3,&num);      
  glColor3uiv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color3ubv) {
  HandleScope scope;
  unsigned int num=0;
  GLubyte *param=arg2v<GLubyte>(Array::Cast(*args[0]),false,0,&num);      
  glColor3ubv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color4bv) {  
  HandleScope scope;
  unsigned int num=0;
  GLbyte *param=arg2v<GLbyte>(Array::Cast(*args[0]),false,4,&num);      
  glColor4bv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color4sv) {
  HandleScope scope;
  unsigned int num=0;
  GLshort *param=arg2v<GLshort>(Array::Cast(*args[0]),false,4,&num);      
  glColor4sv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color4iv) {
  HandleScope scope;
  unsigned int num=0;
  GLint *param=arg2v<GLint>(Array::Cast(*args[0]),false,0,&num);      
  glColor4iv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color4fv) {
  HandleScope scope;
  unsigned int num=0;  
  GLfloat *param=arg2v<GLfloat>(Array::Cast(*args[0]),true,0,&num);      
  glColor4fv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color4dv) {
  HandleScope scope;
  unsigned int num=0;
  GLdouble *param=arg2v<GLdouble>(Array::Cast(*args[0]),true,0,&num);      
  glColor4dv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color4usv) {
  HandleScope scope;
  unsigned int num=0;  
  GLushort *param=arg2v<GLushort>(Array::Cast(*args[0]),false,0,&num);      
  glColor4usv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color4uiv) {
  HandleScope scope;
  unsigned int num=0;  
  GLuint *param=arg2v<GLuint>(Array::Cast(*args[0]),false,0,&num);      
  glColor4uiv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Color4ubv) {
  HandleScope scope;
  unsigned int num=0;  
  GLubyte *param=arg2v<GLubyte>(Array::Cast(*args[0]),false,0,&num);      
  glColor4ubv(param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Rotatef) {
  HandleScope scope;

  float r = (float) args[0]->NumberValue();
  float x = (float) args[1]->NumberValue();
  float y = (float) args[2]->NumberValue();
  float z = (float) args[3]->NumberValue();

  glRotatef(r,x,y,z);
  return scope.Close(Undefined());
}

JS_METHOD(Begin) {
  HandleScope scope;
  GLenum target=args[0]->Int32Value();
  glBegin(target);
  return scope.Close(Undefined());
}

JS_METHOD(End) {
  HandleScope scope;
  glEnd();
  return scope.Close(Undefined());
}

JS_METHOD(LoadIdentity) {
  HandleScope scope;
  glLoadIdentity();
  return scope.Close(Undefined());
}

JS_METHOD(Ortho) {
  HandleScope scope;

  float x1 = (float) args[0]->NumberValue();
  float y1 = (float) args[1]->NumberValue();
  float z1 = (float) args[2]->NumberValue();
  float x2 = (float) args[3]->NumberValue();
  float y2 = (float) args[4]->NumberValue();
  float z2 = (float) args[5]->NumberValue();

  glOrtho(x1,y1,z1,x2,y2,z2);
  return scope.Close(Undefined());
}

JS_METHOD(MatrixMode) {
  HandleScope scope;
  GLenum target=args[0]->Int32Value();
  glMatrixMode(target);
  return scope.Close(Undefined());
}

JS_METHOD(Translatef) {
  HandleScope scope;
  float x1 = (float) args[0]->NumberValue();
  float y1 = (float) args[1]->NumberValue();
  float z1 = (float) args[2]->NumberValue();
  glTranslatef(x1,y1,z1);
  return scope.Close(Undefined());  
}

JS_METHOD(ShadeModel) {
  HandleScope scope;
  GLenum mode=args[0]->Int32Value();
  glShadeModel(mode);
  return scope.Close(Undefined());
}

JS_METHOD(TexCoord2f) {
  HandleScope scope;
  float x1 = (float) args[0]->NumberValue();
  float y1 = (float) args[1]->NumberValue();
  glTexCoord2f(x1,y1);
  return scope.Close(Undefined());  
}

JS_METHOD(Lightfv) {
  HandleScope scope;
  int light = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  unsigned int num=0;
  GLfloat *param=arg2v<GLfloat>(Array::Cast(*args[2]),true,0,&num);  
  glLightfv(light, pname, param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Lightiv) {
  HandleScope scope;
  int light = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  unsigned int num=0;
  GLint *param=arg2v<GLint>(Array::Cast(*args[2]),false,0,&num);  
  glLightiv(light, pname, param);
  delete param;
  return scope.Close(Undefined());
}

JS_METHOD(Lightf) {
  HandleScope scope;
  int light = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  float param = (float) args[2]->NumberValue();
  glLightf(light, pname, param);
  return scope.Close(Undefined());
}

JS_METHOD(Lighti) {
  HandleScope scope;
  int light = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  int param = args[2]->Int32Value();
  glLighti(light, pname, param);
  return scope.Close(Undefined());
}

JS_METHOD(Normal3b) {
  HandleScope scope;
  GLbyte nx = (GLbyte)args[0]->Int32Value();
  GLbyte ny = (GLbyte)args[1]->Int32Value();
  GLbyte nz = (GLbyte)args[2]->Int32Value();
  glNormal3b(nx,ny,nz);
  return scope.Close(Undefined());
}

JS_METHOD(Normal3d) {
  HandleScope scope;
  double nx = (double) args[0]->NumberValue();
  double ny = (double) args[0]->NumberValue();
  double nz = (double) args[0]->NumberValue();
  glNormal3d(nx,ny,nz);
  return scope.Close(Undefined());
}

JS_METHOD(Normal3f) {
  HandleScope scope;
  float nx = (float) args[0]->NumberValue();
  float ny = (float) args[0]->NumberValue();
  float nz = (float) args[0]->NumberValue();
  glNormal3f(nx,ny,nz);
  return scope.Close(Undefined());
}

JS_METHOD(Normal3i) {
  HandleScope scope;
  int nx = args[0]->Int32Value();
  int ny = args[1]->Int32Value();
  int nz = args[2]->Int32Value();
  glNormal3i(nx,ny,nz);
  return scope.Close(Undefined());
}

JS_METHOD(Normal3s) {
  HandleScope scope;
  short nx = args[0]->Int32Value();
  short ny = args[1]->Int32Value();
  short nz = args[2]->Int32Value();
  glNormal3s(nx,ny,nz);
  return scope.Close(Undefined());
}

JS_METHOD(Normal3bv) {
  HandleScope scope;
  unsigned int num=0;
  GLbyte *param=arg2v<GLbyte>(Array::Cast(*args[0]),false,0,&num);
  glNormal3bv(param);
  delete param;
  return scope.Close(Undefined());
}
JS_METHOD(Normal3dv) {
  HandleScope scope;
  unsigned int num=0;
  GLdouble *param=arg2v<GLdouble>(Array::Cast(*args[0]),true,0,&num);
  glNormal3dv(param);
  delete param;
  return scope.Close(Undefined());
}
JS_METHOD(Normal3fv) {
  HandleScope scope;
  unsigned int num=0;
  GLfloat *param=arg2v<GLfloat>(Array::Cast(*args[0]),true,3,&num);
  glNormal3fv(param);
  delete param;
  return scope.Close(Undefined());
}
JS_METHOD(Normal3iv) {
  HandleScope scope;
  unsigned int num=0;
  GLint *param=arg2v<GLint>(Array::Cast(*args[0]),false,0,&num);
  glNormal3iv(param);
  delete param;
  return scope.Close(Undefined());
}
JS_METHOD(Normal3sv) {
  HandleScope scope;
  unsigned int num=0;
  GLshort *param=arg2v<GLshort>(Array::Cast(*args[0]),false,0,&num);
  glNormal3sv(param);
  delete param;
  return scope.Close(Undefined());
}
JS_METHOD(PolygonMode) {
  HandleScope scope;
  int face = args[0]->Int32Value();
  int mode = args[1]->Int32Value();
  glPolygonMode(face,mode);
  return scope.Close(Undefined());
}

JS_METHOD(CreateList) {
  HandleScope scope;
  return scope.Close(JS_INT(glGenLists(1)));
}

JS_METHOD(NewList) {
  HandleScope scope;
  int list = args[0]->Int32Value();
  int mode = args[1]->Int32Value();
  glNewList(list,mode);
  return scope.Close(Undefined());
}

JS_METHOD(CallList) {
  HandleScope scope;
  int list = args[0]->Int32Value();
  glCallList(list);
  return scope.Close(Undefined());
}

JS_METHOD(EndList) {
  HandleScope scope;
  glEndList();
  return scope.Close(Undefined());
}

JS_METHOD(Fogi) {
  HandleScope scope;
  GLenum pname = (GLenum) args[0]->Int32Value();
  GLint param = (GLint) args[1]->Int32Value();
  glFogi(pname, param);
  return scope.Close(Undefined());
}

JS_METHOD(Fogf) {
  HandleScope scope;
  GLenum pname = (GLenum) args[0]->Int32Value();
  GLfloat param = (GLfloat) args[1]->NumberValue();
  glFogf(pname, param);
  return scope.Close(Undefined());
}

JS_METHOD(Fogiv) {
  HandleScope scope;
  unsigned num=0;
  GLenum pname = (GLenum) args[0]->Int32Value();
  GLint *param=arg2v<GLint>(Array::Cast(*args[1]),false,0,&num);
  glFogiv(pname,param);
  return scope.Close(Undefined());
}

JS_METHOD(Fogfv) {
  HandleScope scope;
  unsigned int num=0;
  GLenum pname = (GLenum) args[0]->Int32Value();
  GLfloat *array=arg2v<GLfloat>(Array::Cast(*args[1]),true,0,&num);
  glFogfv(pname,array);
  delete array;
  return scope.Close(Undefined());
}

struct GLObj {
  GLObjectType type;
  GLuint obj;
  GLObj(GLObjectType type, GLuint obj) {
    this->type=type;
    this->obj=obj;
  }
};

vector<GLObj*> globjs;
static bool atExit=false;

void registerGLObj(GLObjectType type, GLuint obj) {
  globjs.push_back(new GLObj(type,obj));
}


void unregisterGLObj(GLuint obj) {
  if(atExit) return;

  vector<GLObj*>::iterator it = globjs.begin();
  while(globjs.size() && it != globjs.end()) {
    GLObj *globj=*it;
    if(globj->obj==obj) {
      delete globj;
      globjs.erase(it);
      break;
    }
    ++it;
  }
}

void AtExit() {
  atExit=true;
  //glFinish();

  vector<GLObj*>::iterator it;

  #ifdef LOGGING
  cout<<"WebGL AtExit() called"<<endl;
  cout<<"  # objects allocated: "<<globjs.size()<<endl;
  it = globjs.begin();
  while(globjs.size() && it != globjs.end()) {
    GLObj *obj=*it;
    cout<<"[";
    switch(obj->type) {
    case GLOBJECT_TYPE_BUFFER: cout<<"buffer"; break;
    case GLOBJECT_TYPE_FRAMEBUFFER: cout<<"framebuffer"; break;
    case GLOBJECT_TYPE_PROGRAM: cout<<"program"; break;
    case GLOBJECT_TYPE_RENDERBUFFER: cout<<"renderbuffer"; break;
    case GLOBJECT_TYPE_SHADER: cout<<"shader"; break;
    case GLOBJECT_TYPE_TEXTURE: cout<<"texture"; break;
    };
    cout<<": "<<obj->obj<<"] ";
    ++it;
  }
  cout<<endl;
  #endif

  it = globjs.begin();
  while(globjs.size() && it != globjs.end()) {
    GLObj *globj=*it;
    GLuint obj=globj->obj;

    switch(globj->type) {
    case GLOBJECT_TYPE_PROGRAM:
      #ifdef LOGGING
      cout<<"  Destroying GL program "<<obj<<endl;
      #endif
      glDeleteProgram(obj);
      break;
    case GLOBJECT_TYPE_BUFFER:
      #ifdef LOGGING
      cout<<"  Destroying GL buffer "<<obj<<endl;
      #endif
      glDeleteBuffers(1,&obj);
      break;
    case GLOBJECT_TYPE_FRAMEBUFFER:
      #ifdef LOGGING
      cout<<"  Destroying GL frame buffer "<<obj<<endl;
      #endif
      glDeleteFramebuffers(1,&obj);
      break;
    case GLOBJECT_TYPE_RENDERBUFFER:
      #ifdef LOGGING
      cout<<"  Destroying GL render buffer "<<obj<<endl;
      #endif
      glDeleteRenderbuffers(1,&obj);
      break;
    case GLOBJECT_TYPE_SHADER:
      #ifdef LOGGING
      cout<<"  Destroying GL shader "<<obj<<endl;
      #endif
      glDeleteShader(obj);
      break;
    case GLOBJECT_TYPE_TEXTURE:
      #ifdef LOGGING
      cout<<"  Destroying GL texture "<<obj<<endl;
      #endif
      glDeleteTextures(1,&obj);
      break;
    default:
      #ifdef LOGGING
      cout<<"  Unknown object "<<obj<<endl;
      #endif
      break;
    }
    delete globj;
    ++it;
  }

  globjs.clear();
}

} // end namespace gl
