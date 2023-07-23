project "OpenGL-Examples"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    -- location "Generated"
    staticruntime "on"

    targetdir("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")


    files {
        "src/**.hpp",
        "src/**.cpp"
    }

    includedirs {
        "../OpenGL-Core/src",
        "../OpenGL-Core/vendor/Glad/include",
        "../OpenGL-Core/vendor/GLFW/include",
        "../OpenGL-Core/vendor/glm/include",
        "../OpenGL-Core/vendor/imgui/include"
    }

    links {
        "OpenGL-Core"
    }

    filter {"configurations:Debug"}
        buildoptions "/MDd" --compiler option for debug
        runtime "Debug"
        symbols "on" --generate debug symbols
        warnings "Extra"
        linkoptions { "/NODEFAULTLIB:LIBCMTD", "/NODEFAULTLIB:library" }

    filter {"configurations:Release"}
        buildoptions "/MT"
        runtime "Release"
        warnings "Extra"
        optimize "on"