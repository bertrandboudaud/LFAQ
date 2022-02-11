#  Copyright(C) 2015-2018  all rights reserved
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

parser = argparse.ArgumentParser(description='Optional app description')

# Required arguments
parser.add_argument('Input_directory_path', type=pathlib.Path,
                    help='Input data directory')
parser.add_argument('Fastapath', type=pathlib.Path,
                    help='fasta file path')
parser.add_argument('ResultPath', type=pathlib.Path,
                    help='Result directory')

# optional arguments
parser.add_argument('--IdentificationFileType', type=ascii,
                    choices=['maxquant', 'TODO1', 'TODO2'],
                    help='')
parser.add_argument('--IdentifierParsingRule', type=ascii,
                    default=">(.*?)\\s",
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
                    choices=['BART', 'TODO1', 'TODO2'],
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
