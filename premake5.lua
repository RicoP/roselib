local is_visual_studio = _ACTION:find("^vs") ~= nil 

workspace "ROS"
  characterset ("MBCS")
  configurations { "Debug", "Release" }
  startproject "test"
  location ".build/projects"
  targetdir ".build/bin/%{cfg.buildcfg}"
  debugdir "bin"
  kind "StaticLib"
  language "C++"
  warnings "Off"
  architecture "x64"
  cppdialect "C++17"

  if is_visual_studio then
    linkoptions {
      "/ignore:4006", -- F already defined in X.lib; second definition ignored
    }
  end

  filter "configurations:Debug"
    defines { "DEBUG", "EA_DEBUG" }
    symbols "Full"
    optimize "Off"
    targetsuffix "-d"

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

project "ros"
  kind "None"
  files { "include/**.h" }

project "test.range"
  kind "ConsoleApp"
  language "C++"
  warnings "Extra"
  includedirs { "include" }
  files { "test/range.cpp" }

project "test.refptr"
  kind "ConsoleApp"
  language "C++"
  warnings "Extra"
  includedirs { "include" }
  files { "test/refptr.cpp" }
