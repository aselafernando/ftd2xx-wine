#!/usr/bin/env python3
import re
import os
import sys

exclude_funcs = ['FT_Initialise','FT_Finalise','FT_W32_GetCommMask']

def is_pointer(arg_type, arg_name):
    return arg_name.startswith("*") or arg_type.endswith("*") or arg_type == "FT_HANDLE" or arg_type.startswith("LP") or arg_type.startswith("P")

def extract_function_details(filename):
    # Check if file exists
    if not os.path.exists(filename):
        raise FileNotFoundError(f"The file {filename} does not exist.")

    # Read the file content
    with open(filename, 'r', encoding='utf-8') as file:
        c_code = file.read()

    # Regex pattern to match function prototypes and their arguments
    pattern = r'((?:FTD2XX_API\s+)?(FT_STATUS|FT_HANDLE|BOOL|void)\s+(?:WINAPI\s+)?(\w+)\s*\(([^)]*)\)\s*);'
    # Find all matches
    matches = re.findall(pattern, c_code, re.DOTALL)

    # Process and format the results
    function_details = []
    for full_prototype, return_type, func_name, args_str in matches:
        # Clean and parse arguments
        args = [arg.strip() for arg in args_str.split(',') if arg.strip()]

        # Parse individual argument details
        parsed_args = []
        for arg in args:
            # Split argument into type and name
            arg_parts = arg.split()
            if len(arg_parts) > 1:
                arg_type = ' '.join(arg_parts[:-1])
                arg_name = arg_parts[-1]
                parsed_args.append({
                    'type': arg_type.strip(),
                    'name': arg_name.strip(),
                    'is_pointer': is_pointer(arg_type.strip(), arg_name.strip())
                })
            else:
                # Fallback if parsing fails
                parsed_args.append({
                    'type': arg,
                    'name': '',
                    'is_pointer': False
                })

        function_details.append({
            'prototype': full_prototype.strip(),
            'return_type': return_type.strip(),
            'name': func_name.strip(),
            'arguments': parsed_args
        })

    return function_details

