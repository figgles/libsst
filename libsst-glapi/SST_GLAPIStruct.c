/* AUTOGENERATED BY parsegl.c -- DO NOT MODIFY */
#include <SST/SST_GLAPIStruct.h>
#include "GLAPIPrivate.h"

void resolveGLAPI(const GLAPIResolver* resolver, struct SST_GLAPI* api)
{
	api->ActiveTexture = resolveGLSymbol(resolver, "glActiveTexture");
	api->AttachShader = resolveGLSymbol(resolver, "glAttachShader");
	api->BeginConditionalRender = resolveGLSymbol(resolver, "glBeginConditionalRender");
	api->BeginQuery = resolveGLSymbol(resolver, "glBeginQuery");
	api->BeginTransformFeedback = resolveGLSymbol(resolver, "glBeginTransformFeedback");
	api->BindAttribLocation = resolveGLSymbol(resolver, "glBindAttribLocation");
	api->BindBuffer = resolveGLSymbol(resolver, "glBindBuffer");
	api->BindBufferBase = resolveGLSymbol(resolver, "glBindBufferBase");
	api->BindBufferRange = resolveGLSymbol(resolver, "glBindBufferRange");
	api->BindFragDataLocation = resolveGLSymbol(resolver, "glBindFragDataLocation");
	api->BindFragDataLocationIndexed = resolveGLSymbol(resolver, "glBindFragDataLocationIndexed");
	api->BindFramebuffer = resolveGLSymbol(resolver, "glBindFramebuffer");
	api->BindRenderbuffer = resolveGLSymbol(resolver, "glBindRenderbuffer");
	api->BindSampler = resolveGLSymbol(resolver, "glBindSampler");
	api->BindTexture = resolveGLSymbol(resolver, "glBindTexture");
	api->BindVertexArray = resolveGLSymbol(resolver, "glBindVertexArray");
	api->BlendColor = resolveGLSymbol(resolver, "glBlendColor");
	api->BlendEquation = resolveGLSymbol(resolver, "glBlendEquation");
	api->BlendEquationSeparate = resolveGLSymbol(resolver, "glBlendEquationSeparate");
	api->BlendFunc = resolveGLSymbol(resolver, "glBlendFunc");
	api->BlendFuncSeparate = resolveGLSymbol(resolver, "glBlendFuncSeparate");
	api->BlitFramebuffer = resolveGLSymbol(resolver, "glBlitFramebuffer");
	api->BufferData = resolveGLSymbol(resolver, "glBufferData");
	api->BufferSubData = resolveGLSymbol(resolver, "glBufferSubData");
	api->CheckFramebufferStatus = resolveGLSymbol(resolver, "glCheckFramebufferStatus");
	api->ClampColor = resolveGLSymbol(resolver, "glClampColor");
	api->Clear = resolveGLSymbol(resolver, "glClear");
	api->ClearBufferiv = resolveGLSymbol(resolver, "glClearBufferiv");
	api->ClearBufferuiv = resolveGLSymbol(resolver, "glClearBufferuiv");
	api->ClearBufferfv = resolveGLSymbol(resolver, "glClearBufferfv");
	api->ClearBufferfi = resolveGLSymbol(resolver, "glClearBufferfi");
	api->ClearColor = resolveGLSymbol(resolver, "glClearColor");
	api->ClearDepth = resolveGLSymbol(resolver, "glClearDepth");
	api->ClearStencil = resolveGLSymbol(resolver, "glClearStencil");
	api->ClientWaitSync = resolveGLSymbol(resolver, "glClientWaitSync");
	api->ColorMask = resolveGLSymbol(resolver, "glColorMask");
	api->ColorMaski = resolveGLSymbol(resolver, "glColorMaski");
	api->CompileShader = resolveGLSymbol(resolver, "glCompileShader");
	api->CompressedTexImage1D = resolveGLSymbol(resolver, "glCompressedTexImage1D");
	api->CompressedTexImage2D = resolveGLSymbol(resolver, "glCompressedTexImage2D");
	api->CompressedTexImage3D = resolveGLSymbol(resolver, "glCompressedTexImage3D");
	api->CompressedTexSubImage1D = resolveGLSymbol(resolver, "glCompressedTexSubImage1D");
	api->CompressedTexSubImage2D = resolveGLSymbol(resolver, "glCompressedTexSubImage2D");
	api->CompressedTexSubImage3D = resolveGLSymbol(resolver, "glCompressedTexSubImage3D");
	api->CopyBufferSubData = resolveGLSymbol(resolver, "glCopyBufferSubData");
	api->CopyTexImage1D = resolveGLSymbol(resolver, "glCopyTexImage1D");
	api->CopyTexImage2D = resolveGLSymbol(resolver, "glCopyTexImage2D");
	api->CopyTexSubImage1D = resolveGLSymbol(resolver, "glCopyTexSubImage1D");
	api->CopyTexSubImage2D = resolveGLSymbol(resolver, "glCopyTexSubImage2D");
	api->CopyTexSubImage3D = resolveGLSymbol(resolver, "glCopyTexSubImage3D");
	api->CreateProgram = resolveGLSymbol(resolver, "glCreateProgram");
	api->CreateShader = resolveGLSymbol(resolver, "glCreateShader");
	api->CullFace = resolveGLSymbol(resolver, "glCullFace");
	api->DeleteBuffers = resolveGLSymbol(resolver, "glDeleteBuffers");
	api->DeleteFramebuffers = resolveGLSymbol(resolver, "glDeleteFramebuffers");
	api->DeleteProgram = resolveGLSymbol(resolver, "glDeleteProgram");
	api->DeleteQueries = resolveGLSymbol(resolver, "glDeleteQueries");
	api->DeleteRenderbuffers = resolveGLSymbol(resolver, "glDeleteRenderbuffers");
	api->DeleteSamplers = resolveGLSymbol(resolver, "glDeleteSamplers");
	api->DeleteShader = resolveGLSymbol(resolver, "glDeleteShader");
	api->DeleteSync = resolveGLSymbol(resolver, "glDeleteSync");
	api->DeleteTextures = resolveGLSymbol(resolver, "glDeleteTextures");
	api->DeleteVertexArrays = resolveGLSymbol(resolver, "glDeleteVertexArrays");
	api->DepthFunc = resolveGLSymbol(resolver, "glDepthFunc");
	api->DepthMask = resolveGLSymbol(resolver, "glDepthMask");
	api->DepthRange = resolveGLSymbol(resolver, "glDepthRange");
	api->DetachShader = resolveGLSymbol(resolver, "glDetachShader");
	api->Disable = resolveGLSymbol(resolver, "glDisable");
	api->DisableVertexAttribArray = resolveGLSymbol(resolver, "glDisableVertexAttribArray");
	api->Disablei = resolveGLSymbol(resolver, "glDisablei");
	api->DrawArrays = resolveGLSymbol(resolver, "glDrawArrays");
	api->DrawArraysInstanced = resolveGLSymbol(resolver, "glDrawArraysInstanced");
	api->DrawBuffer = resolveGLSymbol(resolver, "glDrawBuffer");
	api->DrawBuffers = resolveGLSymbol(resolver, "glDrawBuffers");
	api->DrawElements = resolveGLSymbol(resolver, "glDrawElements");
	api->DrawElementsBaseVertex = resolveGLSymbol(resolver, "glDrawElementsBaseVertex");
	api->DrawElementsInstanced = resolveGLSymbol(resolver, "glDrawElementsInstanced");
	api->DrawElementsInstancedBaseVertex = resolveGLSymbol(resolver, "glDrawElementsInstancedBaseVertex");
	api->DrawRangeElements = resolveGLSymbol(resolver, "glDrawRangeElements");
	api->DrawRangeElementsBaseVertex = resolveGLSymbol(resolver, "glDrawRangeElementsBaseVertex");
	api->Enable = resolveGLSymbol(resolver, "glEnable");
	api->EnableVertexAttribArray = resolveGLSymbol(resolver, "glEnableVertexAttribArray");
	api->Enablei = resolveGLSymbol(resolver, "glEnablei");
	api->EndQuery = resolveGLSymbol(resolver, "glEndQuery");
	api->EndTransformFeedback = resolveGLSymbol(resolver, "glEndTransformFeedback");
	api->FenceSync = resolveGLSymbol(resolver, "glFenceSync");
	api->Finish = resolveGLSymbol(resolver, "glFinish");
	api->Flush = resolveGLSymbol(resolver, "glFlush");
	api->FlushMappedBufferRange = resolveGLSymbol(resolver, "glFlushMappedBufferRange");
	api->FramebufferRenderbuffer = resolveGLSymbol(resolver, "glFramebufferRenderbuffer");
	api->FramebufferTexture = resolveGLSymbol(resolver, "glFramebufferTexture");
	api->FramebufferTexture1D = resolveGLSymbol(resolver, "glFramebufferTexture1D");
	api->FramebufferTexture2D = resolveGLSymbol(resolver, "glFramebufferTexture2D");
	api->FramebufferTexture3D = resolveGLSymbol(resolver, "glFramebufferTexture3D");
	api->FramebufferTextureLayer = resolveGLSymbol(resolver, "glFramebufferTextureLayer");
	api->FrontFace = resolveGLSymbol(resolver, "glFrontFace");
	api->GenBuffers = resolveGLSymbol(resolver, "glGenBuffers");
	api->GenFramebuffers = resolveGLSymbol(resolver, "glGenFramebuffers");
	api->GenQueries = resolveGLSymbol(resolver, "glGenQueries");
	api->GenRenderbuffers = resolveGLSymbol(resolver, "glGenRenderbuffers");
	api->GenSamplers = resolveGLSymbol(resolver, "glGenSamplers");
	api->GenTextures = resolveGLSymbol(resolver, "glGenTextures");
	api->GenVertexArrays = resolveGLSymbol(resolver, "glGenVertexArrays");
	api->GenerateMipmap = resolveGLSymbol(resolver, "glGenerateMipmap");
	api->GetBooleanv = resolveGLSymbol(resolver, "glGetBooleanv");
	api->GetDoublev = resolveGLSymbol(resolver, "glGetDoublev");
	api->GetFloatv = resolveGLSymbol(resolver, "glGetFloatv");
	api->GetIntegerv = resolveGLSymbol(resolver, "glGetIntegerv");
	api->GetInteger64v = resolveGLSymbol(resolver, "glGetInteger64v");
	api->GetActiveAttrib = resolveGLSymbol(resolver, "glGetActiveAttrib");
	api->GetActiveUniform = resolveGLSymbol(resolver, "glGetActiveUniform");
	api->GetActiveUniformBlockiv = resolveGLSymbol(resolver, "glGetActiveUniformBlockiv");
	api->GetActiveUniformBlockName = resolveGLSymbol(resolver, "glGetActiveUniformBlockName");
	api->GetActiveUniformName = resolveGLSymbol(resolver, "glGetActiveUniformName");
	api->GetActiveUniformsiv = resolveGLSymbol(resolver, "glGetActiveUniformsiv");
	api->GetAttachedShaders = resolveGLSymbol(resolver, "glGetAttachedShaders");
	api->GetAttribLocation = resolveGLSymbol(resolver, "glGetAttribLocation");
	api->GetBufferParameteriv = resolveGLSymbol(resolver, "glGetBufferParameteriv");
	api->GetBufferPointerv = resolveGLSymbol(resolver, "glGetBufferPointerv");
	api->GetBufferSubData = resolveGLSymbol(resolver, "glGetBufferSubData");
	api->GetCompressedTexImage = resolveGLSymbol(resolver, "glGetCompressedTexImage");
	api->GetError = resolveGLSymbol(resolver, "glGetError");
	api->GetFragDataIndex = resolveGLSymbol(resolver, "glGetFragDataIndex");
	api->GetFragDataLocation = resolveGLSymbol(resolver, "glGetFragDataLocation");
	api->GetFramebufferAttachmentParameteriv = resolveGLSymbol(resolver, "glGetFramebufferAttachmentParameteriv");
	api->GetMultisamplefv = resolveGLSymbol(resolver, "glGetMultisamplefv");
	api->GetProgramiv = resolveGLSymbol(resolver, "glGetProgramiv");
	api->GetProgramInfoLog = resolveGLSymbol(resolver, "glGetProgramInfoLog");
	api->GetQueryObjectiv = resolveGLSymbol(resolver, "glGetQueryObjectiv");
	api->GetQueryObjectuiv = resolveGLSymbol(resolver, "glGetQueryObjectuiv");
	api->GetQueryObjecti64v = resolveGLSymbol(resolver, "glGetQueryObjecti64v");
	api->GetQueryObjectui64v = resolveGLSymbol(resolver, "glGetQueryObjectui64v");
	api->GetQueryiv = resolveGLSymbol(resolver, "glGetQueryiv");
	api->GetRenderbufferParameteriv = resolveGLSymbol(resolver, "glGetRenderbufferParameteriv");
	api->GetSamplerParameterfv = resolveGLSymbol(resolver, "glGetSamplerParameterfv");
	api->GetSamplerParameteriv = resolveGLSymbol(resolver, "glGetSamplerParameteriv");
	api->GetShaderiv = resolveGLSymbol(resolver, "glGetShaderiv");
	api->GetShaderInfoLog = resolveGLSymbol(resolver, "glGetShaderInfoLog");
	api->GetShaderSource = resolveGLSymbol(resolver, "glGetShaderSource");
	api->GetString = resolveGLSymbol(resolver, "glGetString");
	api->GetStringi = resolveGLSymbol(resolver, "glGetStringi");
	api->GetSynciv = resolveGLSymbol(resolver, "glGetSynciv");
	api->GetTexImage = resolveGLSymbol(resolver, "glGetTexImage");
	api->GetTexLevelParameterfv = resolveGLSymbol(resolver, "glGetTexLevelParameterfv");
	api->GetTexLevelParameteriv = resolveGLSymbol(resolver, "glGetTexLevelParameteriv");
	api->GetTexParameterfv = resolveGLSymbol(resolver, "glGetTexParameterfv");
	api->GetTexParameteriv = resolveGLSymbol(resolver, "glGetTexParameteriv");
	api->GetTransformFeedbackVarying = resolveGLSymbol(resolver, "glGetTransformFeedbackVarying");
	api->GetUniformfv = resolveGLSymbol(resolver, "glGetUniformfv");
	api->GetUniformiv = resolveGLSymbol(resolver, "glGetUniformiv");
	api->GetUniformIndices = resolveGLSymbol(resolver, "glGetUniformIndices");
	api->GetUniformLocation = resolveGLSymbol(resolver, "glGetUniformLocation");
	api->GetVertexAttribdv = resolveGLSymbol(resolver, "glGetVertexAttribdv");
	api->GetVertexAttribfv = resolveGLSymbol(resolver, "glGetVertexAttribfv");
	api->GetVertexAttribiv = resolveGLSymbol(resolver, "glGetVertexAttribiv");
	api->GetVertexAttribIiv = resolveGLSymbol(resolver, "glGetVertexAttribIiv");
	api->GetVertexAttribIuiv = resolveGLSymbol(resolver, "glGetVertexAttribIuiv");
	api->GetVertexAttribPointerv = resolveGLSymbol(resolver, "glGetVertexAttribPointerv");
	api->Hint = resolveGLSymbol(resolver, "glHint");
	api->IsBuffer = resolveGLSymbol(resolver, "glIsBuffer");
	api->IsEnabled = resolveGLSymbol(resolver, "glIsEnabled");
	api->IsEnabledi = resolveGLSymbol(resolver, "glIsEnabledi");
	api->IsFramebuffer = resolveGLSymbol(resolver, "glIsFramebuffer");
	api->IsProgram = resolveGLSymbol(resolver, "glIsProgram");
	api->IsQuery = resolveGLSymbol(resolver, "glIsQuery");
	api->IsRenderbuffer = resolveGLSymbol(resolver, "glIsRenderbuffer");
	api->IsSampler = resolveGLSymbol(resolver, "glIsSampler");
	api->IsShader = resolveGLSymbol(resolver, "glIsShader");
	api->IsSync = resolveGLSymbol(resolver, "glIsSync");
	api->IsTexture = resolveGLSymbol(resolver, "glIsTexture");
	api->IsVertexArray = resolveGLSymbol(resolver, "glIsVertexArray");
	api->LineWidth = resolveGLSymbol(resolver, "glLineWidth");
	api->LinkProgram = resolveGLSymbol(resolver, "glLinkProgram");
	api->LogicOp = resolveGLSymbol(resolver, "glLogicOp");
	api->MapBuffer = resolveGLSymbol(resolver, "glMapBuffer");
	api->MapBufferRange = resolveGLSymbol(resolver, "glMapBufferRange");
	api->MultiDrawArrays = resolveGLSymbol(resolver, "glMultiDrawArrays");
	api->MultiDrawElements = resolveGLSymbol(resolver, "glMultiDrawElements");
	api->MultiDrawElementsBaseVertex = resolveGLSymbol(resolver, "glMultiDrawElementsBaseVertex");
	api->PixelStoref = resolveGLSymbol(resolver, "glPixelStoref");
	api->PixelStorei = resolveGLSymbol(resolver, "glPixelStorei");
	api->PointParameterf = resolveGLSymbol(resolver, "glPointParameterf");
	api->PointParameteri = resolveGLSymbol(resolver, "glPointParameteri");
	api->PointSize = resolveGLSymbol(resolver, "glPointSize");
	api->PolygonMode = resolveGLSymbol(resolver, "glPolygonMode");
	api->PolygonOffset = resolveGLSymbol(resolver, "glPolygonOffset");
	api->PrimitiveRestartIndex = resolveGLSymbol(resolver, "glPrimitiveRestartIndex");
	api->ProvokingVertex = resolveGLSymbol(resolver, "glProvokingVertex");
	api->QueryCounter = resolveGLSymbol(resolver, "glQueryCounter");
	api->ReadBuffer = resolveGLSymbol(resolver, "glReadBuffer");
	api->ReadPixels = resolveGLSymbol(resolver, "glReadPixels");
	api->RenderbufferStorage = resolveGLSymbol(resolver, "glRenderbufferStorage");
	api->RenderbufferStorageMultisample = resolveGLSymbol(resolver, "glRenderbufferStorageMultisample");
	api->SampleCoverage = resolveGLSymbol(resolver, "glSampleCoverage");
	api->SampleMaski = resolveGLSymbol(resolver, "glSampleMaski");
	api->SamplerParameterf = resolveGLSymbol(resolver, "glSamplerParameterf");
	api->SamplerParameteri = resolveGLSymbol(resolver, "glSamplerParameteri");
	api->SamplerParameterfv = resolveGLSymbol(resolver, "glSamplerParameterfv");
	api->SamplerParameteriv = resolveGLSymbol(resolver, "glSamplerParameteriv");
	api->SamplerParameterIiv = resolveGLSymbol(resolver, "glSamplerParameterIiv");
	api->SamplerParameterIuiv = resolveGLSymbol(resolver, "glSamplerParameterIuiv");
	api->Scissor = resolveGLSymbol(resolver, "glScissor");
	api->ShaderSource = resolveGLSymbol(resolver, "glShaderSource");
	api->StencilFunc = resolveGLSymbol(resolver, "glStencilFunc");
	api->StencilFuncSeparate = resolveGLSymbol(resolver, "glStencilFuncSeparate");
	api->StencilMask = resolveGLSymbol(resolver, "glStencilMask");
	api->StencilMaskSeparate = resolveGLSymbol(resolver, "glStencilMaskSeparate");
	api->StencilOp = resolveGLSymbol(resolver, "glStencilOp");
	api->StencilOpSeparate = resolveGLSymbol(resolver, "glStencilOpSeparate");
	api->TexBuffer = resolveGLSymbol(resolver, "glTexBuffer");
	api->TexImage1D = resolveGLSymbol(resolver, "glTexImage1D");
	api->TexImage2D = resolveGLSymbol(resolver, "glTexImage2D");
	api->TexImage2DMultisample = resolveGLSymbol(resolver, "glTexImage2DMultisample");
	api->TexImage3D = resolveGLSymbol(resolver, "glTexImage3D");
	api->TexImage3DMultisample = resolveGLSymbol(resolver, "glTexImage3DMultisample");
	api->TexParameterf = resolveGLSymbol(resolver, "glTexParameterf");
	api->TexParameteri = resolveGLSymbol(resolver, "glTexParameteri");
	api->TexParameterfv = resolveGLSymbol(resolver, "glTexParameterfv");
	api->TexParameteriv = resolveGLSymbol(resolver, "glTexParameteriv");
	api->TexParameterIiv = resolveGLSymbol(resolver, "glTexParameterIiv");
	api->TexParameterIuiv = resolveGLSymbol(resolver, "glTexParameterIuiv");
	api->TexSubImage1D = resolveGLSymbol(resolver, "glTexSubImage1D");
	api->TexSubImage2D = resolveGLSymbol(resolver, "glTexSubImage2D");
	api->TexSubImage3D = resolveGLSymbol(resolver, "glTexSubImage3D");
	api->TransformFeedbackVaryings = resolveGLSymbol(resolver, "glTransformFeedbackVaryings");
	api->Uniform1f = resolveGLSymbol(resolver, "glUniform1f");
	api->Uniform2f = resolveGLSymbol(resolver, "glUniform2f");
	api->Uniform3f = resolveGLSymbol(resolver, "glUniform3f");
	api->Uniform4f = resolveGLSymbol(resolver, "glUniform4f");
	api->Uniform1i = resolveGLSymbol(resolver, "glUniform1i");
	api->Uniform2i = resolveGLSymbol(resolver, "glUniform2i");
	api->Uniform3i = resolveGLSymbol(resolver, "glUniform3i");
	api->Uniform4i = resolveGLSymbol(resolver, "glUniform4i");
	api->Uniform1ui = resolveGLSymbol(resolver, "glUniform1ui");
	api->Uniform2ui = resolveGLSymbol(resolver, "glUniform2ui");
	api->Uniform3ui = resolveGLSymbol(resolver, "glUniform3ui");
	api->Uniform4ui = resolveGLSymbol(resolver, "glUniform4ui");
	api->Uniform1fv = resolveGLSymbol(resolver, "glUniform1fv");
	api->Uniform2fv = resolveGLSymbol(resolver, "glUniform2fv");
	api->Uniform3fv = resolveGLSymbol(resolver, "glUniform3fv");
	api->Uniform4fv = resolveGLSymbol(resolver, "glUniform4fv");
	api->Uniform1iv = resolveGLSymbol(resolver, "glUniform1iv");
	api->Uniform2iv = resolveGLSymbol(resolver, "glUniform2iv");
	api->Uniform3iv = resolveGLSymbol(resolver, "glUniform3iv");
	api->Uniform4iv = resolveGLSymbol(resolver, "glUniform4iv");
	api->Uniform1uiv = resolveGLSymbol(resolver, "glUniform1uiv");
	api->Uniform2uiv = resolveGLSymbol(resolver, "glUniform2uiv");
	api->Uniform3uiv = resolveGLSymbol(resolver, "glUniform3uiv");
	api->Uniform4uiv = resolveGLSymbol(resolver, "glUniform4uiv");
	api->UniformMatrix2fv = resolveGLSymbol(resolver, "glUniformMatrix2fv");
	api->UniformMatrix3fv = resolveGLSymbol(resolver, "glUniformMatrix3fv");
	api->UniformMatrix4fv = resolveGLSymbol(resolver, "glUniformMatrix4fv");
	api->UniformMatrix2x3fv = resolveGLSymbol(resolver, "glUniformMatrix2x3fv");
	api->UniformMatrix3x2fv = resolveGLSymbol(resolver, "glUniformMatrix3x2fv");
	api->UniformMatrix2x4fv = resolveGLSymbol(resolver, "glUniformMatrix2x4fv");
	api->UniformMatrix4x2fv = resolveGLSymbol(resolver, "glUniformMatrix4x2fv");
	api->UniformMatrix3x4fv = resolveGLSymbol(resolver, "glUniformMatrix3x4fv");
	api->UniformMatrix4x3fv = resolveGLSymbol(resolver, "glUniformMatrix4x3fv");
	api->UniformBlockBinding = resolveGLSymbol(resolver, "glUniformBlockBinding");
	api->UnmapBuffer = resolveGLSymbol(resolver, "glUnmapBuffer");
	api->UseProgram = resolveGLSymbol(resolver, "glUseProgram");
	api->ValidateProgram = resolveGLSymbol(resolver, "glValidateProgram");
	api->VertexAttrib1f = resolveGLSymbol(resolver, "glVertexAttrib1f");
	api->VertexAttrib1s = resolveGLSymbol(resolver, "glVertexAttrib1s");
	api->VertexAttrib1d = resolveGLSymbol(resolver, "glVertexAttrib1d");
	api->VertexAttribI1i = resolveGLSymbol(resolver, "glVertexAttribI1i");
	api->VertexAttribI1ui = resolveGLSymbol(resolver, "glVertexAttribI1ui");
	api->VertexAttrib2f = resolveGLSymbol(resolver, "glVertexAttrib2f");
	api->VertexAttrib2s = resolveGLSymbol(resolver, "glVertexAttrib2s");
	api->VertexAttrib2d = resolveGLSymbol(resolver, "glVertexAttrib2d");
	api->VertexAttribI2i = resolveGLSymbol(resolver, "glVertexAttribI2i");
	api->VertexAttribI2ui = resolveGLSymbol(resolver, "glVertexAttribI2ui");
	api->VertexAttrib3f = resolveGLSymbol(resolver, "glVertexAttrib3f");
	api->VertexAttrib3s = resolveGLSymbol(resolver, "glVertexAttrib3s");
	api->VertexAttrib3d = resolveGLSymbol(resolver, "glVertexAttrib3d");
	api->VertexAttribI3i = resolveGLSymbol(resolver, "glVertexAttribI3i");
	api->VertexAttribI3ui = resolveGLSymbol(resolver, "glVertexAttribI3ui");
	api->VertexAttrib4f = resolveGLSymbol(resolver, "glVertexAttrib4f");
	api->VertexAttrib4s = resolveGLSymbol(resolver, "glVertexAttrib4s");
	api->VertexAttrib4d = resolveGLSymbol(resolver, "glVertexAttrib4d");
	api->VertexAttrib4Nub = resolveGLSymbol(resolver, "glVertexAttrib4Nub");
	api->VertexAttribI4i = resolveGLSymbol(resolver, "glVertexAttribI4i");
	api->VertexAttribI4ui = resolveGLSymbol(resolver, "glVertexAttribI4ui");
	api->VertexAttrib1fv = resolveGLSymbol(resolver, "glVertexAttrib1fv");
	api->VertexAttrib1sv = resolveGLSymbol(resolver, "glVertexAttrib1sv");
	api->VertexAttrib1dv = resolveGLSymbol(resolver, "glVertexAttrib1dv");
	api->VertexAttribI1iv = resolveGLSymbol(resolver, "glVertexAttribI1iv");
	api->VertexAttribI1uiv = resolveGLSymbol(resolver, "glVertexAttribI1uiv");
	api->VertexAttrib2fv = resolveGLSymbol(resolver, "glVertexAttrib2fv");
	api->VertexAttrib2sv = resolveGLSymbol(resolver, "glVertexAttrib2sv");
	api->VertexAttrib2dv = resolveGLSymbol(resolver, "glVertexAttrib2dv");
	api->VertexAttribI2iv = resolveGLSymbol(resolver, "glVertexAttribI2iv");
	api->VertexAttribI2uiv = resolveGLSymbol(resolver, "glVertexAttribI2uiv");
	api->VertexAttrib3fv = resolveGLSymbol(resolver, "glVertexAttrib3fv");
	api->VertexAttrib3sv = resolveGLSymbol(resolver, "glVertexAttrib3sv");
	api->VertexAttrib3dv = resolveGLSymbol(resolver, "glVertexAttrib3dv");
	api->VertexAttribI3iv = resolveGLSymbol(resolver, "glVertexAttribI3iv");
	api->VertexAttribI3uiv = resolveGLSymbol(resolver, "glVertexAttribI3uiv");
	api->VertexAttrib4fv = resolveGLSymbol(resolver, "glVertexAttrib4fv");
	api->VertexAttrib4sv = resolveGLSymbol(resolver, "glVertexAttrib4sv");
	api->VertexAttrib4dv = resolveGLSymbol(resolver, "glVertexAttrib4dv");
	api->VertexAttrib4iv = resolveGLSymbol(resolver, "glVertexAttrib4iv");
	api->VertexAttrib4bv = resolveGLSymbol(resolver, "glVertexAttrib4bv");
	api->VertexAttrib4ubv = resolveGLSymbol(resolver, "glVertexAttrib4ubv");
	api->VertexAttrib4usv = resolveGLSymbol(resolver, "glVertexAttrib4usv");
	api->VertexAttrib4uiv = resolveGLSymbol(resolver, "glVertexAttrib4uiv");
	api->VertexAttrib4Nbv = resolveGLSymbol(resolver, "glVertexAttrib4Nbv");
	api->VertexAttrib4Nsv = resolveGLSymbol(resolver, "glVertexAttrib4Nsv");
	api->VertexAttrib4Niv = resolveGLSymbol(resolver, "glVertexAttrib4Niv");
	api->VertexAttrib4Nubv = resolveGLSymbol(resolver, "glVertexAttrib4Nubv");
	api->VertexAttrib4Nusv = resolveGLSymbol(resolver, "glVertexAttrib4Nusv");
	api->VertexAttrib4Nuiv = resolveGLSymbol(resolver, "glVertexAttrib4Nuiv");
	api->VertexAttribI4bv = resolveGLSymbol(resolver, "glVertexAttribI4bv");
	api->VertexAttribI4ubv = resolveGLSymbol(resolver, "glVertexAttribI4ubv");
	api->VertexAttribI4sv = resolveGLSymbol(resolver, "glVertexAttribI4sv");
	api->VertexAttribI4usv = resolveGLSymbol(resolver, "glVertexAttribI4usv");
	api->VertexAttribI4iv = resolveGLSymbol(resolver, "glVertexAttribI4iv");
	api->VertexAttribI4uiv = resolveGLSymbol(resolver, "glVertexAttribI4uiv");
	api->VertexAttribP1ui = resolveGLSymbol(resolver, "glVertexAttribP1ui");
	api->VertexAttribP2ui = resolveGLSymbol(resolver, "glVertexAttribP2ui");
	api->VertexAttribP3ui = resolveGLSymbol(resolver, "glVertexAttribP3ui");
	api->VertexAttribP4ui = resolveGLSymbol(resolver, "glVertexAttribP4ui");
	api->VertexAttribDivisor = resolveGLSymbol(resolver, "glVertexAttribDivisor");
	api->VertexAttribPointer = resolveGLSymbol(resolver, "glVertexAttribPointer");
	api->VertexAttribIPointer = resolveGLSymbol(resolver, "glVertexAttribIPointer");
	api->Viewport = resolveGLSymbol(resolver, "glViewport");
	api->WaitSync = resolveGLSymbol(resolver, "glWaitSync");

}