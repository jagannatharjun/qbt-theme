import subprocess
import glob
import argparse
import os.path
import sys
import fnmatch
import re

def allFiles(glob):
    [dir, pattern] = os.path.split(glob)
    l = list()
    for root, subdir, files in os.walk(dir):
        l.extend([os.path.join(root, x) for x in files if fnmatch.fnmatch(x, pattern)])
    return l

parser = argparse.ArgumentParser(description='helper to create qbtthemes')
parser.add_argument('-output', type=str, help='output qbtheme file', default='style.qbtheme')
parser.add_argument('-style', type=str, help='stylesheet', required=True)
parser.add_argument('-base-dir', type=str, dest='baseDir', default='.')
parser.add_argument('-icons-dir', type=str, dest='iconsDir', default='', help='directory which contains custom icons')
parser.add_argument('-dir-prefix', type=str, default='', dest='dirPrefix', help='prefix added to all files')
parser.add_argument('-config', type=str, dest='config', default=None, help='file used as config.json')
parser.add_argument('-find-files', action='store_true', dest='findFiles', help='find files included in qss and only include those')
parser.add_argument('files', metavar='files', type=str,
                    nargs='*', default=['*'], help='files to include in resources from baseDir, supports glob patterns')

args = parser.parse_args()

if not args.output.endswith('.qbtheme'):
    args.output += '.qbtheme'

if os.path.exists(args.output):
    print("WARNING! %s already exists. overwriting" % (args.output))
    

files = allFiles(os.path.join(args.baseDir, '*'))
if args.findFiles:
    print('finding files')
    args.files = []
    stylesheet = open(os.path.join(args.baseDir, args.style)).read()
    for f in re.findall(':\/uitheme\/(.*)\)', stylesheet):
        args.files.append(f)
    
config_file = None
if args.config:
    if os.path.exists(args.config):
        config_file = args.config
    elif os.path.exists(os.path.join(args.baseDir, args.config)):
        config_file = os.path.join(args.baseDir, args.config)

ResourceFiles = list()
for f in files:
    alias = os.path.relpath(f, args.baseDir)
    for i in args.files:
        if fnmatch.fnmatch(alias, i):
            ResourceFiles.append((alias, f))
            print('adding ' + f)
            break
            
IconFiles = list() if not args.iconsDir else [f for f in glob.glob(os.path.join(args.iconsDir, '*'))]
print(IconFiles)

with open('resources.qrc', 'w') as rcc:
    rcc.write('<!DOCTYPE RCC><RCC version="1.0">\n')
    rcc.write('\t<qresource %s>\n' % ('prefix=\'' + args.dirPrefix + '\'' if args.dirPrefix else ''))
    rcc.writelines(['\t\t<file alias=\'%s\'>%s</file>\n' % x for x in ResourceFiles])
    rcc.write('\t</qresource>\n')
    rcc.write('\t<qresource>\n')
    rcc.write('\t\t<file alias=\'stylesheet.qss\'>%s</file>\n' % (os.path.join(args.baseDir, args.style)))
    rcc.writelines(['\t\t<file alias=\'icons\\%s\'>%s</file>\n' % (os.path.split(x)[1], x) for x in IconFiles])
    if config_file:
        rcc.write('\t\t<file alias=\'config.json\'>%s</file>\n' % (config_file))
    rcc.write('\t</qresource>\n')
    rcc.write('</RCC>')


cmd = [os.path.join(os.path.dirname(os.path.realpath(__file__)), 'tools/rcc'), '-binary', '-o', args.output, 'resources.qrc']
print(' '.join(cmd))

if not subprocess.call(cmd):
    os.remove('resources.qrc')