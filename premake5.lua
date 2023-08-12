--OpenGL-Core
workspace "OpenGL-Core"
    architecture "x64"
    startproject "OpenGL-Core"

    configurations {
        "Debug",
        "Release"
    }

    filter {"configurations:Release"}
        defines {"VERSION_RELEASE"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glad"] = "vendor/glad/include"
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["glm"] = "vendor/glm/include"
IncludeDir["imgui"] = "vendor/imgui/include"
IncludeDir["stb"] = "vendor/stb/include"

group "Dependencies"
    include "OpenGL-Core/vendor/glad"
    include "OpenGL-Core/vendor/GLFW"
    include "OpenGL-Core/vendor/imgui"
group ""

include "OpenGL-Core"
-------------------------------------------------------------------------------

--OpenGL-Examples
workspace "OpenGL-Examples"
    architecture "x64"
    startproject "OpenGL-Examples"
    
    configurations {
        "Debug",
        "Release"
    }

    --Note that all relative paths are relative to the parent of the CWD (current working directory)
    postbuildcommands {
        "{COPYDIR} assets bin/"..outputdir.."/OpenGL-Examples/assets"
    }

    filter {"configurations:Release"}
        defines {"VERSION_RELEASE"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

IncludeDir = {}
IncludeDir["glad"] = "vendor/glad/include"
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["glm"] = "vendor/glm/include"
IncludeDir["imgui"] = "vendor/imgui/include"
IncludeDir["stb"] = "vendor/stb/include"

group "Dependencies"
    includeexternal "OpenGL-Core/vendor/glad"
    includeexternal "OpenGL-Core/vendor/GLFW"
    includeexternal "OpenGL-Core/vendor/imgui"
group ""

includeexternal "OpenGL-Core"
include "OpenGL-Examples"
-------------------------------------------------------------------------------

--Clean Command
function cleanProject(projectDir)
    print("Cleaning Project : " .. projectDir)
    print("Removing binaries")
    os.rmdir(projectDir .. "/bin")

    print("Removing intermediate binaries")
    os.rmdir(projectDir .. "/bin-int")

    print("Removing project files")
    os.rmdir(projectDir .. "/.vs")
    os.rmdir(projectDir .. "/Generated")
    os.remove("**.vcxproj")
    os.remove("**.vcxproj.filters")
    os.remove("**.vcxproj.user")
    os.rmdir("Generated")

    print("Removing misc. files")
    os.remove(projectDir.."/imgui.ini");

end

newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        cleanProject("OpenGL-Core")
        cleanProject("OpenGL-Examples")
        cleanProject("OpenGL-Core/vendor/glad")
        cleanProject("OpenGL-Core/vendor/GLFW")
        cleanProject("OpenGL-Core/vendor/imgui")
        cleanProject("OpenGL-Core/vendor/stb")

        print("Removing Solution Files")
        os.remove("**.sln")
    
        print("Deleting .vs directory")
        os.rmdir(".vs")
    
        print("Done")
    end
}
-------------------------------------------------------------------------------
