# Copyright 2025 HPMicro
#
# SPDX-License-Identifier: BSD-3-Clause

from __future__ import print_function
import subprocess
import re
import os
import sys

# Python 2.7 compatibility
if sys.version_info[0] == 2:
    # Python 2.7 compatibility imports
    try:
        from subprocess import check_output
    except ImportError:
        check_output = None
else:
    # Python 3+
    from subprocess import check_output

# Only import winreg on Windows (Python 2 uses _winreg, Python 3 uses winreg)
if sys.platform == 'win32':
    try:
        # Python 3
        import winreg
    except ImportError:
        try:
            # Python 2
            import _winreg as winreg
        except ImportError:
            winreg = None
else:
    winreg = None

# Python 2/3 compatibility for exceptions
try:
    FileNotFoundError
except NameError:
    FileNotFoundError = IOError

try:
    PermissionError
except NameError:
    PermissionError = OSError


def _normalize_path(path):
    """Normalize path to forward slashes (Python 2/3 compatible)."""
    return os.path.normpath(path).replace('\\', '/')


def _open_registry_key(hkey, subkey, access=None):
    """
    Open registry key with Python 2/3 compatibility.
    Returns a context manager that closes the key.
    """
    if not winreg:
        raise RuntimeError("winreg module not available")

    if access is None:
        key = winreg.OpenKey(hkey, subkey)
    else:
        key = winreg.OpenKey(hkey, subkey, 0, access)

    # Python 2 doesn't support context managers for winreg keys
    # So we create a simple wrapper that works in both Python 2 and 3
    class RegistryKeyContext(object):
        def __init__(self, key_obj):
            self.key = key_obj

        def __enter__(self):
            return self.key

        def __exit__(self, exc_type, exc_val, exc_tb):
            winreg.CloseKey(self.key)
            return False

    return RegistryKeyContext(key)


def find_via_registry():
    """
    Find RT-Thread Studio installation path via Windows Registry.

    Checks common registry locations:
    - SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall
    - SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall (32-bit on 64-bit)

    Returns:
        str: Installation path if found, None otherwise
    """
    if not winreg:
        return None

    registry_keys = [
        (winreg.HKEY_LOCAL_MACHINE, r"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall"),
        (winreg.HKEY_LOCAL_MACHINE, r"SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall"),
        (winreg.HKEY_CURRENT_USER, r"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall"),
    ]

    # Search terms for RT-Thread Studio
    search_terms = [
        "RT-Thread Studio",
        "RT-ThreadStudio",
        "RTThreadStudio",
        "RT Thread Studio"
    ]

    for hkey, base_path in registry_keys:
        try:
            with _open_registry_key(hkey, base_path) as uninstall_key:
                i = 0
                while True:
                    try:
                        subkey_name = winreg.EnumKey(uninstall_key, i)
                        subkey_path = "{0}\\{1}".format(base_path, subkey_name)

                        try:
                            with _open_registry_key(hkey, subkey_path) as subkey:
                                # Try to read DisplayName
                                try:
                                    display_name, _ = winreg.QueryValueEx(subkey, "DisplayName")

                                    # Check if this is RT-Thread Studio
                                    if any(term.lower() in display_name.lower() for term in search_terms):
                                        # Try to get InstallLocation
                                        try:
                                            install_location, _ = winreg.QueryValueEx(subkey, "InstallLocation")
                                            if install_location and os.path.exists(install_location):
                                                return _normalize_path(install_location)
                                        except FileNotFoundError:
                                            pass

                                        # Try to get UninstallString and extract path
                                        try:
                                            uninstall_string, _ = winreg.QueryValueEx(subkey, "UninstallString")
                                            if uninstall_string:
                                                # Extract directory from uninstall string (usually ends with uninstaller)
                                                install_dir = os.path.dirname(uninstall_string)
                                                if install_dir and os.path.exists(install_dir):
                                                    # Check if studio.exe exists in this directory
                                                    studio_exe = os.path.join(install_dir, "studio.exe")
                                                    if os.path.exists(studio_exe):
                                                        return _normalize_path(install_dir)
                                        except FileNotFoundError:
                                            pass

                                except FileNotFoundError:
                                    pass
                        except (OSError, PermissionError):
                            pass

                        i += 1
                    except OSError:
                        break
        except (OSError, PermissionError, FileNotFoundError):
            continue

    return None


