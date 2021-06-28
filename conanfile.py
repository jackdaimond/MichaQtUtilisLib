from conans import ConanFile, CMake, tools


class MichaQtUtilisLibConan(ConanFile):
    name = "MichaQtUtilisLib"
    version = "0.2"
    license = "MIT - https://github.com/jackdaimond/MichaQtUtilisLib/blob/master/LICENSE"
    author = "Michael Kloske"
    url = "https://github.com/jackdaimond/MichaQtUtilisLib.git"
    description = "Contains several functionalities often used in other Qt applications."
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "qmake"

    scm = {
            "type": "git",
            "subfolder": "",
            "url": "https://github.com/jackdaimond/MichaQtUtilisLib.git",
            "revision": "auto"
        }

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    #def source(self):
    #    self.run("git clone https://github.com/conan-io/hello.git")
    #    # This small hack might be useful to guarantee proper /MT /MD linkage
    #    # in MSVC if the packaged project doesn't have variables to set it
    #    # properly

    def build(self):
        self.run("qmake MichaQtUtilisLib.pro CONFIG+=release")
        self.run("nmake")
        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h*", dst="include/MichaQtUtilisLib", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["MichaQtUtilisLib"]
