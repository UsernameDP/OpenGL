project "glad"
    kind "StaticLib"
    language "C++"
    location "Generated"
    staticruntime "on"

    targetdir("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")

    files {
        "src/**.hpp",
        "src/**.cpp",
        "src/**.h",
        "src/**.c"
    }

    includedirs {
        "include"
    }

    filter {"configurations:Debug"}
        buildoptions "/MTd" --compiler option for debug
        runtime "Debug"
        symbols "on" --generate debug symbols

    filter {"configurations:Release"}
        buildoptions "/MT"
        runtime "Release"
        optimize "on"