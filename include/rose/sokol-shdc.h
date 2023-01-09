#pragma once

//Pseudo sokol structs so we can load shaders compiled with sokol-shdc
#define SOKOL_GFX_INCLUDED
enum ShaderUniformType { SG_UNIFORMTYPE_NONE = 0, SG_UNIFORMTYPE_FLOAT4 };
enum ShaderImageType { SG_IMAGETYPE_NONE = 0, SG_IMAGETYPE_2D };
enum ShaderSamplerType { SG_SAMPLERTYPE_NONE = 0, SG_SAMPLERTYPE_FLOAT };
enum sg_backend { SG_BACKEND_NONE = 0, SG_BACKEND_GLCORE33, SG_BACKEND_GLES2 };
enum sg_layout { SG_UNIFORMLAYOUT_NONE = 0, SG_UNIFORMLAYOUT_STD140 };

struct ShaderAttribute {
  const char *name = "";
};

struct ShaderUniform {
  const char *name = "";
  ShaderUniformType type = SG_UNIFORMTYPE_NONE;
  int array_count = 0;
  int location = -1;  // Set after loading.
};

struct ShaderImages {
  const char *name = "";
  ShaderImageType type = SG_IMAGETYPE_NONE;
  ShaderSamplerType sampler_type = SG_SAMPLERTYPE_NONE;
};

struct ShaderUniformBlock {
  int size = 0;
  int layout = 0;
  ShaderUniform uniforms[8];
};

struct ShaderSource {
  const char *source = "";
  const char *entry = "";
  ShaderUniformBlock uniform_blocks[8];
  ShaderImages images[8];
};

struct ShaderDescription {
  ShaderAttribute attrs[8];
  ShaderSource vs;
  ShaderSource fs;
  const char *label = "";
};

typedef ShaderDescription sg_shader_desc;

