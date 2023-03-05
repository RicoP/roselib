local is_visual_studio = _ACTION:find("^vs") ~= nil 

workspace "roselib"
  characterset ("MBCS")
  configurations { "Debug", "Release" }
  location ".build/projects"
  targetdir ".build/bin/%{cfg.buildcfg}"
  kind "StaticLib"
  language "C++"
  warnings "Off"
  architecture "x64"
  cppdialect "C++20"
  startproject "tests"

  filter "configurations:Debug"
    defines { "DEBUG", "EA_DEBUG" }
    symbols "Full"
    optimize "Off"

  filter "configurations:Release"
    defines { "RELEASE", "NDEBUG" }
    symbols "Off"
    optimize "Size"

project "_root"
  kind "None"
  files { "**" }
  removefiles { ".git/**" }
  removefiles { ".build/**" }
  removefiles { "**.cpp", "**.h", "**.c" }

project "roselib"
  kind "ConsoleApp"
  language "C++"
  files { "include/**.h" }

project "tests"
  kind "ConsoleApp"
  language "C++"
  warnings "Extra"
  includedirs { "include" }
  includedirs { "../Catch2/single_include" }
  files { "test/**.cpp" }
  removefiles { "test/refptr.cpp" }

project "rosetests"
  kind "ConsoleApp"
  language "C++"
  warnings "Extra"
  includedirs { "include" }
  files { "test2/**.cpp" }