def find_via_wim():
    """
    Find RT-Thread Studio via Windows Installation Manager registry entries.

    WIM typically stores installation information in specific registry locations.
    This method checks for installation metadata.

    Returns:
        str: Installation path if found, None otherwise
    """
    if not winreg:
        return None

    # Check for WIM-specific registry keys
    wim_keys = [
        (winreg.HKEY_LOCAL_MACHINE, r"SOFTWARE\Microsoft\Windows\CurrentVersion\Installer\Folders"),
        (winreg.HKEY_LOCAL_MACHINE, r"SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Installer\Folders"),
    ]

    search_terms = ["RT-Thread", "RTThread", "Studio"]

    for hkey, key_path in wim_keys:
        try:
            with _open_registry_key(hkey, key_path) as wim_key:
                i = 0
                while True:
                    try:
                        value_name, value_data, _ = winreg.EnumValue(wim_key, i)

                        # Check if the path contains RT-Thread Studio related terms
                        if any(term.lower() in value_data.lower() for term in search_terms):
                            # Check if studio.exe exists in this path
                            path = value_data
                            if os.path.exists(path):
                                # Check if studio.exe exists in this directory or parent
                                if os.path.isfile(path):
                                    # If path is a file, check its directory
                                    studio_exe = os.path.join(os.path.dirname(path), "studio.exe")
                                    if os.path.exists(studio_exe):
                                        return _normalize_path(os.path.dirname(path))
                                else:
                                    # If path is a directory, check it directly
                                    studio_exe = os.path.join(path, "studio.exe")
                                    if os.path.exists(studio_exe):
                                        return _normalize_path(path)

                                # Also check parent directory
                                parent = os.path.dirname(path)
                                studio_exe_parent = os.path.join(parent, "studio.exe")
                                if os.path.exists(studio_exe_parent):
                                    return _normalize_path(parent)

                        i += 1
                    except OSError:
                        break
        except (OSError, PermissionError, FileNotFoundError):
            continue

    return None


def find_via_file_search():
    """
    Fallback method: Search for studio.exe on C: and D: drives.

    This method recursively searches for studio.exe in common locations
    or across the entire drive (limited to avoid excessive searching).

    Returns:
        str: Directory containing studio.exe if found, None otherwise
    """
    drives = ['C:', 'D:']
    search_paths = []

    # First, check common installation directories
    common_bases = [
        'Program Files',
        'Program Files (x86)',
        'DevTools',
        'Tools',
        'RT-ThreadStudio',
    ]

    for drive in drives:
        if os.path.exists(drive + os.sep):
            # Check common directories first
            for base in common_bases:
                base_path = os.path.join(drive + os.sep, base)
                if os.path.exists(base_path):
                    search_paths.append(base_path)

    # Search in common paths first (more efficient)
    for search_path in search_paths:
        try:
            for root, dirs, files in os.walk(search_path):
                # Skip hidden directories and system directories to speed up search
                dirs[:] = [d for d in dirs if not d.startswith('.')]

                if 'studio.exe' in files:
                    studio_path = os.path.join(root, 'studio.exe')
                    if os.path.exists(studio_path):
                        return _normalize_path(root)
        except (PermissionError, OSError):
            continue

    # If not found in common paths, do a broader search on root of C: and D:
    # But limit depth to avoid excessive searching
    for drive in drives:
        drive_path = drive + os.sep
        if not os.path.exists(drive_path):
            continue

        try:
            # Search in root level directories only (not recursive)
            for item_name in os.listdir(drive_path):
                item_path = os.path.join(drive_path, item_name)
                if os.path.isdir(item_path) and not item_name.startswith('.'):
                    try:
                        # Check if studio.exe is directly in this directory
                        studio_exe = os.path.join(item_path, 'studio.exe')
                        if os.path.exists(studio_exe):
                            return _normalize_path(item_path)

                        # Check one level deep in common subdirectories
                        if item_name in ['Program Files', 'Program Files (x86)', 'DevTools', 'Tools']:
                            for subitem_name in os.listdir(item_path):
                                subitem_path = os.path.join(item_path, subitem_name)
                                if os.path.isdir(subitem_path):
                                    studio_exe = os.path.join(subitem_path, 'studio.exe')
                                    if os.path.exists(studio_exe):
                                        return _normalize_path(subitem_path)
                    except (PermissionError, OSError):
                        continue
        except (PermissionError, OSError):
            continue

    return None


def find_rt_thread_studio():
    """
    Main function to find RT-Thread Studio installation directory.

    Tries multiple methods in order:
    1. Windows Registry
    2. Windows Installation Manager (WIM)
    3. File system search for studio.exe

    Returns:
        str: Installation directory path if found, None otherwise
    """
    if sys.platform != 'win32':
        return None

    # Method 1: Try registry first
    # print("Searching Windows Registry...")
    result = find_via_registry()
    if result:
        # print("Found via Registry: {0}".format(result))
        return result

    # Method 2: Try Windows Installation Manager
    # print("Searching Windows Installation Manager...")
    result = find_via_wim()
    if result:
        # print("Found via WIM: {0}".format(result))
        return result

    # Method 3: Fallback to file search
    # print("Searching for studio.exe in C: and D: drives...")
    result = find_via_file_search()
    if result:
        # print("Found via file search: {0}".format(result))
        return result

    return None


