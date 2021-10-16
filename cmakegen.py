import argparse
import os
import platform
import sys
import subprocess

from abc import ABC, abstractmethod

def run_cmd(command):
    subprocess.run(command, shell=True)

def change_working_dir_to(path):
    os.chdir(path)

class IBuilder(ABC):
    '''
        Abstract class to generate a project for some IDEs.
    '''
    def __init__(self, generator, build_type, build_tests, build_samples, enable_coverage):
        self.build_dir = 'build'
        self.generator = generator
        self.build_type = build_type
        self.build_tests = build_tests
        self.build_samples = build_samples
        self.enable_coverage = enable_coverage

    @abstractmethod
    def create_build_dir(self):
        pass

    @abstractmethod
    def generate_project(self):
        pass

    def get_cmake_generate_command(self):
        return 'cmake -G "{}" .. -DCMAKE_BUILD_TYPE={} -DBUILD_TESTS={} -DBUILD_SAMPLES={} -DENABLE_COVERAGE={}'.format(
            self.generator, self.build_type, self.build_tests, self.build_samples, self.enable_coverage)

class XcodeBuilder(IBuilder):
    '''
        Class to generate a project for Xcode IDE.
    '''
    def __init__(self, build_type, build_tests, build_samples, enable_coverage):
        super().__init__('Xcode', build_type, build_tests, build_samples, enable_coverage)

    def create_build_dir(self):
        run_cmd('mkdir -p {}'.format(self.build_dir))
        change_working_dir_to(self.build_dir)

    def generate_project(self):
        run_cmd(super().get_cmake_generate_command())

class VisualStudioBuilder(IBuilder):
    '''
        Class to generate a project for Visual Studio IDE.
    '''
    def __init__(self, build_type, build_tests, build_samples, enable_coverage):
        super().__init__('Visual Studio 16 2019', build_type, build_tests, build_samples, enable_coverage)
        self.platform = 'x64'

    def create_build_dir(self):
        run_cmd('if not exist {0} mkdir {0} && pushd {0}'.format(self.build_dir))
        change_working_dir_to(self.build_dir)

    def generate_project(self):
        run_cmd('{} -A {}'.format(super().get_cmake_generate_command(), self.platform))

class QtBuilder(IBuilder):
    '''
        Class to generate a project for QtCreator IDE.
    '''
    def __init__(self, build_type, build_tests, build_samples, enable_coverage):
        super().__init__('CodeBlocks - Unix Makefiles', build_type, build_tests, build_samples, enable_coverage)

    def create_build_dir(self):
        run_cmd('mkdir -p {}'.format(self.build_dir))
        change_working_dir_to(self.build_dir)

    def generate_project(self):
        run_cmd(super().get_cmake_generate_command())

def create_builder(build_type, build_tests, build_samples, enable_coverage):
    '''
        Factory method that makes a project builder for the specific platform.
    '''
    platform_name = platform.system()
    if platform_name == 'Darwin':
        return XcodeBuilder(build_type, build_tests, build_samples, enable_coverage)
    elif platform_name == 'Windows':
        return VisualStudioBuilder(build_type, build_tests, build_samples, enable_coverage)
    elif platform_name == 'Linux':
        return QtBuilder(build_type, build_tests, build_samples, enable_coverage)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--build-type', '-b', dest='build_type', default='Debug')
    parser.add_argument('--build-tests', '-t', action='store_false')
    parser.add_argument('--build-samples', '-s', action='store_false')
    parser.add_argument('--enable-coverage', '-c', action='store_false')
    args = parser.parse_args()

    builder = create_builder(args.build_type, args.build_tests, args.build_samples, args.enable_coverage)
    builder.create_build_dir()
    builder.generate_project()

if __name__ == '__main__':
    sys.exit(main())
