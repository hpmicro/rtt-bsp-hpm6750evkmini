########################################################################################################################
# Copyright 2025 HPMicro
#
# SPDX-License-Identifier: BSD-3-Clause
#
########################################################################################################################
"""
BSP Utilities for RT-Thread BSP

This script provides command-line utilities for managing HPMicro RT-Thread BSP projects:
- List available example projects
- Export specific projects to external directories
- Display version information

Author: HPMicro
Version: 0.3.0
"""

import os
import sys
import argparse
import shutil

# Version information for the utility
util_version = '0.3.0'


def show_version():
    """Display the current version of the BSP utility."""
    version_info = f"""BSP Utilities v{util_version}
HPMicro RT-Thread Board Support Package Manager
Copyright 2025 HPMicro
SPDX-License-Identifier: BSD-3-Clause

This utility manages RT-Thread BSP projects for HPMicro development boards.
"""
    print(version_info)


def show_usage():
    """
    Display comprehensive usage information and examples for the BSP utility.

    Shows all available commands, their syntax, and practical usage examples
    to help users understand how to use the tool effectively.
    """
    usage_str = """BSP Utilities - HPMicro RT-Thread Board Support Package Manager
================================================================

DESCRIPTION:
    This utility helps manage RT-Thread BSP projects for HPMicro development boards.
    It provides tools to list available example projects and export them to external
    directories for development and customization.

USAGE:
    bsp_utils.py [COMMAND] [OPTIONS]

COMMANDS:
    -v, --version           Display version information
    -l, --list             List all supported example projects in this BSP
    -e, --export_proj      Export project(s) from this BSP to specified destination

OPTIONS FOR EXPORT:
    -p, --project_name     Project name to export (use 'all' for all projects)
    -o, --output_dir       Output directory for exported project(s)

EXAMPLES:

    1. Show version information:
       bsp_utils.py -v
       bsp_utils.py --version

    2. List all available example projects:
       bsp_utils.py -l
       bsp_utils.py --list

    3. Export a specific project:
       bsp_utils.py -e -p blink_led -o D:\\rtt_proj
       bsp_utils.py --export_proj --project_name blink_led --output_dir D:\\rtt_proj

    4. Export all projects:
       bsp_utils.py -e -p all -o D:\\rtt_proj
       bsp_utils.py --export_proj --project_name all --output_dir D:\\rtt_proj

    5. Export to current directory:
       bsp_utils.py -e -p ethernet_demo -o .

EXPORT STRUCTURE:
    When exporting a project, the following structure is created:
    output_dir/
    └── project_name/
        ├── board/           # Board-specific configurations
        ├── libraries/       # RT-Thread Driver adapters, hpm_sdk and other components
        ├── rt-thread/       # RT-Thread source codes and scripts
        ├── startup/         # Startup files
        ├── applications/    # Main application code
        ├── packages/        # Third-party packages
        ├── Kconfig          # Build configuration
        └── README.md        # Project documentation

NOTES:
    • Use 'all' as project name to export all available projects
    • Output directory will be created if it doesn't exist
    • Existing project directories will be cleaned before export
    • The utility automatically excludes system files and utilities

For more information, visit: https://github.com/RT-Thread/rt-thread
"""
    print(usage_str)