def run_subprocess(args, timeout=None):
    """
    Run subprocess with Python 2.7 and 3+ compatibility.

    Args:
        args (list): Command and arguments
        timeout (int): Timeout in seconds (Python 3+ only)

    Returns:
        tuple: (returncode, stdout, stderr)
    """
    if sys.version_info[0] == 2:
        # Python 2.7 compatibility
        try:
            result = subprocess.Popen(
                args, stdout=subprocess.PIPE, stderr=subprocess.PIPE
            )
            stdout, stderr = result.communicate()
            return result.returncode, stdout, stderr
        except Exception:
            return 1, "", ""
    else:
        # Python 3+
        try:
            result = subprocess.run(
                args, capture_output=True, text=True, timeout=timeout
            )
            return result.returncode, result.stdout, result.stderr
        except Exception:
            return 1, "", ""


def extract_info_from_verbose(compiler_path):
    """
    Extract default architecture, ABI, and multilib information from --verbose output.

    Args:
        compiler_path (str): Path to the compiler executable

    Returns:
        dict: Dictionary containing extracted information
    """
    info = {
        "default_arch": None,
        "default_abi": None,
        "multilib_generator": None,
        "target": None,
        "configured_with": None,
        "isa_spec": None,
        "tune": None,
        "pkgversion": None,
        "is_nds32": False,
        "architecture_family": None,
    }

    try:
        returncode, stdout, stderr = run_subprocess(
            [compiler_path, "--verbose"], timeout=15
        )
        verbose_output = stderr

        if returncode == 0:  # Verbose info is in stderr

            # Extract target
            target_match = re.search(r"Target:\s+(\S+)", verbose_output)
            if target_match:
                info["target"] = target_match.group(1)

                # Check if this is an NDS32 toolchain
                target = target_match.group(1).lower()
                if "nds32" in target or "andes" in target:
                    info["is_nds32"] = True
                    info["architecture_family"] = "riscv"
                elif "riscv" in target:
                    info["architecture_family"] = "riscv"
                elif "arm" in target:
                    info["architecture_family"] = "arm"
                elif "x86" in target or "i386" in target or "i686" in target:
                    info["architecture_family"] = "x86"
                elif "aarch64" in target:
                    info["architecture_family"] = "aarch64"
                else:
                    info["architecture_family"] = "unknown"

            # Extract configured with line
            configured_match = re.search(r"Configured with:\s+(.+)", verbose_output)
            if configured_match:
                info["configured_with"] = configured_match.group(1)

                # Extract default architecture from --with-arch
                arch_match = re.search(
                    r"--with-arch=([^\s]+)", configured_match.group(1)
                )
                if arch_match:
                    info["default_arch"] = arch_match.group(1)

                # Extract default ABI from --with-abi
                abi_match = re.search(r"--with-abi=([^\s]+)", configured_match.group(1))
                if abi_match:
                    info["default_abi"] = abi_match.group(1)

                # Extract multilib generator
                multilib_match = re.search(
                    r"--with-multilib-generator=\'([^\']+)\'", configured_match.group(1)
                )
                if multilib_match:
                    info["multilib_generator"] = multilib_match.group(1)

                # Extract ISA specification
                isa_spec_match = re.search(
                    r"--with-isa-spec=([^\s]+)", configured_match.group(1)
                )
                if isa_spec_match:
                    info["isa_spec"] = isa_spec_match.group(1)

                # Extract tune parameter
                tune_match = re.search(
                    r"--with-tune=([^\s]+)", configured_match.group(1)
                )
                if tune_match:
                    info["tune"] = tune_match.group(1)

                # Extract package version
                pkgversion_match = re.search(
                    r"--with-pkgversion=([^\s]+)", configured_match.group(1)
                )
                if pkgversion_match:
                    info["pkgversion"] = pkgversion_match.group(1)

    except Exception:
        pass
    return info


def parse_multilib_generator(multilib_generator_str):
    """
    Parse the multilib generator string to extract individual configurations.

    Args:
        multilib_generator_str (str): Multilib generator string from verbose output

    Returns:
        list: List of dictionaries containing multilib information
    """
    multilibs = []

    if not multilib_generator_str:
        return multilibs

    # Split by semicolon and parse each configuration
    configs = multilib_generator_str.split(";")
    for config in configs:
        config = config.strip()
        if not config:
            continue

        # Format: "rv32i-ilp32--" or "rv32imafc-ilp32f--"
        parts = config.split("-")
        if len(parts) >= 2:
            arch = parts[0]
            abi = parts[1]

            # Skip empty configurations (ending with --)
            if abi and not abi.endswith("--"):
                # Check for B extension support
                has_b_extension = (
                        "b" in arch.lower()
                        or "zbb" in arch.lower()
                        or "zbs" in arch.lower()
                        or "zba" in arch.lower()
                )

                # Parse architecture extensions
                extensions = parse_architecture_extensions(arch)

                multilib_info = {
                    "path": "{}/{}".format(arch, abi),
                    "abi": abi,
                    "arch": arch,
                    "flags": "@march={}@mabi={}".format(arch, abi),
                    "has_b_extension": has_b_extension,
                    "extensions": extensions,
                }
                multilibs.append(multilib_info)

    return multilibs


