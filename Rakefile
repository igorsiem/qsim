# Rakefile for basic Dev tasks in qSim
#
# Copyright Igor Siemienowicz 2018
# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt)

# TODO Windows support

directory "build"

desc "clean all build artefacts"
task :clean do
    FileUtils.rm_rf "build"
end

desc "run cmake to produce platform-specific build files"
task :cmake => "build" do
    Dir.chdir "build"
    sh "cmake ../src"
    Dir.chdir ".."
end

desc "build binaries"
task :bin => :cmake do    
    Dir.chdir "build"
    sh "make -j8"
    Dir.chdir ".."
end

desc "run test suite"
task :test => :bin do
    sh "build/test/test-qsim"
end

directory "build/docs"

desc "build doxygen docs"
task :docs => "build/docs" do
    sh "doxygen"
end

namespace :run do
    
    desc "run the qSim CLI"
    task :cli => :bin do
        sh "build/cli/qsim-cli"
    end
    
end # run namespace
