#  Copyright(C) 2015-2022  all rights reserved
#  This program is a free software; you can redistribute it and / or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
#  GNU General Public License for more details.
#
#  A copy of the GNU General Public License is available at
#  http://www.gnu.org/Licenses/

import argparse
import pathlib
import os
import datetime
import subprocess

parser = argparse.ArgumentParser(description='LFAQ, a novel algorithm for label-free absolute protein quantification, which can correct the biased MS intensities using the predicted peptide quantitative factors for all identified peptides.')

# Required arguments
parser.add_argument('Input_directory_path', type=pathlib.Path,
                    help='Input data directory')
parser.add_argument('Fastapath', type=pathlib.Path,
                    help='fasta file path')
parser.add_argument('ResultPath', type=pathlib.Path,
                    help='Result directory')

# optional arguments
parser.add_argument('--IdentificationFileType', type=ascii,
                    choices=["maxquant", "TODO1", "TODO2"],
                    default="maxquant",
                    help='')
parser.add_argument('--IdentifierParsingRule', type=ascii,
                    default='>(.*?)\s',
                    help='')
parser.add_argument('--IfExistDecoyProteins', action='store_false',
                    help='')
parser.add_argument('--PrefixOfDecoyProtein', type=ascii,
                    default="REV_",
                    help='')
parser.add_argument('--IfExistContaminantProteins', action='store_false',
                    help='')
parser.add_argument('--PrefixOfContaminantProtein', type=ascii,
                    default="CON_",
                    help='')
parser.add_argument('--IfCalculateiBAQ', action='store_false',
                    help='')
parser.add_argument('--IfCalculateTop3', action='store_false',
                    help='')
parser.add_argument('--RegressionMethod', type=ascii,
                    choices=["BART", "TODO1", "TODO2"],
                    default="BART",
                    help='')
parser.add_argument('--alpha', type=float,
                    default=0.85,
                    help='')
parser.add_argument('--beta', type=float,
                    default=1.6,
                    help='')
parser.add_argument('--k', type=float,
                    default=2,
                    help='')
parser.add_argument('--Number_of_trees', type=int,
                    default=200,
                    help='')
parser.add_argument('--MaxMissedCleavage', type=int,
                    default=0,
                    help='')
parser.add_argument('--PepShortestLen', type=int,
                    default=6,
                    help='')
parser.add_argument('--PepLongestLen', type=int,
                    default=30,
                    help='')
parser.add_argument('--Enzyme', type=ascii,
                    default="trypsin",
                    help='')
parser.add_argument('--IfCotainStandardProtein', action='store_false',
                    help='')
parser.add_argument('--IdentifierOfStandardProtein', type=ascii,
                    default="ups",
                    help='')
parser.add_argument('StandardProteinsFilePath', type=pathlib.Path,
                    help='')

args = parser.parse_args()

# summary message
print("Running LFAQ with the following parameters:")

# create parameter file
parameter_file_name =  "parameters_" + str(datetime.datetime.now()).replace(" ","_").replace(":","").replace("-","").replace(".","_") + ".params"
parameter_full_path = os.path.join(args.ResultPath, parameter_file_name)
parameter_file = open(parameter_full_path, 'w')
for arg in vars(args):
    parameter_name = arg.replace("_", " ")
    value = getattr(args,arg)
    if isinstance(value, bool):
        if value:
            value="true"
        else:
            value="false"
    if isinstance(value, str):
        value = value.replace("'","")
    if arg == "IdentifierParsingRule":
        value = value.replace("\\\\","\\")
    parameter_file.write("{0}=\"{1}\"\n".format(parameter_name,value))
    print("{0}=\"{1}\"".format(parameter_name,value))
parameter_file.close()
print("Parameters file created at {0}".format(parameter_full_path))

# execute workflow
executables_path = "C:\\Users\\bertr\\LFAQ\\ExecutableFiles\\x64\\"
os.chdir(executables_path)

# launch load.exe
Load_exe_path = os.path.join(executables_path, "Load.exe")
Load_exe_args = [Load_exe_path, parameter_full_path]
subprocess.check_call(Load_exe_args)

# launch ProteinAbsoluteQuan.exe
ProteinAbsoluteQuan_exe_path = os.path.join(executables_path, "ProteinAbsoluteQuan.exe")
ProteinAbsoluteQuan_exe_args = [ProteinAbsoluteQuan_exe_path, parameter_full_path]
subprocess.check_call(ProteinAbsoluteQuan_exe_args)