def parse_architecture_extensions(arch_string):
    """
    Parse RISC-V architecture string to extract individual extensions.

    Args:
        arch_string (str): Architecture string like 'rv32imafdc' or 'rv32imafdcb'

    Returns:
        dict: Dictionary containing extension information
    """
    extensions = {
        "base": None,
        "m": False,  # Integer Multiplication and Division
        "a": False,  # Atomic Instructions
        "f": False,  # Single-Precision Floating-Point
        "d": False,  # Double-Precision Floating-Point
        "c": False,  # Compressed Instructions
        "b": False,  # Bit Manipulation (B extension)
        "v": False,  # Vector Extension
        "k": False,  # Cryptography Extension
        "h": False,  # Hypervisor Extension
        "j": False,  # Dynamically Translated Languages
        "p": False,  # Packed-SIMD Extension
        "q": False,  # Quad-Precision Floating-Point
        "l": False,  # Decimal Floating-Point
        "n": False,  # User-Level Interrupts
        "s": False,  # Supervisor Mode
        "u": False,  # User Mode
        "x": False,  # Non-Standard Extensions
        "zbb": False,  # Basic Bit Manipulation
        "zbs": False,  # Single-Bit Instructions
        "zba": False,  # Address Generation
        "zbc": False,  # Carry-less Multiplication
        "zbe": False,  # Extract and Deposit
        "zbf": False,  # Bit Field Place
        "zbm": False,  # Matrix Multiply
        "zbp": False,  # Permutation
        "zbr": False,  # CRC
        "zbt": False,  # Ternary
        "other": [],  # Other extensions
    }

    if not arch_string or not arch_string.startswith("rv"):
        return extensions

    # Extract base architecture (rv32, rv64, etc.)
    base_match = re.match(r"rv(\d+)", arch_string)
    if base_match:
        extensions["base"] = "rv{}".format(base_match.group(1))

    # Parse extensions
    ext_part = arch_string[4:] if len(arch_string) > 4 else ""  # Skip 'rv32' or 'rv64'

    for char in ext_part:
        if char in extensions:
            extensions[char] = True
        else:
            extensions["other"].append(char)

    # Check for Z extensions (sub-extensions of B)
    z_extensions = re.findall(r"z[a-z]+", arch_string)
    for z_ext in z_extensions:
        if z_ext in extensions:
            extensions[z_ext] = True
        else:
            extensions["other"].append(z_ext)

    return extensions


def check_b_extension_support(compiler_path):
    """
    Check if the compiler supports B extension (Bit Manipulation).

    Args:
        compiler_path (str): Path to the compiler executable

    Returns:
        dict: Dictionary containing B extension support information
    """
    b_support = {
        "has_b_extension": False,
        "b_variants": [],
        "supported_b_extensions": [],
    }

    # Get verbose information
    verbose_info = extract_info_from_verbose(compiler_path)
    if verbose_info["multilib_generator"]:
        multilibs = parse_multilib_generator(verbose_info["multilib_generator"])

        for multilib in multilibs:
            if multilib.get("has_b_extension", False):
                b_support["has_b_extension"] = True
                b_support["b_variants"].append(multilib["arch"])

                # Check specific B sub-extensions
                extensions = multilib.get("extensions", {})
                for ext_name, ext_supported in extensions.items():
                    if (
                            ext_supported
                            and ext_name.startswith("z")
                            and ext_name
                            in [
                        "zbb",
                        "zbs",
                        "zba",
                        "zbc",
                        "zbe",
                        "zbf",
                        "zbm",
                        "zbp",
                        "zbr",
                        "zbt",
                    ]
                    ):
                        if ext_name not in b_support["supported_b_extensions"]:
                            b_support["supported_b_extensions"].append(ext_name)

    return b_support