def get_parser():
    """
    Create and configure the command-line argument parser.

    Returns:
        argparse.ArgumentParser: Configured parser with all available commands and options

    The parser includes:
    - Mutually exclusive commands (version, list, export)
    - Optional parameters for project name and output directory
    - Help text for each argument
    """
    parser = argparse.ArgumentParser(
        description="HPMicro RT-Thread BSP Project Management Utility",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  %(prog)s -v                                    # Show version
  %(prog)s -l                                    # List all projects
  %(prog)s -e -p blink_led -o D:/rtt_proj        # Export specific project
  %(prog)s -e -p all -o D:/rtt_proj              # Export all projects

For detailed usage information, run: %(prog)s
        """
    )

    # Create a mutually exclusive group for main commands
    # Only one of these commands can be used at a time
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument('-v', '--version',
                       action='store_true',
                       help='Display version information')
    group.add_argument('-l', '--list',
                       action='store_true',
                       help='List all supported example projects in this BSP')
    group.add_argument('-e', '--export_proj',
                       action='store_true',
                       help='Export project(s) from this BSP to specified destination')

    # Optional arguments that can be used with export command
    parser.add_argument('-p', '--project_name',
                        type=str,
                        help='Project name to export (use "all" for all projects)')
    parser.add_argument('-o', '--output_dir',
                        type=str,
                        help='Output directory for exported project(s)')
    return parser


def collect_proj_list():
    """
    Discover and collect all available project names from the projects directory.

    Returns:
        list: List of project directory names (strings)

    This function scans the 'projects/' directory relative to the script location
    and returns all subdirectory names, which represent available example projects.
    """
    # Get the directory where this script is located
    script_dir = os.path.dirname(os.path.realpath(__file__))
    # Construct path to the projects directory
    proj_dir = os.path.join(script_dir, 'projects')
    # Return list of all items in the projects directory
    return os.listdir(proj_dir)


def create_clean_dir(dir_path):
    """
    Create a clean directory by removing existing content if present.

    Args:
        dir_path (str): Path to the directory to be created/cleaned

    This function ensures the target directory is empty before use:
    - If directory exists and contains files/folders, removes all content
    - If directory doesn't exist, creates it
    - If path exists but is a file, removes the file and creates directory
    """
    if os.path.exists(dir_path):
        if os.path.isdir(dir_path):
            # Directory exists, remove all contents
            file_list = os.listdir(dir_path)
            for file in file_list:
                abs_path = os.path.join(dir_path, file)
                if os.path.isdir(abs_path):
                    # Remove subdirectory recursively
                    shutil.rmtree(abs_path)
                else:
                    # Remove file
                    os.remove(abs_path)
        else:
            # Path exists but is a file, remove it and create directory
            os.remove(dir_path)
            os.makedirs(dir_path)
    else:
        # Directory doesn't exist, create it
        os.makedirs(dir_path)


def list_supported_examples():
    """
    Display all available example projects in the BSP.

    This function provides a user-friendly listing of all example projects
    that can be exported or used as templates for development.
    """
    # Get list of all available projects
    proj_list = collect_proj_list()

    # Define project categories for better organization
    project_categories = {
        'Basic Examples': ['blink_led', 'timer_demo', 'uart_dma_demo'],
        'Communication': ['i2c_demo', 'can_example', 'mcan_example'],
        'Audio': ['audio_i2s_demo', 'audio_pdm_dao_demo'],
        'Storage': ['sdcard_demo', 'flashdb_demo'],
        'USB': ['usb_device_generic_hid', 'usb_host_msc_udisk', 'usb_host_nic'],
        'Display': ['lv_demo_widgets'],
        'Networking': ['airoc_wifi_demo', 'rw007_wifi', 'ethernet_demo', 'ethernet_ptp_master_demo', 'ethernet_ptp_slave_demo',
                       'tsn_lwip_tcpecho'],
        'Multimedia': ['web_camera_demo', 'wifi_web_camera_demo'],
        'Motor': ['pwm_demo', 'pwmbeep_demo'],
        'Analog': ['adc_example']
    }

    print("HPMicro RT-Thread BSP - Available Example Projects")
    print("=" * 55)

    if not proj_list:
        print("   No projects found")
    else:
        # Display projects by category
        for category, projects in project_categories.items():
            category_projects = [p for p in projects if p in proj_list]
            if category_projects:
                print(f"\n{category}:")
                for proj_name in sorted(category_projects):
                    print(f"   • {proj_name}")

        # Display any uncategorized projects
        all_categorized = []
        for projects in project_categories.values():
            all_categorized.extend(projects)

        uncategorized = [p for p in proj_list if p not in all_categorized]
        if uncategorized:
            print(f"\nOther Projects:")
            for proj_name in sorted(uncategorized):
                print(f"   • {proj_name}")

    print(f"\nTotal: {len(proj_list)} project(s) available")
    print("\nTo export a project, use: bsp_utils.py -e -p <project_name> -o <output_dir>")
    print("To export all projects, use: bsp_utils.py -e -p all -o <output_dir>")


def export_bsp_proj(proj_name, output_dir):
    """
    Export a specific BSP project to the specified output directory.

    Args:
        proj_name (str): Name of the project to export
        output_dir (str): Destination directory for the exported project

    Raises:
        SystemExit: If project doesn't exist or output directory is invalid

    This function performs a complete project export including:
    - Board-specific files and configurations
    - Common libraries and drivers
    - Project-specific application code
    - All necessary build files and configurations
    """
    # Validate that the requested project exists
    proj_list = collect_proj_list()
    if proj_name not in proj_list:
        print("Example '" + proj_name + "' is not supported.")
        exit(1)

    if not os.path.exists(output_dir):
        try:
            os.makedirs(output_dir)
        except Exception as e:
            print("Failed to create directory '" + output_dir + "'")
            exit(1)

    if not os.path.isdir(output_dir):
        print("directory '" + output_dir + "' is not a directory.")
        exit(1)

    # Validate output directory exists and is a directory
    if os.path.exists(output_dir) and os.path.isdir(output_dir):
        try:
            # Create the destination project root directory
            dst_proj_root = os.path.join(output_dir, proj_name)
            create_clean_dir(dst_proj_root)

            # Get the BSP root directory (where this script is located)
            bsp_root = os.path.dirname(os.path.realpath(__file__))

            # Copy board-specific files and configurations
            # This includes board.c, board.h, linker scripts, debug configurations, etc.
            src_board_dir = os.path.join(bsp_root, 'board')
            dst_board_dir = os.path.join(dst_proj_root, 'board')
            shutil.copytree(src_board_dir, dst_board_dir)

            # Copy common libraries and components
            # This includes RT-Thread, HPM SDK, drivers, and other shared components
            src_common_dir = os.path.join(bsp_root, 'common')
            for file_or_dir in os.listdir(src_common_dir):
                # Skip bsp_utils.py to avoid copying the utility itself
                if os.path.isdir(os.path.join(src_common_dir, file_or_dir)):
                    src_dir_path = os.path.join(src_common_dir, file_or_dir)
                    dst_dir_path = os.path.join(dst_proj_root, file_or_dir)
                    shutil.copytree(src_dir_path, dst_dir_path)

            # Copy project-specific files
            # This includes the main application code, build files, and project configurations
            src_project_dir = os.path.join(bsp_root, 'projects', proj_name)
            dst_project_dir = dst_proj_root
            for file_or_dir in os.listdir(src_project_dir):
                if os.path.isdir(os.path.join(src_project_dir, file_or_dir)):
                    # Copy subdirectories (like applications/, packages/, etc.)
                    src_dir_path = os.path.join(src_project_dir, file_or_dir)
                    dst_dir_path = os.path.join(dst_project_dir, file_or_dir)
                    shutil.copytree(src_dir_path, dst_dir_path)
                elif file_or_dir != 'bsp_utils.py':
                    # Copy individual files (like Kconfig, README.md, etc.)
                    src_file_path = os.path.join(src_project_dir, file_or_dir)
                    dst_file_path = os.path.join(dst_project_dir, file_or_dir)
                    shutil.copyfile(src_file_path, dst_file_path)

            # Success message with destination path
            print("Successfully exported project '" + proj_name + "' to '" + dst_project_dir + "'")

        except Exception as e:
            # Handle any errors during the export process
            print("Failed to export project '" + proj_name + "'")
            # Note: Could add more detailed error reporting here
    else:
        # Output directory validation failed
        print("directory '" + output_dir + "' does not exist.")
        exit(1)


if __name__ == '__main__':
    """
    Main entry point for the BSP utility script.

    This section handles command-line argument parsing and routes to appropriate
    functions based on the user's input. It also provides help when no arguments
    are provided.
    """
    # Create the argument parser
    app_parser = get_parser()

    # If no arguments provided, show usage information
    if len(sys.argv) == 1:
        show_usage()
    else:
        # Parse command-line arguments
        args = app_parser.parse_args()

        # Handle version command
        if args.version:
            show_version()

        # Handle list command
        if args.list:
            list_supported_examples()

        # Handle export command
        if args.export_proj:
            # Validate that both project name and output directory are provided
            if args.project_name is not None and args.output_dir is not None:
                if args.project_name == 'all':
                    # Special case: export all available projects
                    example_list = collect_proj_list()
                    for example_name in example_list:
                        export_bsp_proj(example_name, args.output_dir)
                else:
                    # Export specific project
                    export_bsp_proj(args.project_name, args.output_dir)
            else:
                # Missing required parameters for export
                help_str = 'bsp_utils.py --export_proj --project_name=<project_name> --output_dir=<project_output_dir>'
                print(help_str)
