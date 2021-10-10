import argparse
import os
import platform
import sys
import subprocess

BUILD_DIR = 'build'

def run_cmd(command):
    subprocess.run(command, shell=True)

def change_working_dir_to(path):
    os.chdir(path)

class VisualCompilerBuilder:

    def __init__(self, build_type):
        self.generator = 'Visual Studio 16 2019'
        self.platform = 'x64'
        self.build_type = build_type

    def create_build_dir(self):
        run_cmd('if not exist {0} mkdir {0} && pushd {0}'.format(BUILD_DIR))
        change_working_dir_to(BUILD_DIR)

    def generate_project(self):
        run_cmd('cmake -G {} -A {} -DCMAKE_BUILD_TYPE={} ..'.format(self.generator, self.platform, self.build_type))

class XcodeBuilder:

    def __init__(self, build_type):
        self.generator = 'Xcode'
        self.build_type = build_type

    def create_build_dir(self):
        run_cmd('mkdir -p {}'.format(BUILD_DIR))
        change_working_dir_to(BUILD_DIR)

    def generate_project(self):
        run_cmd('cmake -G {} -DCMAKE_BUILD_TYPE={} ..'.format(self.generator, self.build_type))

def create_builder(build_type):
    platform_name = platform.system()
    if platform_name == 'Windows':
        return VisualCompilerBuilder(build_type)
    elif platform_name == 'Darwin':
        return XcodeBuilder(build_type)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--build-type', dest='build_type', default='Debug', required=False)
    args = parser.parse_args()

    builder = create_builder(args.build_type)
    builder.create_build_dir()
    builder.generate_project()

if __name__ == '__main__':
    sys.exit(main())