def check_isa_spec_support(compiler_path):
    """
    Check ISA specification support and version.

    Args:
        compiler_path (str): Path to the compiler executable

    Returns:
        dict: Dictionary containing ISA specification information
    """
    isa_info = {
        "isa_spec": None,
        "isa_spec_version": None,
        "is_isa_spec_20191213": False,
        "is_isa_spec_2p2": False,
        "tune": None,
        "pkgversion": None,
    }

    # Get verbose information
    verbose_info = extract_info_from_verbose(compiler_path)

    if verbose_info["isa_spec"]:
        isa_info["isa_spec"] = verbose_info["isa_spec"]
        isa_info["isa_spec_version"] = verbose_info["isa_spec"]

        # Check for specific ISA spec versions
        isa_spec = verbose_info["isa_spec"]
        isa_info["is_isa_spec_20191213"] = "20191213" in isa_spec
        isa_info["is_isa_spec_2p2"] = "2.2" in isa_spec

    if verbose_info["tune"]:
        isa_info["tune"] = verbose_info["tune"]

    if verbose_info["pkgversion"]:
        isa_info["pkgversion"] = verbose_info["pkgversion"]

    return isa_info


def check_nds32_toolchain(compiler_path):
    """
    Check if the compiler is an NDS32 (Andes Technology) toolchain by examining --print-multi-lib output.

    Args:
        compiler_path (str): Path to the compiler executable

    Returns:
        dict: Dictionary containing NDS32 detection results
    """
    nds32_info = {
        "is_nds32": False,
        "architecture_family": None,
        "target": None,
        "compiler_name_nds32": False,
        "detection_method": None,
        "andes_found_in_multilib": False,
        "multilib_output": None,
    }

    # Check compiler executable name for NDS32 patterns
    compiler_name = os.path.basename(compiler_path).lower()
    nds32_patterns = [
        "nds32",
        "andes",
        "ae250",
        "ae350",
    ]

    for pattern in nds32_patterns:
        if pattern in compiler_name:
            nds32_info["is_nds32"] = True
            nds32_info["architecture_family"] = "riscv"
            nds32_info["compiler_name_nds32"] = True
            nds32_info["detection_method"] = "compiler_name"
            break

    # If not detected by name, check --print-multi-lib output for "andes"
    if not nds32_info["is_nds32"]:
        try:
            returncode, stdout, stderr = run_subprocess(
                [compiler_path, "--print-multi-lib"], timeout=10
            )
            if returncode == 0:
                multilib_output = stdout
                nds32_info["multilib_output"] = multilib_output

                # Search for "andes" in the multilib output (case-insensitive)
                if "andes" in multilib_output.lower():
                    nds32_info["is_nds32"] = True
                    nds32_info["architecture_family"] = "riscv"
                    nds32_info["andes_found_in_multilib"] = True
                    nds32_info["detection_method"] = "print_multi_lib_andes"

                    # Try to extract target information from verbose output
                    verbose_info = extract_info_from_verbose(compiler_path)
                    if verbose_info["target"]:
                        nds32_info["target"] = verbose_info["target"]
        except Exception:
            pass

    # Fallback: check verbose output if still not detected
    if not nds32_info["is_nds32"]:
        verbose_info = extract_info_from_verbose(compiler_path)
        if verbose_info["is_nds32"]:
            nds32_info["is_nds32"] = True
            nds32_info["architecture_family"] = verbose_info["architecture_family"]
            nds32_info["target"] = verbose_info["target"]
            if not nds32_info["detection_method"]:
                nds32_info["detection_method"] = "target_string"

    return nds32_info


def detect_default_arch(compiler_path):
    """
    Detect the default architecture for the given compiler.

    Args:
        compiler_path (str): Path to the compiler executable

    Returns:
        str: Default architecture string (e.g., 'rv32i', 'rv32im', 'rv32imac')
    """
    # Primary method: Extract from --verbose output
    verbose_info = extract_info_from_verbose(compiler_path)
    if verbose_info["default_arch"]:
        return verbose_info["default_arch"]

    # Fallback: Try to get default architecture using --print-multi-arch
    try:
        returncode, stdout, stderr = run_subprocess(
            [compiler_path, "--print-multi-arch"], timeout=10
        )
        if returncode == 0:
            archs = stdout.strip().split()
            if archs:
                return archs[0]  # First arch is typically the default
    except Exception:
        pass

    # Fallback: try to get arch from --print-multi-lib
    try:
        returncode, stdout, stderr = run_subprocess(
            [compiler_path, "--print-multi-lib"], timeout=10
        )
        if returncode == 0:
            lines = stdout.strip().split("\n")
            for line in lines:
                if ";" in line:
                    flags_part = (
                        line.split(";")[1].strip() if len(line.split(";")) > 1 else ""
                    )
                    if flags_part:
                        # Look for -march=xxx or @march=xxx
                        arch_match = re.search(r"[-@]march=([^\s@]+)", flags_part)
                        if arch_match:
                            return arch_match.group(1)
    except Exception:
        pass

    # Final fallback: try to detect from compiler version or use common defaults
    try:
        returncode, stdout, stderr = run_subprocess(
            [compiler_path, "--version"], timeout=10
        )
        if returncode == 0:
            version_output = stdout.lower()
            if "riscv" in version_output:
                # For RISC-V, common default is rv32i
                return "rv32i"
    except Exception:
        pass

    return "rv32i"  # Default fallback


