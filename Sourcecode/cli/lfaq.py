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
                    help='The file path of proteins database (*.fasta)')
parser.add_argument('ResultPath', type=pathlib.Path,
                    help='Result directory')
parser.add_argument('ExecutablesPath', type=pathlib.Path,
                    help='LFAQ Executables path')

# optional arguments
parser.add_argument('--IdentificationFileType', type=ascii,
                    choices=["maxquant", "PeakView", "mzQuantML"],
                    default="maxquant",
                    help='Software used to identify the proteins')
parser.add_argument('--IdentifierParsingRule', type=ascii,
                    default='>(.*?)\s',
                    help='The regular expression used to extract protein identifiers from the fasta file.')
parser.add_argument('--IfExistDecoyProteins', action='store_false',
                    help='Set to true if input protein list contains decoy proteins')
parser.add_argument('--PrefixOfDecoyProtein', type=ascii,
                    default="REV_",
                    help='Prefix of decoy proteins')
parser.add_argument('--IfExistContaminantProteins', action='store_false',
                    help='Set to true if input protein list contains contaminant proteins')
parser.add_argument('--PrefixOfContaminantProtein', type=ascii,
                    default="CON_",
                    help='Prefix of contaminant protein')
parser.add_argument('--IfCalculateiBAQ', action='store_false',
                    help='If MaxQuant result is used as input, iBAQ values come from MaxQuant result. Otherwise, iBAQ is calculated by LFAQ.')
parser.add_argument('--IfCalculateTop3', action='store_false',
                    help='Calculate Top 3')
parser.add_argument('--RegressionMethod', type=ascii,
                    choices=["BART", "stepwise"],
                    default="BART",
                    help='Regression method for Q-factor learning.')
parser.add_argument('--alpha', type=float,
                    default=0.85,
                    help='The base parameter for the tree prior, ranging from 0 to 1.')
parser.add_argument('--beta', type=float,
                    default=1.6,
                    help='The power parameter for the tree prior, ranging from 0 to positive infinite.')
parser.add_argument('--k', type=int,
                    default=2,
                    help='The number of standard deviations of the dependent variables in the training set.')
parser.add_argument('--Number_of_trees', type=int,
                    default=200,
                    help='The number of trees to train in the BART.')
parser.add_argument('--MaxMissedCleavage', type=int,
                    default=0,
                    help='The maximum number of missed cleavages of a peptide in the theoretical digestion.')
parser.add_argument('--PepShortestLen', type=int,
                    default=6,
                    help='The allowed shortest length of a peptide in the theoretical digestion.')
parser.add_argument('--PepLongestLen', type=int,
                    default=30,
                    help='The allowed longest length of a peptide in the theoretical digestion.')
parser.add_argument('--Enzyme', type=ascii,
                    default="trypsin",
                    help='The enzyme used for theoretical digestion.')
parser.add_argument('--IfCotainStandardProtein', action='store_false',
                    help='Does the sample contain standard proteins')
parser.add_argument('--IdentifierOfStandardProtein', type=ascii,
                    default="ups",
                    help='If the sample contains proteins, identifier of standard proteins')
parser.add_argument('--StandardProteinsFilePath', type=pathlib.Path,
                    default="",
                    help='Standard proteins file path.')
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
executables_path = args.ExecutablesPath
os.chdir(executables_path)

# launch load.exe
Load_exe_path = os.path.join(executables_path, "Load.exe")
Load_exe_args = [Load_exe_path, parameter_full_path]
subprocess.check_call(Load_exe_args)

# launch ProteinAbsoluteQuan.exe
ProteinAbsoluteQuan_exe_path = os.path.join(executables_path, "ProteinAbsoluteQuan.exe")
ProteinAbsoluteQuan_exe_args = [ProteinAbsoluteQuan_exe_path, parameter_full_path]
subprocess.check_call(ProteinAbsoluteQuan_exe_args)
