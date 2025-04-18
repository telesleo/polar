workspace "Polar"
  configurations { "Debug", "Release" }
  platforms { "x64" }

project "Polar"
  kind "SharedLib"
  language "C++"
  cppdialect "C++17"
  targetdir ("./bin/%{cfg.buildcfg}")
  includedirs {
    "./vendor/SDL/include/",
    "./vendor/glad/include/",
    "./vendor/stb_image/include/",
    "./vendor/glm/include/",
    "./vendor/entt/include/"
  }
  libdirs { "./vendor/SDL/lib/" }
  links { "SDL3" }

  files { "**.h", "**.hpp", "**.c", "**.cpp" }

  postbuildcommands {
   "{COPY} \"./vendor/SDL/lib/SDL3.dll\" \"%{cfg.targetdir}\""
  }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