def detect_default_abi(compiler_path):
    """
    Detect the default ABI for the given compiler.

    Args:
        compiler_path (str): Path to the compiler executable

    Returns:
        str: Default ABI string (e.g., 'ilp32', 'ilp32f', 'ilp32d', 'lp64', 'lp64f', 'lp64d')
    """
    # Primary method: Extract from --verbose output
    verbose_info = extract_info_from_verbose(compiler_path)
    if verbose_info["default_abi"]:
        return verbose_info["default_abi"]

    # Fallback: Try to get default ABI using --print-multi-abi
    try:
        returncode, stdout, stderr = run_subprocess(
            [compiler_path, "--print-multi-abi"], timeout=10
        )
        if returncode == 0:
            abis = stdout.strip().split()
            if abis:
                # Handle combined arch/abi format like "rv32i/ilp32"
                first_abi = abis[0]
                if "/" in first_abi:
                    return first_abi.split("/")[1]  # Extract ABI part
                return first_abi
    except Exception:
        pass

    # Fallback: try to get ABI from --print-multi-lib
    try:
        returncode, stdout, stderr = run_subprocess(
            [compiler_path, "--print-multi-lib"], timeout=10
        )
        if returncode == 0:
            lines = stdout.strip().split("\n")
            for line in lines:
                if ";" in line:
                    flags_part = (
                        line.split(";")[1].strip() if len(line.split(";")) > 1 else ""
                    )
                    if flags_part:
                        # Look for -mabi=xxx or @mabi=xxx
                        abi_match = re.search(r"[-@]mabi=([^\s@]+)", flags_part)
                        if abi_match:
                            return abi_match.group(1)
    except Exception:
        pass

    # Final fallback: try to detect from compiler version or use common defaults
    try:
        returncode, stdout, stderr = run_subprocess(
            [compiler_path, "--version"], timeout=10
        )
        if returncode == 0:
            version_output = stdout.lower()
            if "riscv" in version_output:
                # For RISC-V, common default is ilp32 for 32-bit
                return "ilp32"
    except Exception:
        pass

    return "ilp32"  # Default fallback


def detect_supported_abis(compiler_path):
    """
    Detect all supported ABIs for the given compiler.

    Args:
        compiler_path (str): Path to the compiler executable

    Returns:
        list: List of supported ABI strings
    """
    abis = []

    # Primary method: Extract from --verbose output
    verbose_info = extract_info_from_verbose(compiler_path)
    if verbose_info["multilib_generator"]:
        multilibs = parse_multilib_generator(verbose_info["multilib_generator"])
        for multilib in multilibs:
            if multilib["abi"] and multilib["abi"] not in abis:
                abis.append(multilib["abi"])
        if abis:
            return abis

    # Fallback: Try to get all ABIs using --print-multi-abi
    try:
        returncode, stdout, stderr = run_subprocess(
            [compiler_path, "--print-multi-abi"], timeout=10
        )
        if returncode == 0:
            raw_abis = stdout.strip().split()
            if raw_abis:
                # Handle combined arch/abi format like "rv32i/ilp32"
                for raw_abi in raw_abis:
                    if "/" in raw_abi:
                        abi_part = raw_abi.split("/")[1]  # Extract ABI part
                        if abi_part not in abis:
                            abis.append(abi_part)
                    else:
                        if raw_abi not in abis:
                            abis.append(raw_abi)
                if abis:
                    return abis
    except Exception:
        pass

    # Fallback: parse from --print-multi-lib
    try:
        returncode, stdout, stderr = run_subprocess(
            [compiler_path, "--print-multi-lib"], timeout=10
        )
        if returncode == 0:
            lines = stdout.strip().split("\n")
            for line in lines:
                if ";" in line:
                    flags_part = (
                        line.split(";")[1].strip() if len(line.split(";")) > 1 else ""
                    )
                    if flags_part:
                        # Look for -mabi=xxx or @mabi=xxx
                        abi_match = re.search(r"[-@]mabi=([^\s@]+)", flags_part)
                        if abi_match:
                            abi = abi_match.group(1)
                            if abi not in abis:
                                abis.append(abi)
    except Exception:
        pass

    # If no ABIs detected, return common RISC-V ABIs
    if not abis:
        abis = ["ilp32", "ilp32f", "ilp32d", "lp64", "lp64f", "lp64d"]

    return abis


