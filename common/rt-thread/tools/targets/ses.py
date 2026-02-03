# SEGGER Embedded Studio Project Generator

import os
import sys
import re

import xml.etree.ElementTree as etree
from xml.etree.ElementTree import SubElement
from utils import _make_path_relative
from utils import xml_indent
from utils import ProjectInfo
import rtconfig

def SDKAddGroup(parent, name, files, project_path):
    # don't add an empty group
    if len(files) == 0:
        return

    group = SubElement(parent, 'folder', attrib={'Name': name})

    for f in files:
        fn = f.rfile()
        name = fn.name
        path = os.path.dirname(fn.abspath)

        basename = os.path.basename(path)
        path = _make_path_relative(project_path, path)
        elm_attr_name = os.path.join(path, name)

        file = SubElement(group, 'file', attrib={'file_name': elm_attr_name})

    return group

def SESProject(env) :
    target = 'project.emProject'
    tree = etree.parse('template.emProject')
    # print(etree.dump(tree.getroot()))
    # etree.dump(tree.getroot())

    project = ProjectInfo(env)
    # print(project)
    # return

    project_path = os.path.abspath(env['BSP_ROOT'])
    script = env['project']

    root = tree.getroot()
    out = open(target, 'w')
    out.write('<!DOCTYPE CrossStudio_Project_File>\n')

    CPPPATH = []
    CPPDEFINES = []
    LINKFLAGS = ''
    CFLAGS = ''
    LIBS = []
    LIBPATH = []

    project_node = tree.find('project')

    for group in script:
        # print(group)

        group_tree = SDKAddGroup(project_node, group['name'], group['src'], project_path)

        # get each group's cc flags
        if 'CFLAGS' in group and group['CFLAGS']:
            if CFLAGS:
                CFLAGS += ' ' + group['CFLAGS']
            else:
                CFLAGS += group['CFLAGS']

        # get each group's link flags
        if 'LINKFLAGS' in group and group['LINKFLAGS']:
            if LINKFLAGS:
                LINKFLAGS += ' ' + group['LINKFLAGS']
            else:
                LINKFLAGS += group['LINKFLAGS']

        # get each group's libraries
        if 'LIBS' in group and group['LIBS']:
            for lib in group['LIBS']:
                if lib not in LIBS:
                    LIBS.append(lib)
                    print(f"[SES] Found library: {lib}")

        # get each group's library paths
        if 'LIBPATH' in group and group['LIBPATH']:
            for path in group['LIBPATH']:
                if path not in LIBPATH:
                    LIBPATH.append(path)
                    print(f"[SES] Found library path: {path}")

    # Parse the CDEFINES from the rtconfig.py
    CDEFINES = re.findall(r'-D(\w+(?:=[^\s]*)?)', rtconfig.CFLAGS)

    # write include path, definitions and link flags
    path = ';'.join([_make_path_relative(project_path, os.path.normpath(i)) for i in project['CPPPATH']])
    path = path.replace('\\', '/')
    defines = ';'.join(set(project['CPPDEFINES']))
    for cdefine in CDEFINES:
        defines = defines + ";" + cdefine

    node = tree.findall('project/configuration')
    for item in node:
        if item.get('c_preprocessor_definitions'):
            item.set('c_preprocessor_definitions', defines)

        if item.get('c_user_include_directories'):
            item.set('c_user_include_directories', path)

    # Add library files to project
    print(f"[SES] LIBS={LIBS}, LIBPATH={LIBPATH}")
    if LIBS and LIBPATH:
        print(f"[SES] Creating Libraries folder with {len(LIBS)} libraries")
        lib_folder = SubElement(project_node, 'folder', attrib={'Name': 'Libraries'})

        for libpath in LIBPATH:
            for lib in LIBS:
                # Construct full library filename (add lib prefix and .a suffix)
                lib_name = f'lib{lib}.a' if not lib.startswith('lib') else f'{lib}.a'
                lib_fullpath = os.path.join(libpath, lib_name)

                # Make path relative to project
                lib_relative = _make_path_relative(project_path, os.path.normpath(lib_fullpath))
                lib_relative = lib_relative.replace('\\', '/')

                # Add to project (SES will link it automatically)
                SubElement(lib_folder, 'file', attrib={'file_name': lib_relative})
                print(f"[SES] Added library: {lib_relative}")

                # Note: SES will show warning if file doesn't exist, but won't fail

    xml_indent(root)
    if sys.version_info[0] == 2:
        proj_content = str(etree.tostring(root, encoding='utf-8'))
    else:
        proj_content = str(etree.tostring(root, encoding='utf-8'), encoding='utf-8')
    out.write(proj_content)
    out.close()
    return
