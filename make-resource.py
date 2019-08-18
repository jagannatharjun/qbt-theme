import subprocess
import glob
import argparse
import os.path
import sys

parser = argparse.ArgumentParser(description='helper to create qbtthemes')
parser.add_argument('-o', '--output', type=str, help='output qbtheme file', default='style.qbtheme')
parser.add_argument('-s', '--style', type=str, help='stylesheet', required=True)
parser.add_argument('files', metavar='file', type=str,
                    nargs='*', help='files for icons, supports glob patterns')
args = parser.parse_args()


if len(args.output) > 0 and not args.output.endswith('.qbtheme'):
    args.output += '.qbtheme'
if not len(args.output) or os.path.exists(args.output):
    if input('"{}" already exists, Do you want to overwrite?(y,n)'.format(args.output)) == 'n':
        exit()

ResourceFiles = list()
for arg in args.files:
    for p in glob.glob(arg):
        ResourceFiles.append('\t\t<file>' + p + '</file>\n')

ResourceFiles.append('\t\t<file alias="stylesheet.qss">' + args.style + '</file>\n')

with open('resources.qrc', 'w') as rcc:
    rcc.write('<!DOCTYPE RCC><RCC version="1.0">\n')
    rcc.write('\t<qresource>\n')
    rcc.writelines(ResourceFiles)
    rcc.write('\t</qresource>\n')
    rcc.write('</RCC>')

subprocess.call(['rcc', '-binary', '-o', args.output, 'resources.qrc'])