def detect_supported_multilibs(compiler_path):
    """
    Detect all supported multilib configurations for the given compiler.

    Args:
        compiler_path (str): Path to the compiler executable

    Returns:
        list: List of dictionaries containing multilib information
              Each dict has keys: 'path', 'abi', 'arch', 'flags'
    """
    multilibs = []

    # Primary method: Extract from --verbose output
    verbose_info = extract_info_from_verbose(compiler_path)
    if verbose_info["multilib_generator"]:
        multilibs = parse_multilib_generator(verbose_info["multilib_generator"])
        if multilibs:
            return multilibs

    # Fallback: Parse from --print-multi-lib
    try:
        returncode, stdout, stderr = run_subprocess(
            [compiler_path, "--print-multi-lib"], timeout=10
        )
        if returncode == 0:
            lines = stdout.strip().split("\n")
            for line in lines:
                if ";" in line:
                    parts = line.split(";")
                    path_part = parts[0].strip()
                    flags_part = parts[1].strip() if len(parts) > 1 else ""

                    # Parse flags to extract ABI and architecture
                    abi = None
                    arch = None

                    if flags_part:
                        # Look for -mabi=xxx or @mabi=xxx
                        abi_match = re.search(r"[-@]mabi=([^\s@]+)", flags_part)
                        if abi_match:
                            abi = abi_match.group(1)

                        # Look for -march=xxx or @march=xxx
                        arch_match = re.search(r"[-@]march=([^\s@]+)", flags_part)
                        if arch_match:
                            arch = arch_match.group(1)

                    # Check for B extension support
                    has_b_extension = (
                            "b" in arch.lower()
                            or "zbb" in arch.lower()
                            or "zbs" in arch.lower()
                            or "zba" in arch.lower()
                    )

                    # Parse architecture extensions
                    extensions = parse_architecture_extensions(arch)

                    multilib_info = {
                        "path": path_part if path_part != "." else "",
                        "abi": abi,
                        "arch": arch,
                        "flags": flags_part,
                        "has_b_extension": has_b_extension,
                        "extensions": extensions,
                    }
                    multilibs.append(multilib_info)
    except Exception:
        pass

    return multilibs


def get_compiler_info(platform="gcc", exec_path=None, cc="riscv32-unknown-elf-gcc"):
    """
    Get comprehensive compiler information including ABI and multilib support.

    Args:
        platform (str): Platform type (default: 'gcc')
        exec_path (str): Path to the compiler directory
        cc (str): Compiler executable name

    Returns:
        dict: Dictionary containing compiler information
    """
    info = {
        "default_arch": None,
        "default_abi": None,
        "supported_abis": [],
        "supported_multilibs": [],
        "compiler_path": None,
        "verbose_info": None,
        "b_extension_support": None,
        "isa_spec_support": None,
        "nds32_toolchain": None,
    }

    # Determine compiler path based on platform
    if platform == "gcc":
        if exec_path is None:
            exec_path = "/opt/riscv-gnu-gcc/bin"  # Default path

        compiler_path = os.path.join(exec_path, cc)
        if os.name == "nt":
            compiler_path += ".exe"

        if os.path.exists(compiler_path):
            info["compiler_path"] = compiler_path
            # Get verbose information first (used by other detection functions)
            info["verbose_info"] = extract_info_from_verbose(compiler_path)

            # Use the enhanced detection functions
            info["default_arch"] = detect_default_arch(compiler_path)
            info["default_abi"] = detect_default_abi(compiler_path)

            # Check if this is an NDS32 toolchain
            info["nds32_toolchain"] = check_nds32_toolchain(compiler_path)

            if not info["nds32_toolchain"]["is_nds32"]:
                info["supported_abis"] = detect_supported_abis(compiler_path)
                info["supported_multilibs"] = detect_supported_multilibs(compiler_path)
                # Check B extension support
                info["b_extension_support"] = check_b_extension_support(compiler_path)
                # Check ISA specification support
                info["isa_spec_support"] = check_isa_spec_support(compiler_path)

            # Detect if this is an xPACK-distributed toolchain
            try:
                info["is_xpack"] = is_xpack_toolchain(compiler_path)
            except Exception:
                info["is_xpack"] = False
        else:
            info["nds32_toolchain"] = None

    return info


