import os, sys
from os.path import dirname, abspath, splitext,basename
from sultan.api import Sultan

class ContentHunter:
    """
    This class is designed to remove all the "module/module_name" in
    the "#include" line of the header and source files automatically
    usage:

        python content_hunter.py [package1_name] [package2_name]

        [package1_name] can be "common",  "planning", ... and so on.
    """
    def __init__(self):
        self.string_target = "modules\/" # back_bash + / for \
        self.string_replacement = ""
        self.tools_dir = os.getcwd()
        self.scripts_dir = dirname(self.tools_dir)
        self.repo_dir = dirname(self.scripts_dir)
        self.cmd_arguments = sys.argv
        self.cmd_arguments.pop(0) # remove the python script file name
        self.exclude_dir = "cmake-build"
        self.target_file_type = [".cc", ".h"]


    def substitute(self):
        # process the packages one by one
        if len(self.cmd_arguments) >= 1:
            for package_name in self.cmd_arguments:
                self.substituteSinglePackage(package_name)
        else:
            print ("Please provide at least one name of packages to process")

    def getFileExtention(self, file_name):
        return splitext(file_name)[1]

    def substituteSinglePackage(self, pkg_string_name):
        # define the abs path according the package name
        search_dir = self.repo_dir + "/src/" + pkg_string_name
        print ("Processing packge:", search_dir)
        self.searchDir(search_dir, pkg_string_name)

    def searchDir(self, search_dir, pkg_string_name):
        # in a single package root folder, for example ,
        # pkg string name = common
        # pwd/port_apollo/common
        for dirName, subdirList, fileList in os.walk(search_dir):
            if dirName.find(self.exclude_dir) == -1: # cmake-build
                print('Found directory: %s' % basename(dirName))
                for fname in fileList:
                    if self.getFileExtention(fname) in self.target_file_type:
                        # get the absolute path of files
                        abs_file =  dirName + "/" + fname
                        print('\t%s' % abs_file)
                        self.replace_string(abs_file, pkg_string_name)

    def replace_string(self, fname_abs, pkg_string_name):
        # python does not have a very good string-inplace-substitute solution
        # call the `sed` command of the bash to do the work
        # sed -i "s/target_string/final_string/g" file.txt
        # if target_string is a path, use \/ to represent /
        # sed -i "s/include\/header/headers/g" file.txt    # replace include/header with headers
        # call bash commands Pythonically using Sultan
        # https://sultan.readthedocs.io/en/latest/index.html
        # Be careful with bash commands!!!
        complete_target = self.string_target + pkg_string_name + "\/"  # i.e. modules\/common\/
        bash_string_cmd = "\"s/" + complete_target + "/" + self.string_replacement + "/g\""
        with Sultan.load() as s:
            s.sed('-i', bash_string_cmd, fname_abs).run()




hunter = ContentHunter()
hunter.substitute()