def main():
    try:
        exports_type = sys.argv[1]

        # Attempt to find the file in common locations
        possible_paths = [
            'linux-x86_64/ftd2xx.h',  # Current directory
            '/usr/include/ftd2xx.h',  # Linux system include
            '/usr/local/include/ftd2xx.h',  # Alternative system include
            os.path.expanduser('~/ftd2xx.h'),  # User home directory
        ]

        # Find the first existing file
        filename = next(path for path in possible_paths if os.path.exists(path))

        # Extract function details
        function_details = extract_function_details(filename)

        # Print detailed information
        #print(f"Found {len(function_details)} function prototypes in {filename}:")
        wine_unix_call_funcs_string = "const unixlib_entry_t __wine_unix_call_funcs[] =\n{\n"
        wine_unix_call_wow64_funcs_string = "const unixlib_entry_t __wine_unix_call_wow64_funcs[] =\n{\n"
        unix_funcs_enum_string = "enum unix_func {\n"

        for func in function_details:
            if func['name'] not in exclude_funcs:
                wine_unix_call_funcs_string += "    wrap_"+func['name']+",\n"
                wine_unix_call_wow64_funcs_string += "    wow64_wrap_"+func['name']+",\n"
                unix_funcs_enum_string += "    unix_"+func['name']+",\n"
                prototype = func['prototype'].replace("\t","    ").replace("FTD2XX_API ","")
                ftd2xx_func_string = prototype+"{\n    struct prm_"+func['name']+" a = {"
                unixlib_ext_func_string = "extern "+prototype.replace(" WINAPI","").replace(func['return_type']+" FT",func['return_type']+" xFT")+";"
                if func['return_type'] != "void":
                    unixlib_func_string ="    a->ret = x"+func['name']+"("
                    unixlib_wow64_func_string ="    a->ret = x"+func['name']+"("
                else:
                    unixlib_func_string ="    x"+func['name']+"("
                    unixlib_wow64_func_string ="    x"+func['name']+"("
                struct_args_string = "{ "
                struct_wow64_args_string = "{ "
                spec_args_string = ""
                for arg in func['arguments']:
                    if arg['name'] != "":
                        name = arg['name'].replace('*','')
                        ftd2xx_func_string += "."+name+"="+name+", "
                        struct_args_string += arg['type']+" "+arg['name']+"; "
                        unixlib_func_string += "a->"+name+", "
                        if arg["is_pointer"]:
                            struct_wow64_args_string += "uint32_t "+name+"; "
                            if arg['name'].startswith("*"):
                                unixlib_wow64_func_string += "("+arg['type']+"*)ULongToPtr(a->"+name+"), "
                            else:
                                unixlib_wow64_func_string += "("+arg['type']+")ULongToPtr(a->"+name+"), "
                            spec_args_string += "ptr "
                        else:
                            struct_wow64_args_string += arg['type']+" "+arg['name']+"; "
                            unixlib_wow64_func_string += "a->"+name+", "
                            spec_args_string += "long "
                if exports_type == "objcopy":
                    print(func['name'].ljust(30) + " x"+func['name'])
                elif exports_type == "spec":
                    print("@ stdcall "+func['name']+"("+spec_args_string.rstrip(' ')+")")
                elif exports_type == "ftd2xx":
                    ftd2xx_func_string = ftd2xx_func_string.rstrip(', ') + "};\n    Trace(\"Entering\\n\");\n    WINE_UNIX_CALL( unix_"+func['name']+", &a );\n"
                    if func['return_type'] == "FT_STATUS":
                        ftd2xx_func_string += "    Trace(\"Return %lu\\n\", a.ret);\n    return a.ret;\n}\n"
                    elif func['return_type'] == "BOOL":
                        ftd2xx_func_string += "    Trace(\"Return %d\\n\", a.ret);\n    return a.ret;\n}\n"
                    else:
                        ftd2xx_func_string += "    Trace(\"Returned\\n\");\n    return a.ret;\n}\n"
                    print(ftd2xx_func_string)
                elif exports_type == "unixlibh":
                    if func['return_type'] != "void":
                        struct_args_string += func['return_type']+" ret; };"
                        struct_wow64_args_string += func['return_type']+" ret; };"
                    else:
                        struct_args_string += " };"
                        struct_wow64_args_string += " };"
                    print("struct prm_"+func['name']+" "+struct_args_string+"\nstruct p32_"+func['name']+" "+struct_wow64_args_string+"\n")
                elif exports_type == "unixlibc":
                    unixlib_func_string = unixlib_func_string.rstrip(', ') + ");"
                    unixlib_wow64_func_string = unixlib_wow64_func_string.rstrip(', ') + ");"
                    print("NTSTATUS wrap_"+func['name']+"(void *args) {\n    struct prm_"+func['name']+" *a = args;\n"+unixlib_func_string+"\n    return STATUS_SUCCESS;\n}\n")
                    print("NTSTATUS wow64_wrap_"+func['name']+"(void *args) {\n    struct p32_"+func['name']+" *a = args;\n"+unixlib_wow64_func_string+"\n    return STATUS_SUCCESS;\n}\n")
                elif exports_type == "unixlibe":
                    print(unixlib_ext_func_string)
        if exports_type == "unixlibh":
            unix_funcs_enum_string += "};"
            print(unix_funcs_enum_string)
        if exports_type == "wine":
            wine_unix_call_funcs_string += "};\n"
            wine_unix_call_wow64_funcs_string += "};"
            print(wine_unix_call_funcs_string)
            print(wine_unix_call_wow64_funcs_string)

    except StopIteration:
        print("Could not find ftd2xx.h file. Please provide the correct path.")
    except FileNotFoundError as e:
        print(e)
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

if __name__ == '__main__':
    main()