def is_xpack_toolchain(compiler_path):
    """
    Heuristic checks to determine whether a GCC toolchain was distributed by xPACK.

    Looks for tell-tale signs in --version, --verbose/Configured with, and
    package/version strings such as 'xpack', 'xPack', or 'x-pack' that
    are commonly embedded by xPACK-packaged toolchains.

    Args:
        compiler_path (str): Path to the compiler executable

    Returns:
        bool: True if the toolchain appears to be from xPACK, False otherwise
    """
    if not compiler_path or not os.path.exists(compiler_path):
        return False

    try:
        # 1) Check --version output
        returncode, stdout, stderr = run_subprocess([compiler_path, "--version"], timeout=8)
        out = (stdout or "") + (stderr or "")
        if returncode == 0 and re.search(r"\bxpack\b|xPack|x-pack", out, re.IGNORECASE):
            return True

        # 2) Check verbose configured-with / pkgversion
        verbose = extract_info_from_verbose(compiler_path)
        cfg = verbose.get("configured_with") or ""
        pkg = verbose.get("pkgversion") or ""
        combined = (cfg + " " + pkg).lower()
        if "xpack" in combined or "x-pack" in combined:
            return True

        # 3) Check for typical xPACK file layout: sometimes toolchain path contains 'xpack'
        gcc_dir = os.path.dirname(os.path.abspath(compiler_path))
        if "xpack" in gcc_dir.lower() or "x-pack" in gcc_dir.lower():
            return True

        # 4) Some xPACK toolchains include 'xpack' in the triplet/prefix or filename
        name = os.path.basename(compiler_path).lower()
        if "xpack" in name or "x-pack" in name:
            return True

    except Exception:
        return False

    return False


def find_gcc_executable(search_path):
    """
    Find GCC executable from the specified path.

    Args:
        search_path (str): Path to search for GCC executable

    Returns:
        str or None: Path to the GCC executable if found, None otherwise
    """
    if not search_path or not os.path.exists(search_path):
        return None

    # Common GCC executable names
    gcc_names = [
        "riscv32-unknown-elf-gcc",
        "riscv64-unknown-elf-gcc",
        "riscv-none-elf-gcc",
        "riscv32-elf-gcc",
    ]

    # Add .exe extension for Windows
    if os.name == "nt":
        gcc_names.extend([name + ".exe" for name in gcc_names])

    # Search in the specified directory
    for gcc_name in gcc_names:
        gcc_path = os.path.join(search_path, gcc_name)
        if os.path.isfile(gcc_path) and os.access(gcc_path, os.X_OK):
            return gcc_path

    # If not found in the directory, search in subdirectories
    try:
        for root, dirs, files in os.walk(search_path):
            for gcc_name in gcc_names:
                gcc_path = os.path.join(root, gcc_name)
                if os.path.isfile(gcc_path) and os.access(gcc_path, os.X_OK):
                    return gcc_path
    except (OSError, PermissionError):
        pass

    return None


def extract_triplet_from_gcc(gcc_path):
    """
    Extract the target triplet from GCC executable.

    Args:
        gcc_path (str): Path to the GCC executable

    Returns:
        str or None: Target triplet if found, None otherwise
    """
    if not gcc_path or not os.path.exists(gcc_path):
        return None

    try:
        # Method 1: Try to get target from --print-target
        returncode, stdout, stderr = run_subprocess(
            [gcc_path, "--print-target"], timeout=10
        )
        if returncode == 0:
            target = stdout.strip()
            if target:
                return target
    except Exception:
        pass

    try:
        # Method 2: Try to get target from --verbose output
        returncode, stdout, stderr = run_subprocess([gcc_path, "--verbose"], timeout=15)
        if returncode == 0:
            verbose_output = stderr
            target_match = re.search(r"Target:\s+(\S+)", verbose_output)
            if target_match:
                return target_match.group(1)
    except Exception:
        pass

    try:
        # Method 3: Try to extract from executable name
        gcc_basename = os.path.basename(gcc_path)
        # Remove .exe extension if present
        if gcc_basename.endswith(".exe"):
            gcc_basename = gcc_basename[:-4]

        # Common patterns for extracting triplet from name
        # riscv32-unknown-elf-gcc -> riscv32-unknown-elf
        # arm-none-eabi-gcc -> arm-none-eabi
        # x86_64-linux-gnu-gcc -> x86_64-linux-gnu
        if gcc_basename.endswith("-gcc"):
            triplet = gcc_basename[:-4]  # Remove '-gcc' suffix
            # Validate that it looks like a triplet (has at least 2 dashes)
            if triplet.count("-") >= 2:
                return triplet
    except Exception:
        pass

    return None


def find_gcc_and_extract_triplet(search_path):
    """
    Find GCC executable from specified path and extract its triplet.

    Args:
        search_path (str): Path to search for GCC executable

    Returns:
        dict: Dictionary containing 'gcc_path' and 'triplet' keys
              Both values will be None if not found
    """
    result = {"gcc_path": None, "triplet": None}

    # Find GCC executable
    gcc_path = find_gcc_executable(search_path)
    if gcc_path:
        result["gcc_path"] = gcc_path

        # Extract triplet
        triplet = extract_triplet_from_gcc(gcc_path)
        if triplet:
            result["triplet"] = triplet

    return result
